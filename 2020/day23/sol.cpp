#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int move(const int current_cup, std::vector<int>& next_cup) {
    int cup1 = next_cup[current_cup];
    int cup2 = next_cup[cup1];
    int cup3 = next_cup[cup2];
    next_cup[current_cup] = next_cup[cup3];

    int dest_cup = current_cup;
    do {
        if (dest_cup == 0) {
            dest_cup = next_cup.size() - 1;
        } else {
            dest_cup--;
        }
    } while (dest_cup == cup1 || dest_cup == cup2 || dest_cup == cup3);

    int after_dest = next_cup[dest_cup];
    next_cup[dest_cup] = cup1;
    next_cup[cup3] = after_dest;

    return next_cup[current_cup];
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::string line;
    std::getline(input, line);

    auto char_to_int_index = [](char c) -> int {
        return c - '0' - 1;
    };

    std::vector<int> next_cup(line.length());
    {
        auto cup = char_to_int_index(line[0]);
        for (size_t i = 0; i < line.length(); ++i) {
            int next = char_to_int_index(line[(i + 1) % line.length()]);
            next_cup[cup] = next;
            cup = next;
        }
    }

    std::vector<int> next_cup_1000000(1'000'000);
    std::copy(next_cup.begin(), next_cup.end(), next_cup_1000000.begin());

    {
        int current_cup = char_to_int_index(line[0]);
        for (int i = 0; i < 100; ++i) {
            current_cup = move(current_cup, next_cup);
        }

        std::string part1;
        int next = next_cup[0];
        for (size_t i = 0; i < line.length() - 1; ++i) {
            part1 += '0' + next + 1;
            next = next_cup[next];
        }

        std::cout << "part 1: " << part1 << '\n';
    }

    int last = char_to_int_index(line.back());
    for (size_t i = next_cup.size(); i < 1'000'000; ++i) {
        next_cup_1000000[last] = i;
        last = i;
    }
    next_cup_1000000[last] = char_to_int_index(line[0]);

    int current_cup = next_cup_1000000[last];
    for (int i = 0; i < 10'000'000; ++i) {
        current_cup = move(current_cup, next_cup_1000000);
    }

    int64_t cup1 = next_cup_1000000[0];
    int64_t cup2 = next_cup_1000000[cup1];
    int64_t part2 = (cup1 + 1) * (cup2 + 1);

    std::cout << "part 2: " << part2 << '\n';
}
