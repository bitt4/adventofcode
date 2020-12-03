#include <iostream>
#include <set>

int main(){

    int first_number, second_number, third_number, tmp;
    std::multiset<int> numbers;

    for(int i = 0; i < 200; i++){    /* 200 entries in input file */
        std::cin >> tmp;
        numbers.insert(tmp);
    }

    for(std::multiset<int>::iterator i = numbers.begin(); i != numbers.end(); i++){
        for(std::multiset<int>::iterator j = ++numbers.begin(); j != numbers.end(); j++){
            first_number = *i;
            second_number = *j;
            third_number = *numbers.find(2020 - first_number - second_number);

            if(third_number != *numbers.end()){
                std::cout << first_number * second_number * third_number << '\n';
                return 0;
            }
        }
    }

    std::cout << "Didn't find entries that add up to 2020\n";

    return 0;
}
