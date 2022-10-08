#include "../include/scnn/datatypes.h"
#include "../include/scnn/tensor.h"

using namespace SCNN;

// Assuming that w_vec has length F, and ia_vec has length I, with all the relevant information inside each element, 
// iterate through w_vec and ia_vec to find cartesian product of two vectors. Then store result in oa_vec.
// OA_vec mult_array(W_vec w_vec, 
//                 IA_vec ia_vec, 
//                 W_indices w_indices, 
//                 IA_indices ia_indices,
//                 SCNN::ConfigDataflow* cfg_layer,
//                 SCNN::ConfigArch* cfg_arch) {
    
//     // Note that F and I need not be 4: they may be less than 4 as well.
//     OA_vec oa_vec;
//     int F = w_vec.size(); 
//     int I = ia_vec.size();
//     int r_ctr = floor(cfg_layer->get_R() / 2);
//     int s_ctr = floor(cfg_layer->get_S() / 2);

//     for (int f; f < F; f++) {
//         for (int i; i < I; i++) {
//             // Fetch each element from w_vec and ia_vec
//             W_element w_element = w_vec[f];
//             IA_element ia_element = ia_vec[i];

//             // Calculate new data
//             Fmap_t oa_data = w_element.get_data() * ia_element.get_data();

//             // Calculate new idx and determine whether it is valid
//             tensor_4D_idx w_idx = w_element.get_idx();
//             tensor_4D_idx ia_idx = ia_element.get_idx();

//             tensor_4D_idx oa_idx(get<0>(ia_idx), get<0>(w_idx), 0, 0);
//             get<2>(oa_idx) = s_ctr - get<2>(w_idx);
//             get<2>(oa_idx) += get<2>(ia_idx);
//             get<3>(oa_idx) = r_ctr - get<3>(w_idx);
//             get<3>(oa_idx) += get<3>(ia_idx);

//             bool valid;
//             unsigned bank_id;
//             unsigned idx_in_bank;
//             if (get<2>(oa_idx) < 0 || get<3>(oa_idx) < 0) { 
//                 valid = false; 
//                 bank_id = 0;
//                 idx_in_bank = 0;
//             }
//             else {
//                 valid = true;
//                 int sum_of_idx = get<0>(oa_idx) + get<1>(oa_idx) + get<2>(oa_idx) + get<3>(oa_idx);
//                 bank_id = (unsigned int) (sum_of_idx % cfg_arch->get_acc_bank_num());
//                 idx_in_bank = 0;
//             }

//             OA_element oa_element(valid, oa_data, oa_idx, bank_id, idx_in_bank);
//             oa_vec.push_back(oa_element);
//         }
//     }

//     return oa_vec;
// }

// OA_vec 


int main() {
    Tensor4D_IO io(1,3,3,3);
    io.initialize_random(0.7);
    io.print();
    io.compress_IO_sparse();
    IO_buffer iobuffer = io.get_io_buffer();
    IO_indices ioindices = io.get_io_indices();
    for (int i=0; i<iobuffer.size(); i++) {
        for (int j=0; j<iobuffer[i].size(); j++) {
            for (int k=0; k<iobuffer[i][j].size(); k++) {
                iobuffer[i][j][k].print();
            }
            cout << endl;
        }
    }

    for (int i=0; i<ioindices.size(); i++) {
        for (int j=0; j<ioindices[i].size(); j++) {
            for (int k=0; k<ioindices[i][j].size(); k++) {
                cout << ioindices[i][j][k] << " ";
            }
            cout << endl;
        }
    }

    // Tensor4D_W w(3,2,3,3);
    // w.initialize_random(0.5);
    // w.initialize_value(-0.7);
    // w.print();

    return 0;
}






