#ifndef SCNN_TENSOR_H_
#define SCNN_TENSOR_H_

#include "datatypes.h"

namespace SCNN {

class Tensor4D_IO {

public:
    Tensor4D_IO(int _N, int _C, int _H, int _W);
    ~Tensor4D_IO();

    void initialize_random(float sparsity, int min=0, int max=1);
    void initialize_value(Fmap_t init_value);

    void print();

    // compress
    void compress_IO_sparse();

    // get
    int get_N();
    int get_C();
    int get_H();
    int get_W();
    int get_total_element_num();
    tensor_4D_idx get_shape();
    Fmap_t**** get_data();
    IO_buffer get_io_buffer();
    IO_indices get_io_indices();

private:
    int N;
    int C;
    int H;
    int W;

    Fmap_t**** data;
    IO_buffer io_buffer;
    IO_indices io_indices;
};

class Tensor4D_W {

public:
    Tensor4D_W(int _K, int _C, int _S, int _R);
    ~Tensor4D_W();

    void initialize_random(float sparsity, int min=0, int max=1);
    void initialize_value(Weight_t init_value);

    void print();

    // compress
    void compress_W_sparse(int Kc);

    // get
    int get_K();
    int get_C();
    int get_S();
    int get_R();
    int get_total_element_num();
    tensor_4D_idx get_shape();
    Weight_t**** get_data();
    W_buffer get_w_buffer();
    W_indices get_w_indices();

private:
    int K;
    int C;
    int S;
    int R;

    Weight_t**** data;
    W_buffer w_buffer;
    W_indices w_indices;
};

}

#endif