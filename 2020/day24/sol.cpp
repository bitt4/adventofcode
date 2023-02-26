#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using std::make_tuple;

using Tile = std::tuple<int, int, int>;

Tile parse_tile(const std::string& s) {
    int x = 0;
    int y = 0;
    int z = 0;

    for (size_t i = 0; i < s.length(); ++i) {
        char direction = s[i];
        if (direction == 'e') {
            x++;
            z++;
        } else if (direction == 'w') {
            x--;
            z--;
        } else {
            auto direction = s.substr(i, 2);
            if (direction == "ne") {
                x++;
                y++;
            } else if (direction == "se") {
                y--;
                z++;
            } else if (direction == "nw") {
                y++;
                z--;
            } else if (direction == "sw") {
                x--;
                y--;
            }
            i++;
        }
    }
    return make_tuple(x, y, z);
}

std::array<Tile, 6> get_nearby_tiles(const Tile& t) {
    auto& [x, y, z] = t;
    return {
        make_tuple(x + 1, y + 0, z + 1),
        make_tuple(x + 1, y + 1, z + 0),
        make_tuple(x + 0, y + 1, z - 1),
        make_tuple(x - 1, y + 0, z - 1),
        make_tuple(x - 1, y - 1, z + 0),
        make_tuple(x + 0, y - 1, z + 1),
    };
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::set<Tile> black_tiles;

    std::string line;
    while (std::getline(input, line)) {
        Tile t = parse_tile(line);
        if (black_tiles.contains(t)) {
            black_tiles.erase(t);
        } else {
            black_tiles.insert(t);
        }
    }

    int part1 = black_tiles.size();

    std::cout << "part 1: " << part1 << '\n';

    for (int i = 0; i < 100; ++i) {
        std::set<Tile> new_tiles;
        std::set<Tile> nearby_white;
        for (const auto& black_tile : black_tiles) {
            auto nearby_tiles = get_nearby_tiles(black_tile);

            int nearby_black = 0;
            for (auto nearby : nearby_tiles) {
                if (black_tiles.contains(nearby)) {
                    nearby_black++;
                } else {
                    nearby_white.insert(nearby);
                }
            }

            if (!(nearby_black == 0 || nearby_black > 2)) {
                new_tiles.insert(black_tile);
            }
        }

        for (const auto& white_tile : nearby_white) {
            auto nearby_tiles = get_nearby_tiles(white_tile);
            int nearby_black = std::count_if(
                nearby_tiles.begin(),
                nearby_tiles.end(),
                [&black_tiles](const Tile& t) { return black_tiles.contains(t); });

            if (nearby_black == 2) {
                new_tiles.insert(white_tile);
            }
        }
        black_tiles = new_tiles;
    }

    std::cout << "part 2: " << black_tiles.size() << '\n';

    return 0;
}
