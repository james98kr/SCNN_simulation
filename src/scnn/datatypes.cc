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

// Methods for IA_element
IA_element::IA_element(
    bool _valid,
    Fmap_t _data,
    tensor_4D_idx _idx
) {
    valid = _valid;
    data = _data;
    idx = _idx;
}

void IA_element::print() { 
    cout << "Valid: " << valid << ", Data: " << data << ", Index: " << \
    get<0>(idx) << " " << get<1>(idx) << " " << get<2>(idx) << " " <<get<3>(idx) << endl; 
}

void IA_element::set_valid(bool _valid) { valid = _valid; }
void IA_element::set_data(Fmap_t _data) { data = _data; }
void IA_element::set_idx(tensor_4D_idx _idx) { idx = _idx; }
bool IA_element::get_valid() { return valid; }
Fmap_t IA_element::get_data() { return data; }
tensor_4D_idx IA_element::get_idx() { return idx; }

// Methods for OA_element
OA_element::OA_element() {
    valid = false;
    data = 0;
    idx = make_tuple(0,0,0,0);
    bank_id = 0;
    idx_in_bank = 0;
}

OA_element::OA_element(
    bool _valid,
    Fmap_t _data,
    tensor_4D_idx _idx,
    unsigned _bank_id,
    unsigned _idx_in_bank
) {
    valid = _valid;
    data = _data;
    idx = _idx;
    bank_id = _bank_id;
    idx_in_bank = _idx_in_bank;
}

void OA_element::print() { 
    cout << "Valid: " << valid << ", Data: " << data << ", Index: " << \
    get<0>(idx) << " " << get<1>(idx) << " " << get<2>(idx) << " " <<get<3>(idx) << \
    ", Bank ID: " << bank_id << ", Index in Bank: " << idx_in_bank << endl; 
}

void OA_element::set_valid(bool _valid) { valid = _valid; }
void OA_element::set_data(Fmap_t _data) { data = _data; }
void OA_element::set_idx(tensor_4D_idx _idx) { idx = _idx; }
void OA_element::set_bank_id(unsigned _new_id) { bank_id = _new_id; }
void OA_element::set_idx_in_bank(unsigned _new_idx) { idx_in_bank = _new_idx; }

bool OA_element::get_valid() { return valid; }
Fmap_t OA_element::get_data() { return data; }
tensor_4D_idx OA_element::get_idx() { return idx; }
unsigned OA_element::get_bank_id() { return bank_id; }
unsigned OA_element::get_idx_in_bank() { return idx_in_bank; }

} // Namespace SCNN