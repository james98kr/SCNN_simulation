#include "../../include/simulator/config_parser.h"

namespace SCNN {

ConfigParser::ConfigParser(char* _file_name) {
    strncpy(file_name, _file_name, sizeof(file_name));
}

ConfigArch ConfigParser::parse_cfg_arch() {
    ifstream cfg_file(file_name);
    assert(("Failed to open config file", cfg_file.is_open()));  
    int I, F, defval;
    ConfigArch cfg_arch = ConfigArch();
    string line;
    string delimiter = ": ";

    // Get value for num_layers
    getline(cfg_file, line);
    line.erase(0, line.find(delimiter) + delimiter.length());
    num_layers = atoi(line.c_str());
    getline(cfg_file, line);

    // Get values for ConfigArch
    getline(cfg_file, line);
    line.erase(0, line.find(delimiter) + delimiter.length());
    I = atoi(line.c_str());
    assert(("I must be greater than 0", I > 0));
    cfg_arch.set_mult_arr_I(I);

    getline(cfg_file, line);
    line.erase(0, line.find(delimiter) + delimiter.length());
    F = atoi(line.c_str());
    assert(("F must be greater than 0", F > 0));
    cfg_arch.set_mult_arr_F(F);

    getline(cfg_file, line);
    line.erase(0, line.find(delimiter) + delimiter.length());
    defval = atoi(line.c_str());
    assert(("defval must be greater than 0", defval > 0));
    cfg_arch.set_xbar_in(I * F);
    cfg_arch.set_xbar_out(I * F * 2);
    cfg_arch.set_acc_bank_num(I * F * 2);
    cfg_arch.set_ioram_sparse_len(defval);
    cfg_arch.set_ioram_idx_len(defval);
    cfg_arch.set_weight_sparse_len(defval);
    cfg_arch.set_weight_idx_len(defval);
    cfg_arch.set_max_queue_depth(defval);

    cfg_file.close();

    return cfg_arch;
}

vector<ConfigDataflow> ConfigParser::parse_cfg_layers() {
    ifstream cfg_file(file_name);
    assert(("Failed to open config file", cfg_file.is_open())); 
    int N, C, Orig_H, Orig_W, K, Kc, S, R, PE_Num_H, PE_Num_W;
    float io_sparsity, w_sparsity;
    vector<ConfigDataflow> cfg_layers;
    string line;
    string delimiter = ": ";

    // Read first 6 lines
    for (int i=0; i<6; i++)
        getline(cfg_file, line);
    
    // Get values for each ConfigDataflow
    for (int layer=0; layer<num_layers; layer++) {
        ConfigDataflow cur_layer = ConfigDataflow();

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        N = atoi(line.c_str());
        assert(("N must be greater than 0", N > 0));
        cur_layer.set_N(N);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        C = atoi(line.c_str());
        assert(("C must be greater than 0", C > 0));
        cur_layer.set_C(C);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        Orig_H = atoi(line.c_str());
        assert(("Orig_H must be greater than 0", Orig_H > 0));
        cur_layer.set_Orig_H(Orig_H);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        Orig_W = atoi(line.c_str());
        assert(("Orig_W must be greater than 0", Orig_W > 0));
        cur_layer.set_Orig_W(Orig_W);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        K = atoi(line.c_str());
        assert(("K must be greater than 0", K > 0));
        cur_layer.set_K(K);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        Kc = atoi(line.c_str());
        assert(("Kc must be greater than 0", Kc > 0));
        cur_layer.set_Kc(Kc);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        S = atoi(line.c_str());
        assert(("S must be greater than 0", S > 0));
        cur_layer.set_S(S);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        R = atoi(line.c_str());
        assert(("R must be greater than 0", R > 0));
        cur_layer.set_R(R);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        PE_Num_H = min(atoi(line.c_str()), Orig_H);
        assert(("PE_Num_H must be greater than 0", PE_Num_H > 0));
        cur_layer.set_PE_Num_H(PE_Num_H);
        cur_layer.set_H(Orig_H / PE_Num_H);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        PE_Num_W = min(atoi(line.c_str()), Orig_W);
        assert(("PE_Num_W must be greater than 0", PE_Num_W > 0));
        cur_layer.set_PE_Num_W(PE_Num_W);
        cur_layer.set_W(Orig_W / PE_Num_W);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        io_sparsity = atof(line.c_str());
        assert(("io_sparsity must be between 0 and 1, inclusive", io_sparsity >= 0 && io_sparsity <= 1));
        cur_layer.set_io_sparsity(io_sparsity);

        getline(cfg_file, line);
        line.erase(0, line.find(delimiter) + delimiter.length());
        w_sparsity = atof(line.c_str());
        assert(("w_sparsity must be between 0 and 1, inclusive", w_sparsity >= 0 && w_sparsity <= 1));
        cur_layer.set_w_sparsity(w_sparsity);

        getline(cfg_file, line);
        cfg_layers.push_back(cur_layer);
    }

    cfg_file.close();

    return cfg_layers;
}

int ConfigParser::get_num_layers() {
    return num_layers;
}

}