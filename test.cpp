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

using namespace std;

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n;
 
    std::vector<T> vec(first, last);
    return vec;
}

int main() {
    // vector<vector<int>> v;
    // for (int a=0; a<9; a++) {
    //     vector<int> new_vec;
    //     v.push_back(new_vec);
    // }
    // v[0].push_back(1);
    // v[0].push_back(2);
    // v[0].push_back(3);
    // v[1].push_back(4);
    // v[7].push_back(10);
    // for (int i=0 ; i<v.size(); i++) {
    //     cout << "this is start of row " << i << endl;
    //     for (int j=0; j<v[i].size(); j++) {
    //         cout << v[i][j] << endl;
    //     }
    // }

    // vector<int> v;
    // for (int i=0; i<10; i++) {
    //     v.push_back(i);
    // }
    // for (int i=0; i<v.size(); i++) {
    //     cout << v[i] << " ";
    // }
    // cout << "" << endl;

    // vector<int> s = slice(v, 5, v.size());
    // for (int i=0; i<s.size(); i++) {
    //     cout << s[i] << " ";
    // }
    // cout << "" << endl;
    // int W = 260;
    // int PE_Num_W = 8;
    // int average_w = (int) W / PE_Num_W;
    // int remainder_w = (int) W % PE_Num_W;
    // vector<int> new_vec_tile_w(PE_Num_W, average_w);
    // for (int i=0; i<remainder_w; i++) {
    //     new_vec_tile_w[i]++;
    // }
    // for (int i=0; i<new_vec_tile_w.size(); i++) {
    //     cout << new_vec_tile_w[i] << " ";
    // }

    // vector<int> v = {};
    // int target = 18;
    // int low = 0;
    // int high = v.size() - 1;
    // int mid = (low + high) / 2;

    // if (v.empty()) {
    //     v.push_back(target);
    //     for (int i=0; i<v.size(); i++)
    //         cout << v[i] << " ";
    //     cout << "" << endl;
    //     return 0;
    // }

    // while (low <= high) {
    //     mid = (low + high) / 2;
    //     if (v[mid] == target) {
    //         break;
    //     }
    //     else if (v[mid] < target) {
    //         low = mid + 1;
    //     }
    //     else if (v[mid] > target) {
    //         high = mid - 1;
    //     }
    // }
    // if (v[mid] == target) {
    //     cout << mid << endl;
    // }
    // else {
    //     if (v[mid] < target) {
    //         v.insert(v.begin() + (mid + 1), 1, target);
    //     }
    //     else if (v[mid] > target) {
    //         v.insert(v.begin() + mid, 1, target);
    //     }
    //     for (int i=0; i<v.size(); i++)
    //         cout << v[i] << " ";
    //     cout << "" << endl;
    // }
    // return 0;

    float a = -0;
    float b = 0;
    if (a == b) {
        cout << "yes" << endl;
    }
    else {
        cout << "false" << endl;
    }







    // random_device rd;
    // default_random_engine eng(rd());
    // uniform_real_distribution<float> distr(-2, 2);

    // float a = distr(eng);
    // cout << a << endl;

    // shuffle(begin(v), end(v), eng);
    // for (int i=0; i<10; i++) {
    //     cout << v[i] << " ";
    // }
    // cout << "" << endl;

    
}