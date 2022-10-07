#include "../../include/scnn/config_dataflow.h"

namespace SCNN {

ConfigDataflow::ConfigDataflow(
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
) {
    N = _N;
    K = _K;
    Kc = _Kc;
    C = _C;
    W = _W;
    H = _H;
    R = _R;
    S = _S; 
    PE_Num_W = _PE_Num_W;
    PE_Num_H = _PE_Num_H;
}

// Get
unsigned ConfigDataflow::get_N() { return N; }
unsigned ConfigDataflow::get_K() { return K; }
unsigned ConfigDataflow::get_Kc() { return Kc; }
unsigned ConfigDataflow::get_C() { return C; }
unsigned ConfigDataflow::get_W() { return W; }
unsigned ConfigDataflow::get_H() { return H; }
unsigned ConfigDataflow::get_R() { return R; }
unsigned ConfigDataflow::get_S() { return S; }
unsigned ConfigDataflow::get_PE_Num_W() { return PE_Num_W; }
unsigned ConfigDataflow::get_PE_Num_H() { return PE_Num_H; }
unsigned ConfigDataflow::get_Tile_W() { return (unsigned int) W / PE_Num_W; }
unsigned ConfigDataflow::get_Tile_H() { return (unsigned int) H / PE_Num_H; }

// Set
void ConfigDataflow::set_N(unsigned _N) { N = _N; }
void ConfigDataflow::set_K(unsigned _K) { K = _K; }
void ConfigDataflow::set_Kc(unsigned _Kc) { Kc = _Kc; }
void ConfigDataflow::set_C(unsigned _C) { C = _C; }
void ConfigDataflow::set_W(unsigned _W) { W = _W; }
void ConfigDataflow::set_H(unsigned _H) { H = _H; }
void ConfigDataflow::set_R(unsigned _R) { R = _R; }
void ConfigDataflow::set_S(unsigned _S) { S = _S; }
void ConfigDataflow::set_PE_Num_W(unsigned _PE_Num_W) { PE_Num_W = _PE_Num_W; }
void ConfigDataflow::set_PE_Num_H(unsigned _PE_Num_H) { PE_Num_H = _PE_Num_H; }

}