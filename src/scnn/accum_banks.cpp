#include "../../include/scnn/accum_banks.h"

namespace SCNN {

AccumulatorBanks::AccumulatorBanks(ConfigArch* _cfg_arch) {
    cfg_arch = _cfg_arch;
    num_banks = _cfg_arch->get_acc_bank_num();
    max_queue_depth = _cfg_arch->get_max_queue_depth();

    for (int i=0; i<num_banks; i++) {
        IO_vec empty;
        queue.push_back(empty);
        banks.push_back(empty);
    }
}

void AccumulatorBanks::clean() {
    for (int i=0; i<banks.size(); i++)
        banks[i].clear();
}

void AccumulatorBanks::receive_accum_inputs(vector<IO_vec> accum_input) {
    for (int i=0; i<queue.size(); i++) {
        if (accum_input[i].size() > 0)
            queue[i].insert(queue[i].end(), accum_input[i].begin(), accum_input[i].end());
    }
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
    for (int i=0; i<num_banks; i++) {
        if (queue[i].size() > 0) {
            insert_one_element_to_bank(queue[i][0], i);
            queue[i].erase(queue[i].begin());
        }
    }
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
int AccumulatorBanks::get_max_queue_depth() { return max_queue_depth; }

int AccumulatorBanks::get_queue_max_len() {
    int maxlen = 0;
    for (int i=0; i<queue.size(); i++) {
        if (queue[i].size() > maxlen)
            maxlen = queue[i].size();
    }
    return maxlen;
}

}