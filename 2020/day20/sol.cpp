#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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
    for (size_t i = 0; i < TILE_SIZE; ++i) {
        if (left.data[i][TILE_SIZE - 1] != right.data[i][0]) {
            return false;
        }
    }

    return true;
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

    std::set<int> visited;
    std::queue<std::pair<Tile, std::pair<int, int>>> to_visit;
    std::map<std::pair<int, int>, Tile> relative_positions;

    relative_positions[{ 0, 0 }] = tiles[0];
    to_visit.push({ tiles[0], { 0, 0 } });
    while (!to_visit.empty()) {
        auto [tile, position] = to_visit.front();
        auto [x, y] = position;
        to_visit.pop();

        for (const auto& another_tile : tiles) {
            if (tile.id == another_tile.id || visited.contains(another_tile.id)) {
                continue;
            }

            std::array<Tile, 8> rotations;

            rotations[0] = another_tile;
            for (int i = 1; i < 4; ++i) {
                rotations[i] = rotate(rotations[i - 1]);
            }

            rotations[4] = flip(another_tile);
            for (int i = 5; i < 8; ++i) {
                rotations[i] = rotate(rotations[i - 1]);
            }

            for (auto rotated : rotations) {
                int dx = 0;
                int dy = 0;
                if (matches_right(tile, rotated)) {
                    dx = 1;
                } else if (matches_top(tile, rotated)) {
                    dy = -1;
                } else if (matches_left(tile, rotated)) {
                    dx = -1;
                } else if (matches_bottom(tile, rotated)) {
                    dy = 1;
                } else {
                    continue;
                }

                to_visit.push({ rotated, { x + dx, y + dy } });
                relative_positions[{ x + dx, y + dy }] = rotated;
                visited.insert(tile.id);
                visited.insert(rotated.id);
                break;
            }
        }
    }

    int top_row = 0;
    while (relative_positions.contains({ top_row - 1, 0 })) {
        top_row--;
    }

    int bottom_row = 0;
    while (relative_positions.contains({ bottom_row + 1, 0 })) {
        bottom_row++;
    }

    int right_col = 0;
    while (relative_positions.contains({ 0, right_col + 1 })) {
        right_col++;
    }

    int left_col = 0;
    while (relative_positions.contains({ 0, left_col - 1 })) {
        left_col--;
    }

    uint64_t part1 = relative_positions[{ top_row, left_col }].id
        * relative_positions[{ top_row, right_col }].id
        * relative_positions[{ bottom_row, left_col }].id
        * relative_positions[{ bottom_row, right_col }].id;
    std::cout << "part 1: " << part1 << '\n';

    return 0;
}
