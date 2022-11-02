#ifndef SCNN_CROSSBAR_H_
#define SCNN_CROSSBAR_H_

#include "common.h"
#include "datatypes.h"
#include "config_arch.h"
#include "config_dataflow.h"

namespace SCNN {

class CrossBar {
    
public:
    CrossBar(ConfigArch* _cfg_arch, ConfigDataflow* _cfg_layer);

	void clean();

    void receive_port_in(IO_vec _mult_array_input);
	vector<IO_vec> distribute_input_to_output();
	int get_num_port_in();
	int get_num_port_out();

    int hash_function_bank_idx(tensor_4D_idx idx);
    int hash_function_idx_in_bank(tensor_4D_idx idx);

private:
	// CrossBar config
    ConfigArch* cfg_arch;
    ConfigDataflow* cfg_layer;

    // I/O ports
    IO_vec port_in;
    int num_port_in;
    int num_port_out;
};

}

#endif