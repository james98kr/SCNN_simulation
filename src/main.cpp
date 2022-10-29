#include "../include/scnn/datatypes.h"
#include "../include/scnn/tensor.h"
#include "../include/scnn/config_arch.h"
#include "../include/scnn/config_dataflow.h"
#include "../include/scnn/ioram.h"
#include "../include/scnn/weight_fifo.h"
#include "../include/scnn/mult_array.h"
#include "../include/scnn/crossbar.h"
#include "../include/scnn/accum_banks.h"
#include "../include/scnn/golden_model.h"

using namespace SCNN;


// need to resolve bug when size of input activation is 
// smaller than number of PEs

int main() {
    int N = 1;
    int C = 1;
    int Orig_H = 5;
    int Orig_W = 5;
    int K = 1;
    int Kc = 1;
    int S = 5;
    int R = 5;
    int PE_Num_W = 1;
    int PE_Num_H = 1;
    int H = Orig_H / PE_Num_H;
    int W = Orig_W / PE_Num_W;
    int I = 4;
    int F = 4;
    int xbar_in = I * F;
    int xbar_out = xbar_in * 2;
    int acc_bank_num = F * I * 2;
    float sparsity = 0.6;

    ConfigArch arch = ConfigArch(F,I,xbar_in,xbar_out,1000,1000,1000,1000,acc_bank_num,1000);
    ConfigDataflow layer = ConfigDataflow(N,K,Kc,C,W,H,Orig_W,Orig_H,R,S,PE_Num_W,PE_Num_H);
    SparseRAM sram0 = SparseRAM(&arch);
    SparseRAM sram1 = SparseRAM(&arch);
    WeightFIFO wfifo = WeightFIFO(&arch, &layer);
    IORAM ioram = IORAM(&sram0, &sram1);
    MultArray multarray = MultArray(&arch, &layer);
    CrossBar crossbar = CrossBar(&arch);
    AccumulatorBanks accumbanks = AccumulatorBanks(&arch);

    Tensor4D_W w(K,C,S,R);
    w.initialize_random(sparsity, -1, 1);
    w.compress_W_sparse(Kc);

    wfifo.set_w_buffer(w.get_w_buffer());
    wfifo.set_w_indices(w.get_w_indices());

    Tensor4D_IO io(N,C,Orig_H,Orig_W);
    io.initialize_random(sparsity, -1, 1);

    Tensor4D_IO final(N,K,Orig_H,Orig_W);
    final.initialize_value(0);

    vector<IO_vec> flush_port_out;

    cout << "Performing sparse convolution..." << endl;
    for (int tile_num=0; tile_num<(PE_Num_W * PE_Num_H); tile_num++) {
        cout << "tile_num: " << tile_num << endl; 
        ioram.get_ram0()->reset_all();
        wfifo.reset_all();
        multarray.reset_io_cnt();
        multarray.reset_w_cnt();

        io.compress_IO_sparse_tile(&layer, tile_num);
        ioram.get_ram0()->set_tile_num(tile_num);
        ioram.get_ram0()->set_io_buffer(io.get_io_buffer());
        ioram.get_ram0()->set_io_indices(io.get_io_indices());
        
        IO_vec io_vec;
        vector<int> io_idx;
        W_vec w_vec;
        vector<int> w_idx;
        IO_vec out;

        for (int n=0; n<N; n++) {
            for (int kprm=0; kprm<K/Kc; kprm++) {
                // cout << "kprm: " << kprm << endl;
                for (int c=0; c<C; c++) {
                    // cout << "c: " << c << endl;
                    while (true) {
                        io_vec = ioram.get_ram0()->send_input_activation_to_mult_array();
                        io_idx = ioram.get_ram0()->send_input_idx_to_mult_array();
                        multarray.load_input(io_vec, io_idx);
                        if (io_vec.size() <= 0)
                            break;

                        while (true) {
                            w_vec = wfifo.send_weight_activation_to_mult_array();
                            w_idx = wfifo.send_weight_idx_to_mult_array();
                            if (w_vec.size() <= 0)
                                break;
                            multarray.load_weight(w_vec, w_idx);

                            // Perform F x I parallel cartesian product calculation
                            out = multarray.cartesian_product(tile_num, ioram.get_ram0()->get_n_idx(), ioram.get_ram0()->get_c_idx(), wfifo.get_k_idx());
                            // This code for checking validity of algorithm up to multarray
                            for (int p=0; p<out.size(); p++) {
                                if (!out[p].get_valid()) {
                                    continue;
                                }
                                final.accumulate_idx_to_val(out[p].get_data(), out[p].get_idx());
                            }

                            // // Distribute output from multiplier array to corresponding accumulator buffer banks 
                            // crossbar.receive_port_in(out);
                            // flush_port_out = crossbar.distribute_input_to_output();
                            // // This code for checking how elements are spread out among accumulator banks
                            // // for (int idk=0; idk<flush_port_out.size(); idk++) {
                            // //     if (flush_port_out[idk].size() != 0) 
                            // //         cout << flush_port_out[idk].size() << " ";
                            // // }
                            // // cout << " " << endl;

                            // // Accumulator buffer bank
                            // accumbanks.receive_accum_inputs(flush_port_out);
                            // while (!accumbanks.get_finished()) {
                            //     accumbanks.accumulate_one_cycle();
                            // }

                            wfifo.incr_i_idx();
                        }

                        wfifo.reset_i_idx();
                        ioram.get_ram0()->incr_i_idx();
                        multarray.reset_w_cnt();
                    }
                    ioram.get_ram0()->reset_i_idx();
                    ioram.get_ram0()->incr_c_idx();
                    wfifo.incr_c_idx();
                    multarray.reset_io_cnt();
                }
                accumbanks.flush_to_output(&final);
                ioram.get_ram0()->reset_c_idx();
                wfifo.reset_c_idx();
                wfifo.incr_k_idx();
            }
            wfifo.reset_k_idx();
        }
    }

    // Postprocessing for next convolution layer
    ioram.swap_occupied();
    final.compress_IO_sparse();

    // Validation using golden conv model
    GoldenConvModel goldenconvmodel = GoldenConvModel(&io, &w);
    goldenconvmodel.golden_convolution();
    goldenconvmodel.validation(&final);

    return 0;
}