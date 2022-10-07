#ifndef SCNN_DATATYPES_H_
#define SCNN_DATATYPES_H_

#include "common.h"

namespace SCNN {

#define Weight_t float      // Weight data
#define Fmap_t float        // IA & OA data
#define tensor_4D_idx tuple<int, int, int, int>

#define W_indices vector<int>
#define IA_indices vector<int>
#define OA_indices vector<int>

#define W_vec vector<W_element>
#define IA_vec vector<IA_element>
#define OA_vec vector<OA_element>

// W_buffer[C][S*R/F][F]
// Notice that in order to completely fill the buffer, we would need [K/Kc][C][S*R/F][F], 
// but paper assumes that weight buffers are refilled for every iteration of the loop
#define W_buffer <vector<vector<W_vec>>

// IA_buffer[C][Ht*Wt/I][I]
#define IA_buffer vector<vector<IA_vec>>

// OA_buffer[K/Kc][Kc*Ht*Wt]
#define OA_buffer vector<OA_vec>

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

class IA_element {

public:
    IA_element(
        bool _valid, 
        Fmap_t _data, 
        tensor_4D_idx _idx
    );

    void print();
    
    void set_valid(bool _valid);
    void set_data(Fmap_t _data);
    void set_idx(tensor_4D_idx _idx);

    bool get_valid();
    Fmap_t get_data();
    tensor_4D_idx get_idx();

private:
    bool valid;
    Fmap_t data;
    tensor_4D_idx idx;
};

class OA_element {
    
public:
    OA_element();
    
    OA_element(
        bool _valid,
        Fmap_t _data,
        tensor_4D_idx _idx,
        unsigned _bank_id,
        unsigned _idx_in_bank
    );

    void print();

    void set_valid(bool _valid);
    void set_data(Fmap_t _data);
    void set_idx(tensor_4D_idx _idx);
    void set_bank_id(unsigned _new_id);
    void set_idx_in_bank(unsigned _new_idx);

    bool get_valid();
    Fmap_t get_data();
    tensor_4D_idx get_idx();
    unsigned get_bank_id();
    unsigned get_idx_in_bank();
    
private:
	bool valid;
	Fmap_t data;
    tensor_4D_idx idx;
    unsigned bank_id;
    unsigned idx_in_bank;
};

}

# endif