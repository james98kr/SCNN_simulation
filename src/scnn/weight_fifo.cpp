#include "../../include/scnn/weight_fifo.h"

namespace SCNN {

WeightFIFO::WeightFIFO(ConfigArch* _cfg_arch) {
    cfg_arch = _cfg_arch;
    k_idx = 0;
    c_idx = 0;
    i_idx = 0;
}

void WeightFIFO::set_w_buffer(W_buffer _w_buffer) { w_buffer = _w_buffer; }
void WeightFIFO::set_w_indices(W_indices _w_indices) { w_indices = _w_indices; }

int WeightFIFO::get_k_idx() { return k_idx; }
int WeightFIFO::get_c_idx() { return c_idx; }
int WeightFIFO::get_i_idx() { return i_idx; }
ConfigArch* WeightFIFO::get_cfg_arch() { return cfg_arch; }

void WeightFIFO::incr_k_idx() { k_idx++; }
void WeightFIFO::incr_c_idx() { c_idx++; }
void WeightFIFO::incr_i_idx() { i_idx++; }
void WeightFIFO::reset_k_idx() { k_idx = 0; }
void WeightFIFO::reset_c_idx() { c_idx = 0; }
void WeightFIFO::reset_i_idx() { i_idx = 0; }
void WeightFIFO::reset_all() {
    i_idx = 0;
    c_idx = 0;
    k_idx = 0;
}

W_vec WeightFIFO::send_weight_activation_to_mult_array() {
    int F = (int) cfg_arch->get_mult_arr_F();
    W_vec temp = w_buffer[k_idx][c_idx];
    W_vec weight;
    if ((i_idx+1)*F <= temp.size()) {
        weight = slice(temp, i_idx*F, (i_idx+1)*F);
    }
    else if (i_idx*F <= temp.size() && (i_idx+1)*F > temp.size()) {
        weight = slice(temp, i_idx*F, temp.size());
    }
    else if (i_idx*F > temp.size()) {}
    return weight;
}

vector<int> WeightFIFO::send_weight_idx_to_mult_array() {
    int F = (int) cfg_arch->get_mult_arr_F();
    vector<int> temp = w_indices[k_idx][c_idx];
    vector<int> indices;
    if (((i_idx+1)*F)+1 <= temp.size()) {
        indices = slice(temp, (i_idx*F)+1, ((i_idx+1)*F)+1);
    }
    else if ((i_idx*F)+1 <= temp.size() && ((i_idx+1)*F)+1 > temp.size()) {
        indices = slice(temp, (i_idx*F)+1, temp.size());
    }
    else if ((i_idx*F)+1 > temp.size()) {}
    return indices;
}

}