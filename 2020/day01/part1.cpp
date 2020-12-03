#include <iostream>
#include <set>

int main(){

    int first_number, second_number, tmp;
    std::multiset<int> numbers;

    for(int i = 0; i < 200; i++){    /* 200 entries in input file */
        std::cin >> tmp;
        numbers.insert(tmp);
    }

    for(std::multiset<int>::iterator i = numbers.begin(); i != numbers.end(); i++){
        first_number = *i;
        second_number = *numbers.find(2020 - first_number);

        if(second_number != *numbers.end()){
            std::cout << first_number * second_number << '\n';
            return 0;
        }
    }

    std::cout << "Didn't find entries that add up to 2020\n";

    return 0;
}
