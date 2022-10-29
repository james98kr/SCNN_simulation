#include "../../include/scnn/config_arch.h"

namespace SCNN {

ConfigArch::ConfigArch(
    // multiplier array F, I size
    unsigned _mult_arr_F,
    unsigned _mult_arr_I,

    // xbar
    unsigned _xbar_in,
    unsigned _xbar_out,
    
    // SRAM size
    unsigned _ioram_sparse_len,
    unsigned _ioram_idx_len,
    unsigned _weight_sparse_len,
    unsigned _weight_idx_len,

    // Accumulator bank
    unsigned _acc_bank_num,
    unsigned _max_num_elem_per_bank
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

unsigned ConfigArch::get_mult_arr_F() { return mult_arr_F; }
unsigned ConfigArch::get_mult_arr_I() { return mult_arr_I; }
unsigned ConfigArch::get_xbar_in() { return xbar_in; }
unsigned ConfigArch::get_xbar_out() { return xbar_out; }
unsigned ConfigArch::get_ioram_sparse_len() { return ioram_sparse_len; }
unsigned ConfigArch::get_ioram_idx_len() { return ioram_idx_len; }
unsigned ConfigArch::get_weight_sparse_len() { return weight_sparse_len; }
unsigned ConfigArch::get_weight_idx_len() { return weight_idx_len; }
unsigned ConfigArch::get_acc_bank_num() { return acc_bank_num; }
unsigned ConfigArch::get_max_num_elem_per_bank() { return max_num_elem_per_bank; }

} // Namespace SCNN