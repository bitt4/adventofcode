#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

static constexpr size_t TILE_SIZE = 10;

using u64 = uint64_t;

struct Tile {
    u64 id;
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

    auto len = tile.data.size();
    for (size_t i = 0; i < len; ++i) {
        std::string line {};

        for (size_t j = 0; j < len; ++j) {
            line += tile.data[len - j - 1][i];
        }

        new_tile.data[i] = line;
    }

    return new_tile;
}

Tile flip(Tile tile) {
    std::reverse(tile.data.begin(), tile.data.end());
    return tile;
}

std::vector<std::string> remove_monsters(std::vector<std::string> image) {
    const std::vector<std::string> monster = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };

    // compare each 'window' of the image with the monster
    for (size_t y = 0; y < image.size() - 2; ++y) {
        for (size_t x = 0; x < image[y].size() - monster[0].size() + 1; ++x) {
            bool monster_matches = true;
            for (size_t ym = 0; ym < monster.size(); ++ym) {
                for (size_t xm = 0; xm < monster[0].size(); ++xm) {
                    if (monster[ym][xm] == ' ') {
                        continue;
                    }
                    if (monster[ym][xm] != image[y + ym][x + xm]) {
                        monster_matches = false;
                        // using goto to exit nested for loops
                        goto MONSTER_NOT_FOUND;
                    }
                }
            }

            // this label could technically be placed at the end of the loop
            // and we wouldn't even need the `bool monster_matches`, but I
            // think this is more readable, let the compiler do it's magic
        MONSTER_NOT_FOUND:
            if (monster_matches) {
                for (size_t ym = 0; ym < monster.size(); ++ym) {
                    for (size_t xm = 0; xm < monster[0].size(); ++xm) {
                        if (monster[ym][xm] != ' ') {
                            image[y + ym][x + xm] = 'O';
                        }
                    }
                }
            }
        }
    }

    return image;
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
        u64 id = std::stoi(id_with_colon.substr(0, id_with_colon.length() - 1));

        std::array<std::string, TILE_SIZE> data;
        std::string data_line;
        for (size_t i = 0; i < TILE_SIZE; ++i) {
            std::getline(input, data_line);
            data[i] = data_line;
        }

        tiles.push_back({ id, data });

        std::getline(input, line); // consume blank line after tile data in input file
    }

    using Coordinates = std::pair<int, int>;

    std::map<Coordinates, Tile> relative_positions;
    relative_positions[{ 0, 0 }] = tiles[0];

    std::set<int> visited;
    std::queue<std::pair<Tile, Coordinates>> to_visit;
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
    while (relative_positions.contains({ 0, top_row - 1 })) {
        top_row--;
    }

    int bottom_row = 0;
    while (relative_positions.contains({ 0, bottom_row + 1 })) {
        bottom_row++;
    }

    int left_col = 0;
    while (relative_positions.contains({ left_col - 1, 0 })) {
        left_col--;
    }

    int right_col = 0;
    while (relative_positions.contains({ right_col + 1, 0 })) {
        right_col++;
    }

    u64 part1 = relative_positions[{ left_col, top_row }].id
        * relative_positions[{ right_col, top_row }].id
        * relative_positions[{ left_col, bottom_row }].id
        * relative_positions[{ right_col, bottom_row }].id;

    std::cout << "part 1: " << part1 << '\n';

    std::vector<std::string> image;

    // build the image line by line
    for (int y = top_row; y <= bottom_row; ++y) {
        for (size_t i = 1; i < TILE_SIZE - 1; ++i) {
            std::string line {};
            for (int x = left_col; x <= right_col; ++x) {
                line += relative_positions[{ x, y }]
                            .data[i]
                            .substr(1, TILE_SIZE - 2);
            }
            image.push_back(line);
        }
    }

    auto rotate_vector = [](const std::vector<std::string>& vec) {
        std::vector<std::string> out;

        for (size_t x = 0; x < vec[0].size(); ++x) {
            std::string line;
            for (size_t y = 0; y < vec.size(); ++y) {
                line += vec[vec.size() - y - 1][x];
            }
            out.push_back(line);
        }

        return out;
    };

    std::array<std::vector<std::string>, 8> rotations;
    rotations[0] = image;
    for (int i = 1; i < 4; ++i) {
        rotations[i] = rotate_vector(rotations[i - 1]);
    }

    // flip the image
    std::reverse(image.begin(), image.end());

    rotations[4] = image;
    for (int i = 5; i < 8; ++i) {
        rotations[i] = rotate_vector(rotations[i - 1]);
    }

    size_t part2 = 0;
    for (const auto& rotation : rotations) {
        if (auto removed = remove_monsters(rotation); removed != rotation) {
            for (auto line : removed) {
                part2 += std::count_if(line.begin(), line.end(), [](char c) {
                    return c == '#';
                });
            }
        }
    }

    std::cout << "part 2: " << part2 << '\n';

    return 0;
}
