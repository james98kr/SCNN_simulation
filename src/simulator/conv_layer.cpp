#include "../../include/simulator/conv_layer.h"

namespace SCNN {

ConvLayer::ConvLayer(
    IORAM* _ioram,
    WeightFIFO* _wfifo,
    MultArray* _multarray,
    CrossBar* _crossbar,
    AccumulatorBanks* _accumbanks
) {
    ioram = _ioram;
    wfifo = _wfifo;
    multarray = _multarray;
    crossbar = _crossbar;
    accumbanks = _accumbanks;
}

void ConvLayer::set_cfg_layer(ConfigDataflow* _cfg_layer) {
    cfg_layer = _cfg_layer;
    multarray->set_cfg_layer(_cfg_layer);
    crossbar->set_cfg_layer(_cfg_layer);
}

Tensor4D_IO ConvLayer::convolution(Tensor4D_IO* io, Tensor4D_W* w, int layer_num) {
    int N = cfg_layer->get_N();
    int C = cfg_layer->get_C();
    int Orig_H = cfg_layer->get_Orig_H();
    int Orig_W = cfg_layer->get_Orig_W();
    int K = cfg_layer->get_K();
    int Kc = cfg_layer->get_Kc();
    int S = cfg_layer->get_S();
    int R = cfg_layer->get_R();
    int PE_Num_W = cfg_layer->get_PE_Num_W();
    int PE_Num_H = cfg_layer->get_PE_Num_H();
    float io_sparsity = cfg_layer->get_io_sparsity();
    float w_sparsity = cfg_layer->get_w_sparsity();

    // Initialize final tensor that will be returned
    vector<IO_vec> flush_port_out;
    Tensor4D_IO final(N,K,Orig_H,Orig_W);
    final.initialize_value(0);

    // Initialize input activation tensor and weight tensor
    w->initialize_random(w_sparsity, -1, 1);
    w->compress_W_sparse(Kc);
    wfifo->set_w_buffer(w->get_w_buffer());
    wfifo->set_w_indices(w->get_w_indices());
    io->initialize_random(io_sparsity, -1, 1);

    cout << "Performing sparse convolution on layer " << layer_num << "..." << endl;
    for (int tile_num=0; tile_num<(PE_Num_W * PE_Num_H); tile_num++) {
        // cout << "tile_num: " << tile_num << endl; 
        ioram->get_ram0()->reset_all();
        wfifo->reset_all();
        multarray->reset_io_cnt();
        multarray->reset_w_cnt();

        io->compress_IO_sparse_tile(cfg_layer, tile_num);
        ioram->get_ram0()->set_tile_num(tile_num);
        ioram->get_ram0()->set_io_buffer(io->get_io_buffer());
        ioram->get_ram0()->set_io_indices(io->get_io_indices());
        
        IO_vec io_vec;
        vector<int> io_idx;
        W_vec w_vec;
        vector<int> w_idx;
        IO_vec out;

        for (int n=0; n<N; n++) {
            for (int kprm=0; kprm<(K/Kc); kprm++) {
                // cout << "kprm: " << kprm << endl;
                for (int c=0; c<C; c++) {
                    // cout << "c: " << c << endl;
                    while (true) {
                        io_vec = ioram->get_ram0()->send_input_activation_to_mult_array();
                        io_idx = ioram->get_ram0()->send_input_idx_to_mult_array();
                        multarray->load_input(io_vec, io_idx);
                        if (io_vec.size() <= 0)
                            break;

                        while (true) {
                            w_vec = wfifo->send_weight_activation_to_mult_array();
                            w_idx = wfifo->send_weight_idx_to_mult_array();
                            if (w_vec.size() <= 0)
                                break;
                            
                            // Perform F x I parallel cartesian product calculation
                            multarray->load_weight(w_vec, w_idx);
                            out = multarray->cartesian_product(tile_num, ioram->get_ram0()->get_n_idx(), ioram->get_ram0()->get_c_idx(), wfifo->get_k_idx());

                            // Distribute output from multiplier array to corresponding accumulator buffer banks 
                            crossbar->receive_port_in(out);
                            flush_port_out = crossbar->distribute_input_to_output();

                            // Accumulator buffer bank
                            accumbanks->receive_accum_inputs(flush_port_out);
                            while (!accumbanks->get_finished())
                                accumbanks->accumulate_one_cycle();

                            wfifo->incr_i_idx();
                        }

                        wfifo->reset_i_idx();
                        ioram->get_ram0()->incr_i_idx();
                        multarray->reset_w_cnt();
                    }
                    ioram->get_ram0()->reset_i_idx();
                    ioram->get_ram0()->incr_c_idx();
                    wfifo->incr_c_idx();
                    multarray->reset_io_cnt();
                }
                accumbanks->flush_to_output(&final);
                ioram->get_ram0()->reset_c_idx();
                wfifo->reset_c_idx();
                wfifo->incr_k_idx();
            }
            ioram->get_ram0()->incr_n_idx();
            wfifo->reset_k_idx();
        }
    }

    return final;
}

}