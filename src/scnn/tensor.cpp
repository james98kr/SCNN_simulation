#include "../../include/scnn/tensor.h"

namespace SCNN {

Tensor4D_IO::Tensor4D_IO(int _N, int _C, int _H, int _W) {
    assert(_N > 0 && _C > 0 && _H > 0 && _W > 0);
    N = _N;
    C = _C;
    H = _H;
    W = _W;

    Fmap_t**** _data = new Fmap_t***[_N];
    for (int n=0; n<_N; n++) {
        _data[n] = new Fmap_t**[_C];
        assert(_data[n]);
        for (int c=0; c<_C; c++) {
            _data[n][c] = new Fmap_t*[_H];
            assert(_data[n][c]);
            for (int h=0; h<_H; h++) {
                _data[n][c][h] = new Fmap_t[_W];
                assert(_data[n][c][h]);
            }
        }
    }
    data = _data;
}

Tensor4D_IO::~Tensor4D_IO() {
    for (int n=0; n<N; n++) {
        for (int c=0; c<C; c++) {
            for (int h=0; h<H; h++) {
                delete[] data[n][c][h];
            }
            delete[] data[n][c];
        }
        delete[] data[n];
    }
    delete[] data;
}

void Tensor4D_IO::initialize_random(float sparsity, int min, int max) {
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<Fmap_t> distr(min, max);

    int cnt = 0;
    int num_zeros = floor(N * C * H * W * sparsity);
    int num_ones = (N * C * H * W) - num_zeros;
    vector<int> mask(num_zeros, 0);
    for (int i=0; i<num_ones; i++) { mask.push_back(1); }
    shuffle(begin(mask), end(mask), eng);

    for (int n=0; n<N; n++) {
        for (int c=0; c<C; c++) {
            for (int h=0; h<H; h++) {
                for (int w=0; w<W; w++) {
                    data[n][c][h][w] = distr(eng) * mask[cnt];
                    cnt++;
                }
            }
        }
    }
}

void Tensor4D_IO::initialize_value(Fmap_t init_value) {
    for (int n=0; n<N; n++) {
        for (int c=0; c<C; c++) {
            for (int h=0; h<H; h++) {
                for (int w=0; w<W; w++) {
                    data[n][c][h][w] = init_value;
                }
            }
        }
    }
}

void Tensor4D_IO::print() {
    for (int n=0; n<N; n++) {
        cout << "[";
        for (int c=0; c<C; c++) {
            cout << "[";
            for (int h=0; h<H; h++) {
                cout << "[";
                for (int w=0; w<W; w++) {
                    if (w <= (W - 2))
                        cout << setw(10) << data[n][c][h][w] << ", ";
                    else
                        cout << setw(10) << data[n][c][h][w] << " ";
                }
                if (h == H-1)
                    cout << "]";
                else
                    cout << "], " << endl;
            }
            if (c == C-1)
                cout << "]";
            else
                cout << "], " << endl;
        }
        cout << "] " << endl;
    }
}

void Tensor4D_IO::compress_IO_sparse() {
    IO_buffer _io_buffer;
    IO_indices _io_indices;
    int cnt = 0;

    for (int n=0; n<N; n++) {
        vector<IO_vec> new_elem;
        vector<vector<int>> new_idx;
        _io_buffer.push_back(new_elem);
        _io_indices.push_back(new_idx);
        for (int c=0; c<C; c++) {
            IO_vec new_elem;
            vector<int> new_idx;
            _io_buffer[n].push_back(new_elem);
            _io_indices[n].push_back(new_idx);
            cnt = 0;
            for (int h=0; h<H; h++) {
                for (int w=0; w<W; w++) {
                    if (data[n][c][h][w] != 0) {
                        bool valid = true;
                        Fmap_t val = data[n][c][h][w];
                        tensor_4D_idx idx = make_tuple(n, c, h, w);
                        IO_element new_elem(valid, val, idx);
                        _io_buffer[n][c].push_back(new_elem);
                        _io_indices[n][c].push_back(cnt);
                        cnt = 0;
                    }
                    else {
                        cnt++;
                    }
                }
            }
            _io_indices[n][c].insert(_io_indices[n][c].begin(), _io_buffer[n][c].size());
        }
    }
    io_buffer = _io_buffer;
    io_indices = _io_indices;
    return;
}

void Tensor4D_IO::compress_IO_sparse_tile(ConfigDataflow* cfg_layer, int tile_num) {
    IO_buffer _io_buffer;
    IO_indices _io_indices;
    int cnt = 0;

    int tile_h, tile_w;
    int start_h = 0;
    int end_h = 0;
    int start_w = 0;
    int end_w = 0;
    vector<int> vec_tile_w = cfg_layer->get_Vec_Tile_W();
    vector<int> vec_tile_h = cfg_layer->get_Vec_Tile_H();
    tile_h = tile_num / vec_tile_w.size();
    tile_w = tile_num % vec_tile_w.size();
    for (int a=0; a<tile_h; a++) {
        start_h += vec_tile_h[a];
    }
    end_h = start_h + vec_tile_h[tile_h];
    for (int b=0; b<tile_w; b++) {
        start_w += vec_tile_w[b];
    }
    end_w = start_w + vec_tile_w[tile_w];

    for (int n=0; n<N; n++) {
        vector<IO_vec> new_elem;
        vector<vector<int>> new_idx;
        _io_buffer.push_back(new_elem);
        _io_indices.push_back(new_idx);
        for (int c=0; c<C; c++) {
            IO_vec new_elem;
            vector<int> new_idx;
            _io_buffer[n].push_back(new_elem);
            _io_indices[n].push_back(new_idx);
            cnt = 0;
            for (int h=start_h; h<end_h; h++) {
                for (int w=start_w; w<end_w; w++) {
                    if (data[n][c][h][w] != 0) {
                        bool valid = true;
                        Fmap_t val = data[n][c][h][w];
                        tensor_4D_idx idx = make_tuple(n, c, h, w);
                        IO_element new_elem(valid, val, idx);
                        _io_buffer[n][c].push_back(new_elem);
                        _io_indices[n][c].push_back(cnt);
                        cnt = 0;
                    }
                    else {
                        cnt++;
                    }
                }
            }
            _io_indices[n][c].insert(_io_indices[n][c].begin(), _io_buffer[n][c].size());
        }
    }
    io_buffer = _io_buffer;
    io_indices = _io_indices;
    return;
}

int Tensor4D_IO::get_N() { return N; }
int Tensor4D_IO::get_C() { return C; }
int Tensor4D_IO::get_H() { return H; }
int Tensor4D_IO::get_W() { return W; }

int Tensor4D_IO::get_total_element_num() {
    return N * C * H * W;
}

tensor_4D_idx Tensor4D_IO::get_shape() {
    tensor_4D_idx shape = make_tuple(N, C, H, W);
    return shape;
}

Fmap_t**** Tensor4D_IO::get_data() { return data; }
IO_buffer Tensor4D_IO::get_io_buffer() { return io_buffer; }
IO_indices Tensor4D_IO::get_io_indices() { return io_indices; }

void Tensor4D_IO::accumulate_idx_to_val(Fmap_t val, tensor_4D_idx idx) {
    assert(get<0>(idx) < N && get<1>(idx) < C && get<2>(idx) < H && get<3>(idx) < W);
    data[get<0>(idx)][get<1>(idx)][get<2>(idx)][get<3>(idx)] += val;
}

/* ------------------------------------------------------------------------------------------------------ */

Tensor4D_W::Tensor4D_W(int _K, int _C, int _S, int _R) {
    assert(_K > 0 && _C > 0 && _S > 0 && _R > 0);
    K = _K;
    C = _C;
    S = _S;
    R = _R;

    Weight_t**** _data = new Weight_t***[_K];
    for (int k=0; k<_K; k++) {
        _data[k] = new Weight_t**[_C];
        assert(_data[k]);
        for (int c=0; c<_C; c++) {
            _data[k][c] = new Weight_t*[_S];
            assert(_data[k][c]);
            for (int s=0; s<_S; s++) {
                _data[k][c][s] = new Weight_t[_R];
                assert(_data[k][c][s]);
            }
        }
    }
    data = _data;
}

Tensor4D_W::~Tensor4D_W() {
    for (int k=0; k<K; k++) {
        for (int c=0; c<C; c++) {
            for (int s=0; s<S; s++) {
                delete[] data[k][c][s];
            }
            delete[] data[k][c];
        }
        delete[] data[k];
    }
    delete[] data;
}

void Tensor4D_W::initialize_random(float sparsity, int min, int max) {
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<Weight_t> distr(min, max);

    int cnt = 0;
    int num_zeros = floor(K * C * S * R * sparsity);
    int num_ones = (K * C * S * R) - num_zeros;
    vector<int> mask(num_zeros, 0);
    for (int i=0; i<num_ones; i++) { mask.push_back(1); }
    shuffle(begin(mask), end(mask), eng);

    for (int k=0; k<K; k++) {
        for (int c=0; c<C; c++) {
            for (int s=0; s<S; s++) {
                for (int r=0; r<R; r++) {
                    data[k][c][s][r] = distr(eng) * mask[cnt];
                    cnt++;
                }
            }
        }
    }
}

void Tensor4D_W::initialize_value(Fmap_t init_value) {
    for (int k=0; k<K; k++) {
        for (int c=0; c<C; c++) {
            for (int s=0; s<S; s++) {
                for (int r=0; r<R; r++) {
                    data[k][c][s][r] = init_value;
                }
            }
        }
    }
}

void Tensor4D_W::print() {
    for (int k=0; k<K; k++) {
        cout << "[";
        for (int c=0; c<C; c++) {
            cout << "[";
            for (int s=0; s<S; s++) {
                cout << "[";
                for (int r=0; r<R; r++) {
                    if (r <= (R - 2))
                        cout << setw(10) << data[k][c][s][r] << ", ";
                    else
                        cout << setw(10) << data[k][c][s][r] << " ";
                }
                if (s == S-1)
                    cout << "]";
                else
                    cout << "], " << endl;
            }
            if (c == C-1)
                cout << "]";
            else
                cout << "], " << endl;
        }
        cout << "] " << endl;
    }
}

void Tensor4D_W::compress_W_sparse(int Kc) {
    int out_channel_group = (int) K / Kc;
    W_buffer _w_buffer;
    W_indices _w_indices;
    int cnt = 0;

    for (int kprm=0; kprm<out_channel_group; kprm++) {
        vector<W_vec> new_elem;
        vector<vector<int>> new_idx;
        _w_buffer.push_back(new_elem);
        _w_indices.push_back(new_idx);
        for (int c=0; c<C; c++) {
            W_vec new_elem;
            vector<int> new_idx;
            _w_buffer[kprm].push_back(new_elem);
            _w_indices[kprm].push_back(new_idx);
            cnt = 0;
            for (int k=0; k<Kc; k++) {
                for (int s=0; s<S; s++) {
                    for (int r=0; r<R; r++) {
                        if (data[k+(kprm*Kc)][c][s][r] != 0) {
                            bool valid = true;
                            Weight_t val = data[k+(kprm*Kc)][c][s][r];
                            tensor_4D_idx idx = make_tuple(k+(kprm*Kc), c, s, r);
                            W_element new_elem(valid, val, idx);
                            _w_buffer[kprm][c].push_back(new_elem);
                            _w_indices[kprm][c].push_back(cnt);
                            cnt = 0;
                        }
                        else {
                            cnt++;
                        }
                    }
                }
            }
            _w_indices[kprm][c].insert(_w_indices[kprm][c].begin(), _w_buffer[kprm][c].size());
        }
    }
    w_buffer = _w_buffer;
    w_indices = _w_indices;
    return;
}

int Tensor4D_W::get_K() { return K; }
int Tensor4D_W::get_C() { return C; }
int Tensor4D_W::get_S() { return S; }
int Tensor4D_W::get_R() { return R; }

int Tensor4D_W::get_total_element_num() {
    return K * C * S * R;
}

tensor_4D_idx Tensor4D_W::get_shape() {
    tensor_4D_idx shape = make_tuple(K, C, S, R);
    return shape;
}

Weight_t**** Tensor4D_W::get_data() { return data; }
W_buffer Tensor4D_W::get_w_buffer() { return w_buffer; }
W_indices Tensor4D_W::get_w_indices() { return w_indices; }

}