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
    int H = 5;
    int W = 5;
    int K = 8;
    int Kc = 2;
    int S = 3;
    int R = 3;
    int PE_Num_W = 1;
    int PE_Num_H = 1;
    int I = 4;
    int F = 4;

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

    SparseRAM sram = SparseRAM(iobuffer, ioindices, &arch, 0);
    WeightFIFO wfifo = WeightFIFO

    IO_vec out;
    vector<int> idx;

    for (int j=0; j<10; j++) {
        out = sram.send_input_activation_to_mult_array();
        idx = sram.send_input_idx_to_mult_array();
        for (int i=0; i<out.size(); i++) {
            out[i].print();
            cout << idx[i] << endl;
        }
        sram.incr_i_idx();
    }
    sram.incr_c_idx();
    sram.reset_i_idx();
    cout << " " << endl;

    for (int j=0; j<10; j++) {
        out = sram.send_input_activation_to_mult_array();
        idx = sram.send_input_idx_to_mult_array();
        for (int i=0; i<out.size(); i++) {
            out[i].print();
            cout << idx[i] << endl;
        }
        sram.incr_i_idx();
    }





    return 0;
}






