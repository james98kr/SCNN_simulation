#include "../../include/scnn/mult_array.h"

namespace SCNN {

MultArray::MultArray(ConfigArch* _cfg_arch, ConfigDataflow* _cfg_layer) {
    cfg_layer = _cfg_layer;
    io_cnt = 0;
    w_cnt = 0;
    vector<int> v1(_cfg_arch->get_mult_arr_I());
    vector<int> v2(_cfg_arch->get_mult_arr_F());
    io_idx = v1;
    w_idx = v2;
    io_reset_flag = 1;
    w_reset_flag = 1;
}

void MultArray::clean() {
    W_vec new_w_vec;
    IO_vec new_io_vec;
    w_vec = new_w_vec;
    io_vec = new_io_vec;
    io_cnt = 0;
    w_cnt = 0;
}

void MultArray::load_input(IO_vec _io_vec, vector<int> _io_idx) {
    if (io_reset_flag == 0) { 
        for (int i=0; i<io_idx.size(); i++) {
            io_cnt += io_idx[i];
            io_cnt++;
        }
    }
    else {
        io_reset_flag = 0;
    }
    io_vec = _io_vec;
    io_idx = _io_idx;
}

void MultArray::load_weight(W_vec _w_vec, vector<int> _w_idx) {
    if (w_reset_flag == 0) {
        for (int i=0; i<w_idx.size(); i++) {
            w_cnt += w_idx[i];
            w_cnt++;
        }
    }
    else {
        w_reset_flag = 0;
    }
    w_vec = _w_vec;
    w_idx = _w_idx;
}

IO_vec MultArray::cartesian_product(int tile_num, int n_idx, int c_idx, int k_idx) {
    IO_vec result;
    vector<int> vec_tile_w = cfg_layer->get_Vec_Tile_W();
    vector<int> vec_tile_h = cfg_layer->get_Vec_Tile_H();
    IO_element io_element(true, 0, make_tuple(0,0,0,0));
    W_element w_element(true, 0, make_tuple(0,0,0,0));
    int H = (int) cfg_layer->get_H();
    int W = (int) cfg_layer->get_W();
    int input_n, input_c, input_h, input_w, tile_h, tile_w;
    int S = (int) cfg_layer->get_S();
    int R = (int) cfg_layer->get_R();
    int weight_k, weight_c, weight_s, weight_r;
    int io_cnt_backup, w_cnt_backup;

    io_cnt_backup = io_cnt;
    w_cnt_backup = w_cnt;

    for (int i=0; i < io_vec.size(); i++) {
        // Fetch one input element
        io_element = io_vec[i];

        // Calculate input element idx
        io_cnt += io_idx[i];
        tile_h = tile_num / vec_tile_w.size();
        tile_w = tile_num % vec_tile_w.size();
        input_n = n_idx;
        input_c = c_idx;
        input_h = io_cnt / W;
        for (int a=0; a<tile_h; a++) {
            input_h += vec_tile_h[a];
        }
        input_w = io_cnt % W;
        for (int b=0; b<tile_w; b++) {
            input_w += vec_tile_w[b];
        }
        io_cnt++;
        
        tensor_4D_idx input_idx = make_tuple(input_n, input_c, input_h, input_w);
        tensor_4D_idx gt_input_idx = io_element.get_idx();
        assert(get<0>(input_idx) == get<0>(gt_input_idx) && 
               get<1>(input_idx) == get<1>(gt_input_idx) && 
               get<2>(input_idx) == get<2>(gt_input_idx) && 
               get<3>(input_idx) == get<3>(gt_input_idx));

        for (int f=0; f < w_vec.size(); f++) {
            // Fetch one weight element
            w_element = w_vec[f];

            // Calculate weight element idx
            w_cnt += w_idx[f];
            weight_k = (k_idx * cfg_layer->get_Kc()) + (w_cnt / (R * S));
            weight_c = c_idx;
            weight_s = (w_cnt % (R * S)) / R;
            weight_r = (w_cnt % (R * S)) % R;
            w_cnt++;
            tensor_4D_idx weight_idx = make_tuple(weight_k, weight_c, weight_s, weight_r);
            tensor_4D_idx gt_weight_idx = w_element.get_idx();
            assert(get<0>(weight_idx) == get<0>(gt_weight_idx) && 
                   get<1>(weight_idx) == get<1>(gt_weight_idx) && 
                   get<2>(weight_idx) == get<2>(gt_weight_idx) && 
                   get<3>(weight_idx) == get<3>(gt_weight_idx));

            // Calculate new data and idx & Create new output element
            bool valid = true;
            Fmap_t oa_data = io_element.get_data() * w_element.get_data();
            tensor_4D_idx oa_idx = calculate_oa_coordinates(input_idx, weight_idx);
            if (get<2>(oa_idx) < 0 || get<3>(oa_idx) < 0 || get<2>(oa_idx) >= cfg_layer->get_Orig_H() || get<3>(oa_idx) >= cfg_layer->get_Orig_W() ) { valid = false; }
            IO_element new_element(valid, oa_data, oa_idx);

            // Push into resulting IO_vec
            result.push_back(new_element);
        }
        w_cnt = w_cnt_backup;
    }
    io_cnt = io_cnt_backup;
    return result;
}

tensor_4D_idx MultArray::calculate_oa_coordinates(tensor_4D_idx input_idx, tensor_4D_idx weight_idx) {
    int s_ctr = floor(cfg_layer->get_S() / 2);
    int r_ctr = floor(cfg_layer->get_R() / 2);
    tensor_4D_idx oa_idx = make_tuple(get<0>(input_idx), get<0>(weight_idx), 0, 0);

    get<2>(oa_idx) = s_ctr - get<2>(weight_idx);
    get<2>(oa_idx) += get<2>(input_idx);
    get<3>(oa_idx) = r_ctr - get<3>(weight_idx);
    get<3>(oa_idx) += get<3>(input_idx);

    return oa_idx;
}

void MultArray::set_cfg_layer(ConfigDataflow* _cfg_layer) { cfg_layer = _cfg_layer; }
void MultArray::reset_io_cnt() { io_cnt = 0; io_reset_flag = 1; }
void MultArray::reset_w_cnt() { w_cnt = 0; w_reset_flag = 1; }

}