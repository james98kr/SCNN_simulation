#include "../include/scnn/golden_model.h"
#include "../include/simulator/config_parser.h"
#include "../include/simulator/conv_layer.h"

using namespace SCNN;

int main(int argc, char** argv) {
    // Parse YAML file for configuration
    assert(("Need to specify config file path", argc >= 2));
    ConfigParser configparser = ConfigParser(argv[1]);
    ConfigArch arch = configparser.parse_cfg_arch();
    vector<ConfigDataflow> vec_layers = configparser.parse_cfg_layers();
    ConfigDataflow dummy_layer = ConfigDataflow();
    arch.print();

    // Create all modules for SCNN
    SparseRAM sram0 = SparseRAM(&arch);
    SparseRAM sram1 = SparseRAM(&arch);
    IORAM ioram = IORAM(&sram0, &sram1);
    WeightFIFO wfifo = WeightFIFO(&arch);
    MultArray multarray = MultArray(&arch, &dummy_layer);
    CrossBar crossbar = CrossBar(&arch, &dummy_layer);
    AccumulatorBanks accumbanks = AccumulatorBanks(&arch);

    // Create ConvLayer
    ConvLayer convlayer(
        &ioram,
        &wfifo,
        &multarray,
        &crossbar,
        &accumbanks
    );

    for (int layer=0; layer<configparser.get_num_layers(); layer++) {
        convlayer.set_cfg_layer(&vec_layers[layer]);
        vec_layers[layer].print(layer);

        int N = vec_layers[layer].get_N();
        int C = vec_layers[layer].get_C();
        int Orig_H = vec_layers[layer].get_Orig_H();
        int Orig_W = vec_layers[layer].get_Orig_W();
        int K = vec_layers[layer].get_K();
        int S = vec_layers[layer].get_S();
        int R = vec_layers[layer].get_R();

        Tensor4D_W w(K,C,S,R);
        Tensor4D_IO io(N,C,Orig_H,Orig_W);
        
        Tensor4D_IO final = convlayer.convolution(&io, &w, layer);

        // Validation using golden conv model
        GoldenConvModel goldenconvmodel = GoldenConvModel(&io, &w);
        goldenconvmodel.golden_convolution();
        goldenconvmodel.validation(&final, layer);
    }
    cout << "------------------------------------------------------------------------" << endl;

    return 0;
}