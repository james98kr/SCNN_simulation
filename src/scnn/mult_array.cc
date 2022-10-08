#include "../../include/scnn/mult_array.h"

namespace SCNN {

MultArray::MultArray(SCNN::ConfigArch* _cfg_arch, SCNN::ConfigDataflow* _cfg_layer) {
    cfg_arch = _cfg_arch;
    cfg_layer = _cfg_layer;
    mult_arr_F = _cfg_arch->get_mult_arr_F();
    mult_arr_I = _cfg_arch->get_mult_arr_I();
}

void MultArray::clean() {
    W_vec new_w_vec;
    IA_vec new_ia_vec;
    w_vec = new_w_vec;
    ia_vec = new_ia_vec;
}

int MultArray::calculate_oa_coordinates(W_element _w_element, IA_element _ia_element) {
    return 0;
}

void MultArray::load_input_and_weight(W_vec _w_vec, IA_vec _ia_vec) {
    w_vec = _w_vec;
    ia_vec = _ia_vec;
}

int MultArray::hash_function(tensor_4D_idx _idx) {
    int sum_of_idx = get<0>(_idx) + get<1>(_idx) + get<2>(_idx) + get<3>(_idx);
    return (unsigned int) (sum_of_idx % cfg_arch->get_acc_bank_num());
}

}





