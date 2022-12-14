#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

static constexpr size_t TILE_SIZE = 10;

struct Tile {
    uint64_t id;
    std::array<std::string, TILE_SIZE> data;
};

std::vector<std::string> split_string(std::string s, const std::string delim = " ", std::vector<std::string> acc = {}) {
    auto pos = s.find(delim);
    if (pos != std::string::npos) {
        acc.push_back(s.substr(0, pos));
        return split_string(s.substr(pos + delim.length()), delim, acc);
    } else {
        acc.push_back(s);
        return acc;
    }
}

bool matches_right(const Tile& left, const Tile& right) {
    std::string left_side {};
    for (size_t i = 0; i < TILE_SIZE; ++i) {
        left_side += left.data[i][TILE_SIZE - 1];
    }

    std::string right_side {};
    for (size_t i = 0; i < TILE_SIZE; ++i) {
        right_side += right.data[i][0];
    }

    return left_side == right_side;
}

bool matches_left(const Tile& left, const Tile& right) {
    return matches_right(right, left);
}

bool matches_top(const Tile& left, const Tile& right) {
    return left.data[0] == right.data[TILE_SIZE - 1];
}

bool matches_bottom(const Tile& left, const Tile& right) {
    return matches_top(right, left);
}

Tile rotate(const Tile& tile) {
    Tile new_tile;
    new_tile.id = tile.id;

    for (size_t i = 0; i < TILE_SIZE; ++i) {
        std::string line {};

        for (size_t j = 0; j < TILE_SIZE; ++j) {
            line += tile.data[TILE_SIZE - j - 1][i];
        }

        new_tile.data[i] = line;
    }

    return new_tile;
}

Tile flip(Tile tile) {
    std::reverse(tile.data.begin(), tile.data.end());
    return tile;
}

bool matches(const Tile& left, const Tile& right) {
    auto matches_sides = [](const Tile& a, const Tile& b) {
        if (matches_right(a, b) || matches_left(a, b) || matches_top(a, b) || matches_bottom(a, b)) {
            return true;
        }
        return false;
    };

    std::vector<Tile> all_rotations = {
        left,
        rotate(left),
        rotate(rotate(left)),
        rotate(rotate(rotate(left))),
        flip(left),
        rotate(flip(left)),
        rotate(rotate(flip(left))),
        rotate(rotate(rotate(flip(left))))
    };

    for (const auto& tile : all_rotations) {
        if (matches_sides(tile, right)) {
            return true;
        }
    }

    return false;
}

bool is_corner(const Tile& tile, const std::vector<Tile>& tiles) {
    int matches_with = 0;
    for (const auto& another_tile : tiles) {
        if (tile.id != another_tile.id) {
            if (matches(tile, another_tile)) {
                matches_with++;
            }
        }
    }

    return matches_with == 2;
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::vector<Tile> tiles;

    std::string line;
    while (std::getline(input, line)) {
        std::string id_with_colon = split_string(line)[1];
        uint64_t id = std::stoi(id_with_colon.substr(0, id_with_colon.length() - 1));

        std::array<std::string, TILE_SIZE> data;
        std::string data_line;
        for (size_t i = 0; i < TILE_SIZE; ++i) {
            std::getline(input, data_line);
            data[i] = data_line;
        }

        tiles.push_back({ id, data });

        std::getline(input, line); // consume blank line after tile data in input file
    }

    uint64_t part1 = 1;
    for (const auto& tile : tiles) {
        if (is_corner(tile, tiles)) {
            part1 *= tile.id;
        }
    }

    std::cout << "part 1: " << part1 << '\n';

    return 0;
}
