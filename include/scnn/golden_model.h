#ifndef SCNN_GOLDEN_MODEL_H_
#define SCNN_GOLDEN_MODEL_H_

#include "tensor.h"

namespace SCNN {

class GoldenConvModel {

public:
    GoldenConvModel(Tensor4D_IO* _tensor_input, Tensor4D_W* _tensor_weight);
    ~GoldenConvModel();
    void golden_convolution();
    bool validation(Tensor4D_IO* my_ouptut);

private:
    Tensor4D_IO* tensor_input;
    Tensor4D_W* tensor_weight;

    Fmap_t**** ground_truth;
    float epsilon;

    int N;
    int C;
    int H;
    int W;
    int K;
    int S;
    int R;
};

}

#endif