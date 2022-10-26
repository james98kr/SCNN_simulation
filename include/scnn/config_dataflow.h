#ifndef SCNN_CONFIG_DATAFLOW_H_
#define SCNN_CONFIG_DATAFLOW_H_

#include "common.h"

namespace SCNN {

class ConfigDataflow {

public:
    ConfigDataflow(
        unsigned _N,
        unsigned _K,
        unsigned _Kc,
        unsigned _C,
        unsigned _W, // This is tile W
        unsigned _H, // This is tile H
        unsigned _Orig_W, // This is original W
        unsigned _Orig_H, // This is original H
        unsigned _R,
        unsigned _S, 
        unsigned _PE_Num_W,
        unsigned _PE_Num_H
    );

    // Get
    unsigned get_N();
    unsigned get_K();
    unsigned get_Kc();
    unsigned get_C();
    unsigned get_W();
    unsigned get_H();
    unsigned get_Orig_W();
    unsigned get_Orig_H();
    unsigned get_R();
    unsigned get_S();
    unsigned get_PE_Num_W();
    unsigned get_PE_Num_H();
    vector<int> get_Vec_Tile_W();
    vector<int> get_Vec_Tile_H();

    // Set
    void set_N(unsigned _N);
    void set_K(unsigned _K);
    void set_Kc(unsigned _Kc);
    void set_C(unsigned _C);
    void set_W(unsigned _W);
    void set_H(unsigned _H);
    void set_Orig_W(unsigned _Orig_W);
    void set_Orig_H(unsigned _Orig_H);
    void set_R(unsigned _R);
    void set_S(unsigned _S);
    void set_PE_Num_W(unsigned _PE_Num_W);
    void set_PE_Num_H(unsigned _PE_Num_H);
    void reset_vec_tile();

private:
    unsigned N;     // Batch size
    unsigned K;     // Total number of output channels
    unsigned Kc;    // Number of output channels per group
    unsigned C;     // Number of input channels
    unsigned W;     // IA tile width
    unsigned H;     // IA tile height
    unsigned Orig_W; // IA original width
    unsigned Orig_H; // IA original height
    unsigned R;     // Weight width
    unsigned S;     // Weight height
    unsigned PE_Num_W;  // Number of PE in horizontal axis
    unsigned PE_Num_H;  // Number of PE in vertical axis
    vector<int> Vec_Tile_W;
    vector<int> Vec_Tile_H;
};

}

#endif