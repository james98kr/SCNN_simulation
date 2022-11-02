#ifndef SCNN_CONFIG_DATAFLOW_H_
#define SCNN_CONFIG_DATAFLOW_H_

#include "common.h"

namespace SCNN {

class ConfigDataflow {

public:
    ConfigDataflow(
        int _N=0,
        int _K=0,
        int _Kc=0,
        int _C=0,
        int _W=0, // This is tile W
        int _H=0, // This is tile H
        int _Orig_W=0, // This is original W
        int _Orig_H=0, // This is original H
        int _R=0,
        int _S=0, 
        int _PE_Num_W=1,
        int _PE_Num_H=1,
        float _io_sparsity=0,
        float _w_sparsity=0
    );

    void print(int layer_num);

    // Get
    int get_N();
    int get_K();
    int get_Kc();
    int get_C();
    int get_W();
    int get_H();
    int get_Orig_W();
    int get_Orig_H();
    int get_R();
    int get_S();
    int get_PE_Num_W();
    int get_PE_Num_H();
    float get_io_sparsity();
    float get_w_sparsity();
    vector<int> get_Vec_Tile_W();
    vector<int> get_Vec_Tile_H();

    // Set
    void set_N(int _N);
    void set_K(int _K);
    void set_Kc(int _Kc);
    void set_C(int _C);
    void set_W(int _W);
    void set_H(int _H);
    void set_Orig_W(int _Orig_W);
    void set_Orig_H(int _Orig_H);
    void set_R(int _R);
    void set_S(int _S);
    void set_PE_Num_W(int _PE_Num_W);
    void set_PE_Num_H(int _PE_Num_H);
    void set_io_sparsity(float _io_sparsity);
    void set_w_sparsity(float _w_sparsity);
    void reset_vec_tile();

private:
    int N;     // Batch size
    int K;     // Total number of output channels
    int Kc;    // Number of output channels per group
    int C;     // Number of input channels
    int W;     // IA tile width
    int H;     // IA tile height
    int Orig_W; // IA original width
    int Orig_H; // IA original height
    int R;     // Weight width
    int S;     // Weight height
    int PE_Num_W;  // Number of PE in horizontal axis
    int PE_Num_H;  // Number of PE in vertical axis
    vector<int> Vec_Tile_W;
    vector<int> Vec_Tile_H;
    float io_sparsity;
    float w_sparsity;
};

}

#endif