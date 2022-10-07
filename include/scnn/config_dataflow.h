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
        unsigned _W,
        unsigned _H,
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
    unsigned get_R();
    unsigned get_S();
    unsigned get_PE_Num_W();
    unsigned get_PE_Num_H();
    unsigned get_Tile_W();
    unsigned get_Tile_H();

    // Set
    void set_N(unsigned _N);
    void set_K(unsigned _K);
    void set_Kc(unsigned _Kc);
    void set_C(unsigned _C);
    void set_W(unsigned _W);
    void set_H(unsigned _H);
    void set_R(unsigned _R);
    void set_S(unsigned _S);
    void set_PE_Num_W(unsigned _PE_Num_W);
    void set_PE_Num_H(unsigned _PE_Num_H);

private:
    unsigned N;     // Batch size
    unsigned K;     // Total number of output channels
    unsigned Kc;    // Number of output channels per group
    unsigned C;     // Number of input channels
    unsigned W;     // IA width
    unsigned H;     // IA height
    unsigned R;     // OA width
    unsigned S;     // OA height
    unsigned PE_Num_W;  // Number of PE in horizontal axis
    unsigned PE_Num_H;  // Number of PE in vertical axis
};

}

#endif