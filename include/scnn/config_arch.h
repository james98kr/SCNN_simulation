#ifndef SCNN_CONFIG_ARCH_H_
#define SCNN_CONFIG_ARCH_H_

#include "common.h"

namespace SCNN {

class ConfigArch {

public:
    ConfigArch(
        // multiplier array F, I size
        unsigned _mult_arr_F,
        unsigned _mult_arr_I,

        // xbar
        unsigned _xbar_in,
        unsigned _xbar_out,
        
        // SRAM size
        unsigned _iaram_sparse_len,
        unsigned _iaram_idx_len,
        unsigned _oaram_sparse_len,
        unsigned _oaram_idx_len,
        unsigned _weight_sparse_len,
        unsigned _weight_idx_len,

        // Accumulator bank
        unsigned _acc_bank_num,
        unsigned _max_num_elem_per_bank
    );

    unsigned get_mult_arr_F();
    unsigned get_mult_arr_I();

    unsigned get_xbar_in();
    unsigned get_xbar_out();
    
    unsigned get_iaram_sparse_len();
    unsigned get_iaram_idx_len();
    unsigned get_oaram_sparse_len();
    unsigned get_oaram_idx_len();
    unsigned get_weight_sparse_len();
    unsigned get_weight_idx_len();

    unsigned get_acc_bank_num();
    unsigned get_max_num_elem_per_bank();

private:
    // multiplier array F, I size
    unsigned mult_arr_F;
    unsigned mult_arr_I;

    // xbar
    unsigned xbar_in;
    unsigned xbar_out;
    
    // SRAM size
    unsigned iaram_sparse_len;
    unsigned iaram_idx_len;
    unsigned oaram_sparse_len;
    unsigned oaram_idx_len;
    unsigned weight_sparse_len;
    unsigned weight_idx_len;

    // Accumulator bank
    unsigned acc_bank_num;
    unsigned max_num_elem_per_bank;
};

}

#endif