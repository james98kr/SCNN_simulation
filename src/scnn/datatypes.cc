#include "../../include/scnn/datatypes.h"

namespace SCNN {

// Methods for W_element
W_element::W_element(
    bool _valid,
    Weight_t _data,
    tensor_4D_idx _idx
) {
    valid = _valid;
    data = _data;
    idx = _idx;
}

void W_element::print() { 
    cout << "Valid: " << valid << ", Data: " << data << ", Index: " << \
    get<0>(idx) << " " << get<1>(idx) << " " << get<2>(idx) << " " <<get<3>(idx) << endl; 
}

void W_element::set_valid(bool _valid) { valid = _valid; }
void W_element::set_data(Weight_t _data) { data = _data; }
void W_element::set_idx(tensor_4D_idx _idx) { idx = _idx; }
bool W_element::get_valid() { return valid; }
Weight_t W_element::get_data() { return data; }
tensor_4D_idx W_element::get_idx() { return idx; }

// Methods for IO_element
IO_element::IO_element(
    bool _valid,
    Fmap_t _data,
    tensor_4D_idx _idx
) {
    valid = _valid;
    data = _data;
    idx = _idx;
}

void IO_element::print() { 
    cout << "Valid: " << valid << ", Data: " << data << ", Index: " << \
    get<0>(idx) << " " << get<1>(idx) << " " << get<2>(idx) << " " <<get<3>(idx) << endl; 
}

void IO_element::set_valid(bool _valid) { valid = _valid; }
void IO_element::set_data(Fmap_t _data) { data = _data; }
void IO_element::set_idx(tensor_4D_idx _idx) { idx = _idx; }
bool IO_element::get_valid() { return valid; }
Fmap_t IO_element::get_data() { return data; }
tensor_4D_idx IO_element::get_idx() { return idx; }

} // Namespace SCNN