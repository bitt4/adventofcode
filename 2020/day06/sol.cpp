#include <fstream>
#include <iostream>
#include <map>

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::map<char, int> group_answ;
    uint32_t anyone = 0;
    uint32_t everyone = 0;
    int group_size = 0;

    std::string line;
    while (std::getline(input, line)) {
        for (size_t j = 0; j < line.length(); j++) {
            group_answ[line[j]]++;
        }

        if (line.empty() || input.peek() == EOF) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (group_answ[c]) {
                    anyone++;
                }
                if (group_answ[c] == group_size) {
                    everyone++;
                }
            }

            group_size = 0;
            group_answ.clear();
        } else {
            group_size++;
        }
    }

    std::cout << "part 1: " << anyone << '\n';
    std::cout << "part 2: " << everyone << '\n';

    return 0;
}
