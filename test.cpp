#include <iomanip>
#include <iostream>
#include <cmath>
#include <deque>
#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <map>
#include <random>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using namespace std;

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n;
 
    std::vector<T> vec(first, last);
    return vec;
}

int main(int argc, char **argv) {

    // assert(argc == 2);
    // ifstream cfg_file(argv[1]);
    // assert(cfg_file.is_open());
    // string line;
    // string delimiter = ": ";
    // int num_layers;

    // // Get Num_Layers value
    // getline(cfg_file, line);
    // line.erase(0, line.find(delimiter) + delimiter.length());
    // num_layers = atoi(line.c_str());
    // cout << "Num_Layers: " << num_layers << endl;
    // getline(cfg_file, line);
    // cout << line << endl;

    // // Get values for ConfigArch
    // getline(cfg_file, line);
    // line.erase(0, line.find(delimiter) + delimiter.length());
    // cout << "I: " << atoi(line.c_str())<< endl;
    // getline(cfg_file, line);
    // line.erase(0, line.find(delimiter) + delimiter.length());
    // cout << "F: " << atoi(line.c_str())<< endl;
    // getline(cfg_file, line);
    // line.erase(0, line.find(delimiter) + delimiter.length());
    // cout << "defval: " << atoi(line.c_str())<< endl;
    // getline(cfg_file, line);
    // cout << line << endl;
    
    // // Get values for each ConfigDataflow
    // for (int layer=0; layer<num_layers; layer++) {
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "N: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "C: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "Orig_H: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "Orig_W: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "K: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "Kc: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "S: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "R: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "PE_Num_H: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "PE_Num_W: " << atoi(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "io_sparsity: " << atof(line.c_str())<< endl;
    //     getline(cfg_file, line);
    //     line.erase(0, line.find(delimiter) + delimiter.length());
    //     cout << "w_sparsity: " << atof(line.c_str())<< endl;
    //     if (layer < (num_layers - 1)) {
    //         getline(cfg_file, line);
    //         cout << line << endl;
    //     }
    // }

    // cfg_file.close();
    char b[10] = "9076876";
    char* c = b;
    char a[20];
    strncpy(a, c, sizeof(a));
    cout << c << endl;
    cout << a << endl;

    return 0;
}
