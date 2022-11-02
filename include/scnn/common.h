#ifndef SCNN_COMMON_H_
#define SCNN_COMMON_H_

#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <tuple>
#include <random>

namespace SCNN {
    using namespace std;

    template<typename T>
    std::vector<T> slice(std::vector<T> const &v, int m, int n)
    {
        auto first = v.cbegin() + m;
        auto last = v.cbegin() + n;
    
        std::vector<T> vec(first, last);
        return vec;
    }
}

#endif