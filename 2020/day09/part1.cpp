#include <iostream>
#include <vector>
#include <algorithm>

int main(){

    const size_t input_size = 1000;

    std::vector<uint64_t> numbers;
    numbers.resize(input_size);

    for(size_t i = 0; i < input_size; i++){
        std::cin >> numbers[i];
    }

    size_t preamble_size = 25;

    for(size_t i = preamble_size; i < input_size; i++){
        uint64_t current_number = numbers[i];
        size_t preamble_range_from = i - preamble_size;
        size_t preamble_range_to = i - 1;

        bool found = false;
        std::vector<uint64_t>::iterator target;

        for(size_t j = preamble_range_from; j <= preamble_range_to; j++){
            target = std::find(numbers.begin() + preamble_range_from,
                               numbers.begin() + preamble_range_to + 1,
                               current_number - numbers[j]);

            if(*target != current_number){
                found = true;
                break;
            }
        }

        if(!found){
            std::cout << current_number << '\n';
            break;
        }
    }

    return 0;
}
