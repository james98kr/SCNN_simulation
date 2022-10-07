#include "../../include/scnn/crossbar.h"

namespace SCNN {

CrossBar::CrossBar(SCNN::ConfigArch* _cfg_arch) {
    cfg_arch = _cfg_arch;
    num_port_in = _cfg_arch->get_xbar_in();
    num_port_out = _cfg_arch->get_xbar_out();

    OA_vec new_ia_vec(num_port_in);
    vector<OA_vec> new_oa_vec(num_port_out);
    port_in = new_ia_vec;
    port_out = new_oa_vec;
}

void CrossBar::clean() {
    OA_vec new_ia_vec(num_port_in);
    vector<OA_vec> new_oa_vec(num_port_out);
    port_in = new_ia_vec;
    port_out = new_oa_vec;
}

void CrossBar::receive_port_in(OA_vec _mult_array_input) {
    port_in = _mult_array_input;
    return;
}

// Note that the length of OA_vec stored in port_in need not be F*I (can be less)
void CrossBar::relay_input_to_output() {
    OA_element cur = OA_element();
    for (int i=0; i<port_in.size(); i++) {
        if (!port_in[i].get_valid()) {
            continue;
        }
        cur = port_in[i];
        port_out[cur.get_bank_id()].push_back(cur);
    }
    return;
}

vector<OA_vec> CrossBar::flush_port_out() {
    return port_out;
}

unsigned CrossBar::get_num_port_in() {
    return num_port_in;
}

unsigned CrossBar::get_num_port_out() {
    return num_port_out;
}

}