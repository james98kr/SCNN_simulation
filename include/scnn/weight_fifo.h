#ifndef SCNN_WEIGHT_FIFO_H_
#define SCNN_WEIGHT_FIFO_H_

#include "datatypes.h"
#include "config_arch.h"
#include "config_dataflow.h"

namespace SCNN {

class WeightFIFO {

public:
    WeightFIFO(ConfigArch* _cfg_arch,
               ConfigDataflow* _cfg_layer);
    void set_w_buffer(W_buffer _w_buffer);
    void set_w_indices(W_indices _w_indices);

    int get_k_idx();
    int get_c_idx();
    int get_i_idx();
    ConfigArch* get_cfg_arch();
    ConfigDataflow* get_cfg_layer();

    void incr_k_idx();
    void incr_c_idx();
    void incr_i_idx();
    void reset_k_idx();
    void reset_c_idx();
    void reset_i_idx();
    void reset_all();
    
    W_vec send_weight_activation_to_mult_array();
    vector<int> send_weight_idx_to_mult_array();

private:
    ConfigArch* cfg_arch;
    ConfigDataflow* cfg_layer;
    int k_idx;
    int c_idx;
    int i_idx;
    W_buffer w_buffer;
    W_indices w_indices;
};

}

#endif