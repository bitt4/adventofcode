#include <iostream>
#include <set>

int main(){

    std::set<int> adapters;
    int tmp;
    uint32_t one_jolt_diff = 0,
             three_jolt_diffs = 1;

    int last_adapter = 0;

    for(size_t i = 0; i < 99; i++){
        std::cin >> tmp;
        adapters.insert(tmp);
    }

    for(std::set<int>::iterator i = adapters.begin(); i != adapters.end(); i++){
        int difference = *i - last_adapter;

        if(difference == 1)
            one_jolt_diff++;
        else if(difference == 3)
            three_jolt_diffs++;

        last_adapter = *i;
    }

    std::cout << one_jolt_diff * three_jolt_diffs << '\n';

    return 0;
}
