#include <fstream>
#include <iostream>
#include <set>

int main(){
    std::ifstream input("input");
    std::multiset<int> numbers;

    int tmp;
    while (input >> tmp) {
        numbers.insert(tmp);
    }

    input.close();

    bool found1 = false;
    bool found2 = false;
    for (auto i = numbers.begin(); i != numbers.end(); ++i) {
        for (auto j = i; j != numbers.end(); ++j) {
            int first_number = *i;
            int second_number = *j;
            auto third_number_pos = numbers.find(2020 - first_number - second_number);

            if (first_number + second_number == 2020) {
                found1 = true;
                std::cout << "part 1: " << first_number * second_number << '\n';
            }

            if (third_number_pos != numbers.end()) {
                found2 = true;
                std::cout << "part 2: " << first_number * second_number * *third_number_pos << '\n';
            }

            if (found1 && found2) {
                return 0;
            }
        }
    }

    return 0;
}
