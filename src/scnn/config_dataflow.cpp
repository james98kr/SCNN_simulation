#include "../../include/scnn/config_dataflow.h"

namespace SCNN {

ConfigDataflow::ConfigDataflow(
    int _N,
    int _K,
    int _Kc,
    int _C,
    int _W,
    int _H,
    int _Orig_W,
    int _Orig_H,
    int _R,
    int _S, 
    int _PE_Num_W,
    int _PE_Num_H,
    float _io_sparsity,
    float _w_sparsity
) {
    N = _N;
    K = _K;
    Kc = _Kc;
    C = _C;
    W = _W;
    H = _H;
    Orig_W = _Orig_W;
    Orig_H = _Orig_H;
    R = _R;
    S = _S; 
    PE_Num_W = _PE_Num_W;
    PE_Num_H = _PE_Num_H;
    io_sparsity = _io_sparsity;
    w_sparsity = _w_sparsity;
    reset_vec_tile();
}

void ConfigDataflow::print(int layer_num) {
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Configurations for layer " << layer_num << endl;
    cout << "- Input activation shape (N, C, H, W): (" << N << ", " << C << ", " << Orig_H << ", " << Orig_W << ")" << endl;
    cout << "- Weight shape (K, C, S, R): (" << K << ", " << C << ", " << S << ", " << R << ")" << endl;
    cout << "- Temporal PE config (PE_Num_H, PE_Num_W): (" << PE_Num_H << ", " << PE_Num_W << ")" << endl;
    cout << "- Kc: " << Kc << endl;
    cout << "- Input activation sparsity: " << io_sparsity << endl;
    cout << "- Weight sparsity: " << w_sparsity << endl;
    cout << "" << endl;
}

// Get
int ConfigDataflow::get_N() { return N; }
int ConfigDataflow::get_K() { return K; }
int ConfigDataflow::get_Kc() { return Kc; }
int ConfigDataflow::get_C() { return C; }
int ConfigDataflow::get_W() { return W; }
int ConfigDataflow::get_H() { return H; }
int ConfigDataflow::get_Orig_W() { return Orig_W; }
int ConfigDataflow::get_Orig_H() { return Orig_H; }
int ConfigDataflow::get_R() { return R; }
int ConfigDataflow::get_S() { return S; }
int ConfigDataflow::get_PE_Num_W() { return PE_Num_W; }
int ConfigDataflow::get_PE_Num_H() { return PE_Num_H; }
float ConfigDataflow::get_io_sparsity() { return io_sparsity; };
float ConfigDataflow::get_w_sparsity() { return w_sparsity; };
vector<int> ConfigDataflow::get_Vec_Tile_W() { return Vec_Tile_W; }
vector<int> ConfigDataflow::get_Vec_Tile_H() { return Vec_Tile_H; }

// Set
void ConfigDataflow::set_N(int _N) { N = _N; }
void ConfigDataflow::set_K(int _K) { K = _K; }
void ConfigDataflow::set_Kc(int _Kc) { Kc = _Kc; }
void ConfigDataflow::set_C(int _C) { C = _C; }
void ConfigDataflow::set_W(int _W) { W = _W; }
void ConfigDataflow::set_H(int _H) { H = _H; }
void ConfigDataflow::set_Orig_W(int _Orig_W) {
    Orig_W = _Orig_W;
    reset_vec_tile();
}
void ConfigDataflow::set_Orig_H(int _Orig_H) {
    Orig_H = _Orig_H;
    reset_vec_tile();
}
void ConfigDataflow::set_R(int _R) { R = _R; }
void ConfigDataflow::set_S(int _S) { S = _S; }
void ConfigDataflow::set_PE_Num_W(int _PE_Num_W) { 
    PE_Num_W = _PE_Num_W; 
    reset_vec_tile();
}
void ConfigDataflow::set_PE_Num_H(int _PE_Num_H) { 
    PE_Num_H = _PE_Num_H; 
    reset_vec_tile();
}
void ConfigDataflow::set_io_sparsity(float _io_sparsity) { io_sparsity = _io_sparsity; }
void ConfigDataflow::set_w_sparsity(float _w_sparsity) { w_sparsity = _w_sparsity; }
void ConfigDataflow::reset_vec_tile() {
    // Find Vec_Tile_W
    int average_w = (int) Orig_W / PE_Num_W;
    int remainder_w = (int) Orig_W % PE_Num_W;
    vector<int> new_vec_tile_w(PE_Num_W, average_w);
    for (int i=0; i<remainder_w; i++) {
        new_vec_tile_w[i]++;
    }
    Vec_Tile_W = new_vec_tile_w;

    // Find Vec_Tile_H
    int average_h = (int) Orig_H / PE_Num_H;
    int remainder_h = (int) Orig_H % PE_Num_H;
    vector<int> new_vec_tile_h(PE_Num_H, average_h);
    for (int i=0; i<remainder_h; i++) {
        new_vec_tile_h[i]++;
    }
    Vec_Tile_H = new_vec_tile_h;
}

}