#ifndef SCNN_CROSSBAR_H_
#define SCNN_CROSSBAR_H_

#include "common.h"
#include "datatypes.h"
#include "config_arch.h"

namespace SCNN {

class CrossBar {
    
public:
    CrossBar(SCNN::ConfigArch* _cfg_arch);

	void clean();

    void receive_port_in(OA_vec _mult_array_input);
	void relay_input_to_output();
    vector<OA_vec> flush_port_out();
	unsigned get_num_port_in();
	unsigned get_num_port_out();

private:
	// CrossBar config
    SCNN::ConfigArch* cfg_arch;

    // i/o ports
    OA_vec port_in;
    unsigned num_port_in;
    vector<OA_vec> port_out;
    unsigned num_port_out;
};

}

#endif