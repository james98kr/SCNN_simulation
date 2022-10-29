#include "../../include/scnn/accum_banks.h"

namespace SCNN {

AccumulatorBanks::AccumulatorBanks(ConfigArch* _cfg_arch) {
    cfg_arch = _cfg_arch;
    num_banks = _cfg_arch->get_acc_bank_num();
    num_elem_per_bank = _cfg_arch->get_max_num_elem_per_bank();

    for (int i=0; i<num_banks; i++) {
        IO_vec empty;
        banks.push_back(empty);
    }

    ptr = 0;
    finished = false;
}

void AccumulatorBanks::clean() {
    for (int i=0; i<banks.size(); i++)
        banks[i].clear();
    banks.clear();
    ptr = 0;
    finished = false;
}

void AccumulatorBanks::receive_accum_inputs(vector<IO_vec> accum_input) {
    banks = accum_input;
}

void AccumulatorBanks::insert_one_element_to_bank(IO_element elem, int bank_idx) {
    if (banks[bank_idx].empty()) {
        banks[bank_idx].push_back(elem);
        return;
    }

    int low = 0;
    int high = banks[bank_idx].size() - 1;
    int mid = (low + high) / 2;
    Fmap_t target = elem.get_idx_in_bank();
    Fmap_t cmp = banks[bank_idx][mid].get_idx_in_bank();

    while (low <= high) {
        mid = (low + high) / 2;
        cmp = banks[bank_idx][mid].get_idx_in_bank();
        if (cmp == target)
            break;
        else if (cmp < target)
            low = mid + 1;
        else if (cmp > target)
            high = mid - 1;
    }

    if (cmp == target)
        banks[bank_idx][mid].accumulate(elem.get_data());
    else {
        if (cmp < target)
            banks[bank_idx].insert(banks[bank_idx].begin() + (mid + 1), 1, elem);
        else if (cmp > target)
            banks[bank_idx].insert(banks[bank_idx].begin() + mid, 1, elem);
    }
}

void AccumulatorBanks::accumulate_one_cycle() {
    finished = true;
    for (int i=0; i<num_banks; i++) {
        if (ptr < banks[i].size()) {
            finished = false;
            insert_one_element_to_bank(banks[i][ptr], i);
        }
    }
    ptr++;
}

void AccumulatorBanks::flush_to_output(Tensor4D_IO* output_tensor) {
    for (int i=0; i<num_banks; i++) {
        for (int j=0; j<banks[i].size(); j++) {
            output_tensor->accumulate_idx_to_val(banks[i][j].get_data(), banks[i][j].get_idx());
        }
    }
    clean();
}

int AccumulatorBanks::get_num_banks() { return num_banks; }
int AccumulatorBanks::get_num_elem_per_bank() { return num_elem_per_bank; }
bool AccumulatorBanks::get_finished() { return finished; }

}