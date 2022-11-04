#include "../../include/scnn/crossbar.h"

namespace SCNN {

CrossBar::CrossBar(ConfigArch* _cfg_arch, ConfigDataflow* _cfg_layer) {
    cfg_arch = _cfg_arch;
    cfg_layer = _cfg_layer;
    num_port_in = _cfg_arch->get_xbar_in();
    num_port_out = _cfg_arch->get_xbar_out();
    IO_vec empty;
    port_in = empty;
}

void CrossBar::clean() {
    port_in.clear();
}

void CrossBar::receive_port_in(IO_vec _mult_array_input) {
    assert(_mult_array_input.size() <= num_port_in);
    port_in = _mult_array_input;
}

// Note that the length of IO_vec stored in port_in need not be F x I (can be less)
vector<IO_vec> CrossBar::distribute_input_to_output() {
    IO_vec empty;
    vector<IO_vec> port_out(num_port_out, empty);
    for (int i=0; i<port_in.size(); i++) {
        if (!port_in[i].get_valid())
            continue;
        port_in[i].set_idx_in_bank(hash_function_idx_in_bank(port_in[i].get_idx()));
        port_out[hash_function_bank_idx(port_in[i].get_idx())].push_back(port_in[i]);
    }
    return port_out;
}

int CrossBar::get_num_port_in() { return num_port_in; }
int CrossBar::get_num_port_out() { return num_port_out; }
void CrossBar::set_cfg_layer(ConfigDataflow* _cfg_layer) { cfg_layer = _cfg_layer; }

int CrossBar::hash_function_bank_idx(tensor_4D_idx idx) {
    // int sum_of_idx = get<0>(idx) + get<1>(idx) + get<2>(idx) + get<3>(idx);
    // return (int) (sum_of_idx % num_port_out);
    int k = get<1>(idx);
    int h = get<2>(idx);
    int w = get<3>(idx);
    int mult = 373;
    int ret = ((k * mult * mult) + (h * mult) + w) % num_port_out;
    assert(ret >= 0 && ret < num_port_out);
    return ret;
}

int CrossBar::hash_function_idx_in_bank(tensor_4D_idx idx) {
    int k = get<1>(idx);
    int h = get<2>(idx);
    int w = get<3>(idx);
    int mult = max(cfg_layer->get_Orig_H(), cfg_layer->get_Orig_W());
    return (k * mult * mult) + (h * mult) + w;
}

}