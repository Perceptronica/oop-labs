#include "../lib/vector.h"
#include <iostream>
#include <vector>
#include <map>

int main() {
    /*
    std::map<int, int, std::less<int>, allocator< std::pair<const int, int> > > mp;
    mp[0] = 0;
    mp[1] = 1;
    for (int i = 2; i < 9; ++i) {
        mp[i] = mp[i - 1] * i;
    }
    for (auto& [k, v] : mp) {
        std::cout << "{" << k << ", " << v << "}\n";
    }
    */
    
    Vector<int> vec(10);
    for (size_t i {0}; i < 10; ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; ++i) {
        vec[i] = i * i;
    }
    for (size_t i {0}; i < 10; ++i) {
        std::cout << vec[i] << ' ';
    }
    std::cout << std::endl << vec.front() << ' ' << vec.back() << std::endl;
    vec.clear();
    for (size_t i {0}; i < vec.size(); ++i) {
        std::cout << vec[i] << ' ';
    }
    //return 0;
    std::vector<int> v(10);
    std::cout << v.size() << std::endl;
}