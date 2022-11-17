#ifndef SCNN_CONFIG_ARCH_H_
#define SCNN_CONFIG_ARCH_H_

#include "common.h"

namespace SCNN {

class ConfigArch {

public:
    ConfigArch(
        // multiplier array F, I size
        int _mult_arr_F=0,
        int _mult_arr_I=0,

        // xbar
        int _xbar_in=0,
        int _xbar_out=0,
        
        // SRAM size
        int _ioram_sparse_len=0,
        int _ioram_idx_len=0,
        int _weight_sparse_len=0,
        int _weight_idx_len=0,

        // Accumulator bank
        int _acc_bank_num=0,
        int _max_queue_depth=0
    );

    void print();

    // Get
    int get_mult_arr_F();
    int get_mult_arr_I();

    int get_xbar_in();
    int get_xbar_out();
    
    int get_ioram_sparse_len();
    int get_ioram_idx_len();
    int get_weight_sparse_len();
    int get_weight_idx_len();

    int get_acc_bank_num();
    int get_max_queue_depth();

    // Set
    void set_mult_arr_F(int _mult_arr_F);
    void set_mult_arr_I(int _mult_arr_I);

    void set_xbar_in(int _xbar_in);
    void set_xbar_out(int _xbar_out);
    
    void set_ioram_sparse_len(int _ioram_sparse_len);
    void set_ioram_idx_len(int _ioram_idx_len);
    void set_weight_sparse_len(int _weight_sparse_len);
    void set_weight_idx_len(int _weight_idx_len);

    void set_acc_bank_num(int _acc_bank_num);
    void set_max_queue_depth(int _max_queue_depth);

private:
    // multiplier array F, I size
    int mult_arr_F;
    int mult_arr_I;

    // xbar
    int xbar_in;
    int xbar_out;
    
    // SRAM size
    int ioram_sparse_len;
    int ioram_idx_len;
    int weight_sparse_len;
    int weight_idx_len;

    // Accumulator bank
    int acc_bank_num;
    int max_queue_depth;
};

}

#endif