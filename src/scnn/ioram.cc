#include "../../include/scnn/ioram.h"

namespace SCNN {

SparseRAM::SparseRAM(
    IO_buffer _io_buffer, 
    IO_indices _io_indices, 
    ConfigArch* _cfg_arch, 
    int _tile_num
) {
    cfg_arch = _cfg_arch;
    tile_num = _tile_num;
    io_buffer = _io_buffer;
    io_indices = _io_indices;
    n_idx = 0;
    c_idx = 0;
    i_idx = 0;
    finished = 0;
}

void SparseRAM::set_tile_num(int _tile_num) { tile_num = _tile_num; }
void SparseRAM::set_io_buffer(IO_buffer _io_buffer) { io_buffer = _io_buffer; }
void SparseRAM::set_io_indices(IO_indices _io_indices) { io_indices = _io_indices; }

int SparseRAM::get_tile_num() { return tile_num; }
int SparseRAM::get_n_idx() { return n_idx; }
int SparseRAM::get_c_idx() { return c_idx; }
int SparseRAM::get_i_idx() { return i_idx; }
int SparseRAM::get_finished() { return finished; }
ConfigArch* SparseRAM::get_cfg_arch() { return cfg_arch; }

void SparseRAM::incr_n_idx() { n_idx++; }
void SparseRAM::incr_c_idx() { c_idx++; }
void SparseRAM::incr_i_idx() { i_idx++; }
void SparseRAM::reset_c_idx() { c_idx = 0; }
void SparseRAM::reset_i_idx() { i_idx = 0; }
void SparseRAM::set_finished() { finished = 1; }

IO_vec SparseRAM::send_input_activation_to_mult_array() {
    assert(finished == 0);
    int I = (int) cfg_arch->get_mult_arr_I();
    IO_vec temp = io_buffer[n_idx][c_idx];
    IO_vec activation;
    if ((i_idx+1)*I <= temp.size()) {
        activation = slice(temp, i_idx*I, (i_idx+1)*I);
    }
    else if (i_idx*I <= temp.size() && (i_idx+1)*I > temp.size()) {
        activation = slice(temp, i_idx*I, temp.size());
    }
    else if (i_idx*I > temp.size()) {}
    return activation;
}

vector<int> SparseRAM::send_input_idx_to_mult_array() {
    assert(finished == 0);
    int I = (int) cfg_arch->get_mult_arr_I();
    vector<int> temp = io_indices[n_idx][c_idx];
    vector<int> indices;
    if (((i_idx+1)*I)+1 <= temp.size()) {
        indices = slice(temp, (i_idx*I)+1, ((i_idx+1)*I)+1);
    }
    else if ((i_idx*I)+1 <= temp.size() && ((i_idx+1)*I)+1 > temp.size()) {
        indices = slice(temp, (i_idx*I)+1, temp.size());
    }
    else if ((i_idx*I)+1 > temp.size()) {}
    return indices;
}

/* ------------------------------------------------------------------------------------------------------ */

IORAM::IORAM(SparseRAM* _RAM0, SparseRAM* _RAM1) {
    // By default, occupied is set to 0 when initialized
    occupied = 0;
    RAM0 = _RAM0;
    RAM1 = _RAM1;
}

void IORAM::set_ram0(SparseRAM* _RAM0) { RAM0 = _RAM0; }
void IORAM::set_ram1(SparseRAM* _RAM1) { RAM1 = _RAM1; }
void IORAM::swap_occupied() { occupied = !occupied; }
SparseRAM* IORAM::get_ram0() { return RAM0; }
SparseRAM* IORAM::get_ram1() { return RAM1; }
int IORAM::get_occupied() { return occupied; }

}