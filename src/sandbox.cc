#include "../include/scnn/datatypes.h"
#include "../include/scnn/tensor.h"
#include "../include/scnn/config_arch.h"
#include "../include/scnn/config_dataflow.h"
#include "../include/scnn/ioram.h"
#include "../include/scnn/weight_fifo.h"
#include "../include/scnn/mult_array.h"

// int MultArray::hash_function(tensor_4D_idx _idx) {
//     int sum_of_idx = get<0>(_idx) + get<1>(_idx) + get<2>(_idx) + get<3>(_idx);
//     return (int) (sum_of_idx % cfg_arch->get_acc_bank_num());
// }
using namespace SCNN;

int main() {
    int N = 1;
    int C = 3;
    int H = 4;
    int W = 4;
    int K = 4;
    int Kc = 2;
    int S = 3;
    int R = 3;
    int PE_Num_W = 1;
    int PE_Num_H = 1;
    int I = 4;
    int F = 4;
    int tile_num = 0;

    ConfigArch arch = ConfigArch(F,I,16,32,1000,1000,1000,1000,1000,1000);
    ConfigDataflow layer = ConfigDataflow(N,K,Kc,C,W,H,R,S,PE_Num_W,PE_Num_H);

    Tensor4D_IO io(N,C,H,W);
    io.initialize_random(0.5);
    io.compress_IO_sparse();
    // IO_buffer iobuffer = io.get_io_buffer();
    // IO_indices ioindices = io.get_io_indices();
    // for (int i=0; i<iobuffer.size(); i++) {
    //     for (int j=0; j<iobuffer[i].size(); j++) {
    //         for (int k=0; k<iobuffer[i][j].size(); k++) {
    //             iobuffer[i][j][k].print();
    //         }
    //         cout << endl;
    //     }
    // }

    // for (int i=0; i<ioindices.size(); i++) {
    //     for (int j=0; j<ioindices[i].size(); j++) {
    //         for (int k=0; k<ioindices[i][j].size(); k++) {
    //             cout << ioindices[i][j][k] << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    Tensor4D_W w(K,C,S,R);
    w.initialize_random(0.5);
    w.compress_W_sparse(Kc);
    // W_buffer wbuffer = w.get_w_buffer();
    // W_indices windices = w.get_w_indices();
    // for (int i=0; i<wbuffer.size(); i++) {
    //     for (int j=0; j<wbuffer[i].size(); j++) {
    //         for (int k=0; k<wbuffer[i][j].size(); k++) {
    //             wbuffer[i][j][k].print();
    //         }
    //         cout << endl;
    //     }
    // }

    // for (int i=0; i<windices.size(); i++) {
    //     for (int j=0; j<windices[i].size(); j++) {
    //         for (int k=0; k<windices[i][j].size(); k++) {
    //             cout << windices[i][j][k] << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    SparseRAM sram = SparseRAM(io.get_io_buffer(), io.get_io_indices(), &arch, 0);
    WeightFIFO wfifo = WeightFIFO(w.get_w_buffer(), w.get_w_indices(), &arch, &layer);
    MultArray multarray = MultArray(&arch, &layer);

    IO_vec io_vec;
    vector<int> io_idx;
    W_vec w_vec;
    vector<int> w_idx;
    IO_vec out;

    for (int n=0; n<N; n++) {
        for (int kprm=0; kprm<K/Kc; kprm++) {
            cout << "kprm: " << kprm << endl;
            for (int c=0; c<C; c++) {
                cout << "c: " << c << endl;
                while (true) {
                    io_vec = sram.send_input_activation_to_mult_array();
                    io_idx = sram.send_input_idx_to_mult_array();
                    multarray.load_input(io_vec, io_idx);
                    if (io_vec.size() <= 0)
                        break;

                    while (true) {
                        w_vec = wfifo.send_weight_activation_to_mult_array();
                        w_idx = wfifo.send_weight_idx_to_mult_array();
                        if (w_vec.size() <= 0)
                            break;
                        multarray.load_weight(w_vec, w_idx);

                        out = multarray.cartesian_product(tile_num, sram.get_n_idx(), sram.get_c_idx(), wfifo.get_k_idx());
                        for (int p=0; p<out.size(); p++) {
                            out[p].print();
                        }
                        cout << " " << endl;

                        wfifo.incr_i_idx();
                    }

                    wfifo.reset_i_idx();
                    sram.incr_i_idx();
                    multarray.reset_w_cnt();
                }
                sram.reset_i_idx();
                sram.incr_c_idx();
                wfifo.incr_c_idx();
                multarray.reset_io_cnt();
            }
            sram.reset_c_idx();
            wfifo.reset_c_idx();
            wfifo.incr_k_idx();
        }
        wfifo.reset_k_idx();
    }
    return 0;
}






