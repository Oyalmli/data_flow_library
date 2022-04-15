#include <iostream>
#include <vector>

#include "dvfw/dvfw.hpp"
#include <iterator>

using namespace dvfw;

struct Hell {
    int o;
    int a;
};

class hell_gen : public gen::base_generator<Hell> {
    public: 
    bool hasNext () {
        return true;
    }

    Hell next (){
        return {1,2};
    }

    hell_gen(){}
};

int main() {
    auto t_val_gen = gen::take<gen::value<int>>(100,gen::value(10));
    auto h_it = gen::gen_it<gen::take<gen::value<int>>, int>(t_val_gen);

    for (int i : h_it) {
        std::cout << i << "\n";
    }
}
