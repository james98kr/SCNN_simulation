#ifndef SCNN_CONFIG_PARSER_H_
#define SCNN_CONFIG_PARSER_H_

#include "../scnn/config_arch.h"
#include "../scnn/config_dataflow.h"

namespace SCNN {

class ConfigParser {

public:
    ConfigParser(char* _file_name);
    ConfigArch parse_cfg_arch();
    vector<ConfigDataflow> parse_cfg_layers();
    int get_num_layers();

private:
    char file_name[100];
    int num_layers;
};

}

#endif