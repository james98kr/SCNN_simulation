#ifndef SCNN_MULT_ARRAY_H_
#define SCNN_MULT_ARRAY_H_

#include "datatypes.h"
#include "config_arch.h"
#include "config_dataflow.h"

namespace SCNN {

class MultArray {

public:
    MultArray(ConfigArch* _cfg_arch, ConfigDataflow* _cfg_layer);

    void clean();

    // calculate
    void load_input(IO_vec _io_vec, vector<int> _io_idx);
    void load_weight(W_vec _w_vec, vector<int> _w_idx);
    IO_vec cartesian_product(int tile_num, int n_idx, int c_idx, int k_idx);
    tensor_4D_idx calculate_oa_coordinates(tensor_4D_idx input_idx, tensor_4D_idx weight_idx);

    // set
    void set_cfg_layer(ConfigDataflow* _cfg_layer);
    void reset_io_cnt();
    void reset_w_cnt();

private:
    ConfigDataflow* cfg_layer;

    int io_cnt;
    int w_cnt;
    int io_reset_flag;
    int w_reset_flag;

    W_vec w_vec;
    vector<int> w_idx;
    IO_vec io_vec;
    vector<int> io_idx;
};

}

#endif