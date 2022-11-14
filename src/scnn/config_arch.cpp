#include "../../include/scnn/config_arch.h"

namespace SCNN {

ConfigArch::ConfigArch(
    // multiplier array F, I size
    int _mult_arr_F,
    int _mult_arr_I,

    // xbar
    int _xbar_in,
    int _xbar_out,
    
    // SRAM size
    int _ioram_sparse_len,
    int _ioram_idx_len,
    int _weight_sparse_len,
    int _weight_idx_len,

    // Accumulator bank
    int _acc_bank_num,
    int _max_num_elem_per_bank
) {
    mult_arr_F = _mult_arr_F;
    mult_arr_I = _mult_arr_I;

    xbar_in = _xbar_in;
    xbar_out = _xbar_out;

    ioram_sparse_len = _ioram_sparse_len;
    ioram_idx_len = _ioram_idx_len;
    weight_sparse_len = _weight_sparse_len;
    weight_idx_len = _weight_idx_len;

    acc_bank_num = _acc_bank_num;
    max_num_elem_per_bank = _max_num_elem_per_bank;
}

void ConfigArch::print() {
    cout << "" << endl;
    cout << "################# Configurations for SCNN Architecture #################" << endl;
    cout << "Multiplier array size (F, I): (" << mult_arr_F << ", " << mult_arr_I << ")" << endl;
    cout << "Crossbar port_in: " << xbar_in << endl;
    cout << "Crossbar port_out: " << xbar_out << endl;
    cout << "Accumulator bank number: " << acc_bank_num << endl;
    cout << "########################################################################" << endl;
    cout << "" << endl;
}

int ConfigArch::get_mult_arr_F() { return mult_arr_F; }
int ConfigArch::get_mult_arr_I() { return mult_arr_I; }
int ConfigArch::get_xbar_in() { return xbar_in; }
int ConfigArch::get_xbar_out() { return xbar_out; }
int ConfigArch::get_ioram_sparse_len() { return ioram_sparse_len; }
int ConfigArch::get_ioram_idx_len() { return ioram_idx_len; }
int ConfigArch::get_weight_sparse_len() { return weight_sparse_len; }
int ConfigArch::get_weight_idx_len() { return weight_idx_len; }
int ConfigArch::get_acc_bank_num() { return acc_bank_num; }
int ConfigArch::get_max_num_elem_per_bank() { return max_num_elem_per_bank; }

void ConfigArch::set_mult_arr_F(int _mult_arr_F) { mult_arr_F = _mult_arr_F; }
void ConfigArch::set_mult_arr_I(int _mult_arr_I) { mult_arr_I = _mult_arr_I; }
void ConfigArch::set_xbar_in(int _xbar_in) { xbar_in = _xbar_in; }
void ConfigArch::set_xbar_out(int _xbar_out) { xbar_out = _xbar_out; }
void ConfigArch::set_ioram_sparse_len(int _ioram_sparse_len) { ioram_sparse_len = _ioram_sparse_len; }
void ConfigArch::set_ioram_idx_len(int _ioram_idx_len) { ioram_idx_len = _ioram_idx_len; }
void ConfigArch::set_weight_sparse_len(int _weight_sparse_len) { weight_sparse_len = _weight_sparse_len; }
void ConfigArch::set_weight_idx_len(int _weight_idx_len) { weight_idx_len = _weight_idx_len; }
void ConfigArch::set_acc_bank_num(int _acc_bank_num) { acc_bank_num = _acc_bank_num; }
void ConfigArch::set_max_num_elem_per_bank(int _max_num_elem_per_bank) { max_num_elem_per_bank = _max_num_elem_per_bank; }

} // Namespace SCNN