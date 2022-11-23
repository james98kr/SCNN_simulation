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
    int F = wfifo->get_cfg_arch()->get_mult_arr_F();
    int I = wfifo->get_cfg_arch()->get_mult_arr_I();

    int cycle = 0;
    int mult_cycle = 0;
    int mult_util = 0;
    bool loop_terminate = false;
    bool loop_start = true;
    bool accumbanks_flush = false;

    // Initialize final tensor that will be returned
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
        cout << "\rtile_num: " << tile_num + 1 << "/" << PE_Num_W * PE_Num_H;
        cout.flush(); 
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
        IO_vec multarray_out;
        vector<IO_vec> crossbar_out;

        for (int n=0; n<N; n++) {
            while (true) {
                // Accumulator Buffer Bank: Perform accumulation / flush
                accumbanks->accumulate_one_cycle();
                if (accumbanks_flush) {
                    accumbanks_flush = false;
                    accumbanks->flush_to_output(&final);
                }

                // CrossBar: Distribute output to corresponding accumulator buffer banks 
                // If queue is full, stall until queue is cleared
                crossbar_out = crossbar->distribute_input_to_output();
                accumbanks->receive_accum_inputs(crossbar_out);
                if (accumbanks->get_max_queue_depth() < accumbanks->get_queue_max_len()) {
                    while (accumbanks->get_queue_max_len() > 0) {
                        accumbanks->accumulate_one_cycle();
                        cycle++;
                    }
                }

                // Multiplier Array: Perform F x I parallel cartesian product calculation
                multarray_out = multarray->cartesian_product(tile_num, ioram->get_ram0()->get_n_idx(), ioram->get_ram0()->get_c_idx(), wfifo->get_k_idx());
                if (multarray_out.size() > 0) {
                    mult_util += multarray_out.size();
                    mult_cycle++;
                }
                crossbar->receive_port_in(multarray_out);

                // IORAM, WFIFO: Fetch input activations and weight
                if (wfifo->get_k_idx() < (K/Kc)) {
                    w_vec = wfifo->send_weight_activation_to_mult_array();
                    w_idx = wfifo->send_weight_idx_to_mult_array();
                    wfifo->incr_i_idx();
                    multarray->load_weight(w_vec, w_idx);
                    if (loop_start) {
                        io_vec = ioram->get_ram0()->send_input_activation_to_mult_array();
                        io_idx = ioram->get_ram0()->send_input_idx_to_mult_array();
                        ioram->get_ram0()->incr_i_idx();
                        multarray->load_input(io_vec, io_idx);
                        loop_start = false;
                    }
                    
                    if (w_vec.size() <= 0 && io_vec.size() > 0) {
                        wfifo->reset_i_idx();
                        multarray->reset_w_cnt();
                        w_vec = wfifo->send_weight_activation_to_mult_array();
                        w_idx = wfifo->send_weight_idx_to_mult_array();
                        wfifo->incr_i_idx();
                        multarray->load_weight(w_vec, w_idx);

                        io_vec = ioram->get_ram0()->send_input_activation_to_mult_array();
                        io_idx = ioram->get_ram0()->send_input_idx_to_mult_array();
                        ioram->get_ram0()->incr_i_idx();
                        multarray->load_input(io_vec, io_idx);
                    }
                    if (io_vec.size() <= 0) {
                        wfifo->reset_i_idx();
                        wfifo->incr_c_idx();
                        ioram->get_ram0()->reset_i_idx();
                        ioram->get_ram0()->incr_c_idx();
                        multarray->reset_w_cnt();
                        multarray->reset_io_cnt();
                        loop_start = true;
                    }
                    if (wfifo->get_c_idx() == C) {
                        wfifo->reset_c_idx();
                        wfifo->incr_k_idx();
                        ioram->get_ram0()->reset_c_idx();
                        accumbanks_flush = true;
                        loop_start = true;
                    }
                }
                if (wfifo->get_k_idx() == (K/Kc)) {
                    w_vec.clear();
                    w_idx.clear();
                    io_vec.clear();
                    io_idx.clear();
                    multarray->load_weight(w_vec, w_idx);
                    multarray->load_input(io_vec, io_idx);
                }

                // Increment cycle
                cycle++;

                // Condition for loop termination
                if (loop_terminate) {
                    loop_terminate = false;
                    break;
                }
                if (wfifo->get_k_idx() == (K/Kc) && multarray_out.size() <= 0) {
                    loop_terminate = true;
                    accumbanks_flush = true;
                    for (int t=0; t<crossbar_out.size(); t++) {
                        if (crossbar_out[t].size() > 0) {
                            loop_terminate = false;
                            break;
                        }
                    }
                }
            }

            // Complete convolution layer by clearing the queue
            while (accumbanks->get_queue_max_len() > 0) {
                accumbanks->accumulate_one_cycle();
                cycle++;
            }

            ioram->get_ram0()->incr_n_idx();
            wfifo->reset_k_idx();
        }
    }

    cout << "\n- Total number of cycles: " << cycle << endl;
    cout << "- Multiplier utilization: " << ((float) mult_util / (mult_cycle * F * I)) << endl;
    cout << "   - Total mult_array output size: " << mult_util << endl;
    cout << "   - Mult_cycle: " << mult_cycle << "\n" <<endl;

    return final;
}

}