#ifndef SCNN_COMMON_H_
#define SCNN_COMMON_H_

#include <algorithm>
#include <cassert>
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