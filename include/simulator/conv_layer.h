#ifndef SCNN_CONV_LAYER_H_
#define SCNN_CONV_LAYER_H_

#include "../scnn/datatypes.h"
#include "../scnn/tensor.h"
#include "../scnn/config_arch.h"
#include "../scnn/config_dataflow.h"
#include "../scnn/ioram.h"
#include "../scnn/weight_fifo.h"
#include "../scnn/mult_array.h"
#include "../scnn/crossbar.h"
#include "../scnn/accum_banks.h"

namespace SCNN {

class ConvLayer {

public:
    ConvLayer(
        IORAM* _ioram,
        WeightFIFO* _wfifo,
        MultArray* _multarray,
        CrossBar* _crossbar,
        AccumulatorBanks* _accumbanks
    );

    void set_cfg_layer(ConfigDataflow* _cfg_layer);
    Tensor4D_IO convolution(Tensor4D_IO* io, Tensor4D_W* w, int layer_num);

private:
    ConfigDataflow* cfg_layer;

    IORAM* ioram;
    WeightFIFO* wfifo;
    MultArray* multarray;
    CrossBar* crossbar;
    AccumulatorBanks* accumbanks;
};

}

#endif