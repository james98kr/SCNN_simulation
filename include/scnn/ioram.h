#ifndef SCNN_IORAM_H_
#define SCNN_IORAM_H_

#include "datatypes.h"
#include "config_arch.h"

namespace SCNN {

class SparseRAM {

public:
    SparseRAM(ConfigArch* _cfg_arch);
    void set_tile_num(int _tile_num);
    void set_io_buffer(IO_buffer _io_buffer);
    void set_io_indices(IO_indices _io_indices);

    int get_tile_num();
    int get_n_idx();
    int get_c_idx();
    int get_i_idx();
    ConfigArch* get_cfg_arch();

    void incr_n_idx();
    void incr_c_idx();
    void incr_i_idx();
    void reset_c_idx();
    void reset_i_idx();
    void reset_all();

    IO_vec send_input_activation_to_mult_array();
    vector<int> send_input_idx_to_mult_array();

private:
    ConfigArch* cfg_arch;
    int tile_num;
    int n_idx;
    int c_idx;
    int i_idx;
    IO_buffer io_buffer;
    IO_indices io_indices;
};

class IORAM {

public:
    IORAM(SparseRAM* _RAM0, SparseRAM* _RAM1);
    void set_ram0(SparseRAM* _RAM0);
    void set_ram1(SparseRAM* _RAM1);
    void swap_occupied();

    SparseRAM* get_ram0();
    SparseRAM* get_ram1();
    int get_occupied();

private:
    // If occupied == 0, it means RAM0 is occupied. 
    // If occupied == 1, it means RAM1 is occupied.
    // "occupied" means it is used as IA buffer
    int occupied;
    SparseRAM* RAM0;
    SparseRAM* RAM1;
};

}

#endif