#include "../../include/scnn/golden_model.h"

namespace SCNN {

GoldenConvModel::GoldenConvModel(Tensor4D_IO* _tensor_input, Tensor4D_W* _tensor_weight) {
    tensor_input = _tensor_input;
    tensor_weight = _tensor_weight;

    N = tensor_input->get_N();
    C = tensor_input->get_C();
    H = tensor_input->get_H();
    W = tensor_input->get_W();
    K = tensor_weight->get_K();
    S = tensor_weight->get_S();
    R = tensor_weight->get_R();

    Fmap_t**** _ground_truth = new Fmap_t***[N];
    for (int n=0; n<N; n++) {
        _ground_truth[n] = new Fmap_t**[K];
        for (int k=0; k<K; k++) {
            _ground_truth[n][k] = new Fmap_t*[H];
            for (int h=0; h<H; h++) {
                _ground_truth[n][k][h] = new Fmap_t[W]();
            }
        }
    }

    ground_truth = _ground_truth;
    epsilon = 1e-4;
}

GoldenConvModel::~GoldenConvModel() {
    for (int n=0; n<N; n++) {
        for (int k=0; k<K; k++) {
            for (int h=0; h<H; h++) {
                delete[] ground_truth[n][k][h];
            }
            delete[] ground_truth[n][k];
        }
        delete[] ground_truth[n];
    }
    delete[] ground_truth;
}

void GoldenConvModel::golden_convolution() {
    Fmap_t**** inputdata = tensor_input->get_data();
    Weight_t**** weightdata = tensor_weight->get_data();
    int h_off = S / 2;
    int w_off = R / 2;

    cout << "Performing golden convolution..." << endl;
    for (int n=0; n<N; n++) {
        for (int k=0; k<K; k++) {
            for (int c=0; c<C; c++) {
                for (int h=0; h<H; h++) {
                    for (int w=0; w<W; w++) {
                        for (int s=0; s<S; s++) {
                            for (int r=0; r<R; r++) {
                                if (h+s-h_off < 0 || h+s-h_off >= H || w+r-w_off < 0 || w+r-w_off >= W)
                                    continue;
                                ground_truth[n][k][h][w] += inputdata[n][c][h+s-h_off][w+r-w_off] * weightdata[k][c][s][r];
                            }
                        }
                    }
                }
            }
        }
    }
}

bool GoldenConvModel::validation(Tensor4D_IO* my_output, int layer_num) {
    cout << "Performing validation for layer " << layer_num << "..." << endl;
    Fmap_t**** my_data = my_output->get_data();
    bool ret = true;

    for (int n=0; n<N; n++) {
        for (int k=0; k<K; k++) {
            for (int h=0; h<H; h++) {
                for (int w=0; w<W; w++) {
                    if (abs(my_data[n][k][h][w] - ground_truth[n][k][h][w]) > epsilon) {
                        ret = false;
                    }
                    
                }
            }
        }
    }

    if (!ret) {
        cout << "Validation Failed: Incorrect Model" << endl;
        assert(ret);
    }
    cout << "*** Validation Complete: Output correct for layer " << layer_num << "! ***" << endl;
    return ret;
}

}