#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<std::string> split_string(std::string target, const char delimeter = ' ') {
    std::vector<std::string> out;
    int position = 0;
    size_t length = target.length();

    for (size_t i = 0; i < length; i++) {
        if (target[i] == delimeter) {
            out.push_back(std::string(target, position, i - position));
            position = i + 1;
            continue;
        }
        if (i == length - 1) {
            out.push_back(std::string(target, position, length - position));
        }
    }

    return out;
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    int valid_passwords_1 = 0;
    int valid_passwords_2 = 0;
    std::string range, rule, password;

    while (input >> range >> rule >> password) {
        char character = rule[0];

        std::vector<std::string> range_split = split_string(range, '-');

        int from = std::stoi(range_split[0]);
        int to = std::stoi(range_split[1]);

        int char_occ = std::count(password.begin(), password.end(), character);

        if (from <= char_occ && char_occ <= to) {
            valid_passwords_1++;
        }

        int first_position = from - 1;
        int second_position = to - 1;

        if ((password[first_position] == character) ^ (password[second_position] == character)) {
            valid_passwords_2++;
        }
    }

    std::cout << "part 1: " << valid_passwords_1 << '\n';
    std::cout << "part 2: " << valid_passwords_2 << '\n';

    return 0;
}
