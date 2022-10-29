#ifndef SCNN_DATATYPES_H_
#define SCNN_DATATYPES_H_

#include "common.h"

namespace SCNN {

#define Weight_t float      // Weight data
#define Fmap_t float        // IA & OA data
#define tensor_4D_idx tuple<int, int, int, int>

#define W_indices vector<vector<vector<int>>>
#define IO_indices vector<vector<vector<int>>>

#define W_vec vector<W_element>
#define IO_vec vector<IO_element>

// W_buffer[K/Kc][C][Kc*S*R]: assumes whole weight tensor stored in FIFO buffer
#define W_buffer vector<vector<W_vec>>

// IO_buffer[N][C][Ht*Wt]: assumes whole IO tensor stored in RAM
#define IO_buffer vector<vector<IO_vec>>

class W_element {

public:
    W_element(
        bool _valid,
        Weight_t _data,
        tensor_4D_idx _idx
    );
    
    void print();

    void set_valid(bool _valid);
    void set_data(Weight_t _data);
    void set_idx(tensor_4D_idx _idx);

    bool get_valid();
    Weight_t get_data();
    tensor_4D_idx get_idx();

private:
    bool valid;
    Weight_t data;
    tensor_4D_idx idx;
};

class IO_element {

public:
    IO_element(
        bool _valid, 
        Fmap_t _data, 
        tensor_4D_idx _idx
    );

    void print();
    
    void set_valid(bool _valid);
    void set_data(Fmap_t _data);
    void set_idx(tensor_4D_idx _idx);
    void set_idx_in_bank(int _idx_in_bank);

    void accumulate(Fmap_t _data);

    bool get_valid();
    Fmap_t get_data();
    tensor_4D_idx get_idx();
    int get_idx_in_bank();

private:
    bool valid;
    Fmap_t data;
    tensor_4D_idx idx;
    int idx_in_bank;
};

}

#endif