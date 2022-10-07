#ifndef SCNN_ACCUM_BANKS_H_
#define SCNN_ACCUM_BANKS_H_

#include "common.h"
#include "datatypes.h"
#include "config_arch.h"

namespace SCNN {

class AccumulatorBanks {

public:
    AccumulatorBanks(SCNN::ConfigArch* cfg_arch);

    void clean();

    // get
    vector<OA_vec>* banks();
    unsigned ptr_active_bank();
    unsigned num_banks();
    unsigned num_elem_per_bank();

private:
    SCNN::ConfigArch* arch_cfg;

    unsigned num_banks;
    unsigned num_elem_per_bank;
    unsigned ptr_active_bank;

    vector<OA_vec> banks;
};
    
}

#endif