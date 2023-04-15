#include <array>
#include <fstream>
#include <iostream>
#include <tuple>

using v4 = std::tuple<int, int, int, int>;
using Grid4d = std::array<std::array<std::array<std::array<char, 20>, 20>, 13>, 13>;

int get_nearby_cubes(const Grid4d& grid, v4 coords, bool four_dim = false) {
    auto [x, y, z, w] = coords;

    int from = four_dim ? w - 1 : w;
    int to = four_dim ? w + 1 : w;

    int count = 0;
    for (int nw = from; nw <= to; ++nw) {
        for (int nz = z - 1; nz <= z + 1; ++nz) {
            for (int ny = y - 1; ny <= y + 1; ++ny) {
                for (int nx = x - 1; nx <= x + 1; ++nx) {
                    if (nz == z && ny == y && nx == x && nw == w) {
                        continue;
                    }
                    if (nw < 0 || nz < 0 || ny < 0 || nx < 0) {
                        continue;
                    }
                    if (   nw >= std::ssize(grid)
                        || nz >= std::ssize(grid[0])
                        || ny >= std::ssize(grid[0][0])
                        || nx >= std::ssize(grid[0][0][0])) {
                        continue;
                    }
                    if (grid[nw][nz][ny][nx] == '#') {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

Grid4d cycle(const Grid4d& current_state, bool four_dim = false) {
    Grid4d next_state = {};

    int from = four_dim ? 0 : 6;
    int to = four_dim ? std::ssize(current_state) : 7;

    for (int w = from; w < to; ++w) {
        for (int z = 0; z < std::ssize(current_state[0]); ++z) {
            for (int y = 0; y < std::ssize(current_state[0][0]); ++y) {
                for (int x = 0; x < std::ssize(current_state[0][0][0]); ++x) {
                    int nearby = get_nearby_cubes(current_state, { x, y, z, w }, four_dim);
                    auto&& next_cube = next_state[w][z][y][x];
                    if (current_state[w][z][y][x] == '#') {
                        if (2 <= nearby && nearby <= 3) {
                            next_cube = '#';
                        } else {
                            next_cube = '.';
                        }
                    } else if (nearby == 3) {
                        next_cube = '#';
                    } else {
                        next_cube = '.';
                    }
                }
            }
        }
    }

    return next_state;
}

int count_active(const Grid4d& grid, bool four_dim = false) {
    int count = 0;

    int from = four_dim ? 0 : 6;
    int to = four_dim ? std::ssize(grid) : 7;

    for (int w = from; w < to; ++w) {
        for (int z = 0; z < std::ssize(grid[0]); ++z) {
            for (int y = 0; y < std::ssize(grid[0][0]); ++y) {
                for (int x = 0; x < std::ssize(grid[0][0][0]); ++x) {
                    if (grid[w][z][y][x] == '#') {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int simulate(Grid4d grid, bool four_dim = false) {
    for (int i = 0; i < 6; ++i) {
        grid = cycle(grid, four_dim);
    }

    return count_active(grid, four_dim);
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    Grid4d grid = {};
    {
        std::string line;
        for (int y = 0; std::getline(input, line); ++y) {
            for (size_t x = 0; x < line.size(); ++x) {
                grid[6][6][y + 6][x + 6] = line[x];
            }
        }
    }
    input.close();

    std::cout << "part 1: " << simulate(grid) << '\n';
    std::cout << "part 2: " << simulate(grid, true) << '\n';

    return 0;
}
