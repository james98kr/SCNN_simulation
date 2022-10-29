#ifndef SCNN_ACCUM_BANKS_H_
#define SCNN_ACCUM_BANKS_H_

#include "tensor.h"
#include "datatypes.h"
#include "config_arch.h"

namespace SCNN {

class AccumulatorBanks {

public:
    AccumulatorBanks(ConfigArch* _cfg_arch);

    void clean();

    void receive_accum_inputs(vector<IO_vec> accum_input);
    void insert_one_element_to_bank(IO_element elem, int bank_idx);
    void accumulate_one_cycle();
    void flush_to_output(Tensor4D_IO* output_tensor);

    // get
    int get_num_banks();
    int get_num_elem_per_bank();
    bool get_finished();

private:
    SCNN::ConfigArch* cfg_arch;

    int num_banks;
    int num_elem_per_bank;
    int ptr;
    bool finished;

    vector<IO_vec> banks;
};
    
}

#endif