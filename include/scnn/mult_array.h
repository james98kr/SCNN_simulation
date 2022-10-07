#ifndef SCNN_MULT_ARRAY_H_
#define SCNN_MULT_ARRAY_H_

#include "common.h"
#include "datatypes.h"
#include "config_arch.h"
#include "config_dataflow.h"

namespace SCNN {

class MultArray {

public:
    MultArray(SCNN::ConfigArch* _cfg_arch, SCNN::ConfigDataflow* _cfg_layer);

    void clean();

    // calculate
    void load_input_and_weight(W_vec _w_vec, IA_vec _ia_vec);
    void cartesian_product();
    int hash_function(tensor_4D_idx _idx);

    // get
    unsigned get_mult_arr_F();
    unsigned get_mult_arr_I();

    // set
    void set_cfg_arch(SCNN::ConfigArch* _cfg_arch);
    void set_cfg_layer(SCNN::ConfigDataflow* _cfg_layer);

private:
    SCNN::ConfigArch* cfg_arch;
    SCNN::ConfigDataflow* cfg_layer;
    unsigned mult_arr_F;
    unsigned mult_arr_I;

    W_vec w_vec;
    IA_vec ia_vec;
};

}

#endif