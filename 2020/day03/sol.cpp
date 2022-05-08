#include <fstream>
#include <iostream>
#include <vector>

uint32_t check_slope(const std::vector<std::string>& area, int xs, int ys) {
    uint32_t trees = 0;
    uint32_t x = 0;
    uint32_t y = 0;

    while (y < area.size()) {
        x %= area[y].length();

        if (area[y][x] == '#') {
            trees++;
        }

        x += xs;
        y += ys;
    }

    return trees;
}

int main() {
    std::ifstream input("input");
    std::vector<std::string> forest;
    uint32_t pos = 0, trees = 0;

    std::string line;
    while (std::getline(input, line)) {
        forest.push_back(line);

        pos %= line.length();

        if (line[pos] == '#') {
            trees++;
        }

        pos += 3;
    }

    std::cout << "part 1: " << trees << '\n';

    std::cout << "part 2: " <<
        check_slope(forest, 1, 1) *
        check_slope(forest, 3, 1) *
        check_slope(forest, 5, 1) *
        check_slope(forest, 7, 1) *
        check_slope(forest, 1, 2) << '\n';

    return 0;
}
