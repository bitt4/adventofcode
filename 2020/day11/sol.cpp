#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

bool valid_coordinate(const int x, const int y, const int width, const int height) {
    return 0 <= x && x < width && 0 <= y && y < height;
}

size_t get_nearby_seats(const std::vector<std::string>& seats, const int x, const int y) {
    size_t nearby_seats = 0;
    int line_length = seats[0].length();
    int number_of_lines = seats.size();

    for (int rx = -1; rx <= 1; ++rx) {
        for (int ry = -1; ry <= 1; ++ry) {
            if (rx == 0 && ry == 0) {
                continue;
            }
            int current_x = x + rx;
            int current_y = y + ry;
            if (valid_coordinate(current_x, current_y, line_length, number_of_lines)) {
                if (seats[current_y][current_x] == '#') {
                    nearby_seats++;
                }
            }
        }
    }

    return nearby_seats;
}

size_t get_visible_seats(const std::vector<std::string>& seats, const int x, const int y) {
    size_t visible_seats = 0;
    int line_length = seats[0].length();
    int number_of_lines = seats.size();

    for (int rx = -1; rx <= 1; ++rx) {
        for (int ry = -1; ry <= 1; ++ry) {
            int current_x = x + rx;
            int current_y = y + ry;
            if (rx == 0 && ry == 0) {
                continue;
            }
            while (valid_coordinate(current_x, current_y, line_length, number_of_lines)) {
                if (seats[current_y][current_x] == '#') {
                    visible_seats++;
                    break;
                } else if (seats[current_y][current_x] == 'L') {
                    break;
                } else {
                    current_x += rx;
                    current_y += ry;
                }
            }
        }
    }

    return visible_seats;
}

template <typename T>
bool vec_equal(const std::vector<T>& a, const std::vector<T>& b) {
    if (a.size() != b.size()) {
        return false;
    }
    return std::equal(a.begin(), a.end(), b.begin());
}

size_t occupied_seats(std::vector<std::string> seats,
                      size_t (*f)(
                          const std::vector<std::string>&,
                          const int, const int
                          ),
                      const size_t tolerancy_limit) {
    size_t occupied_seats = 0;
    std::vector<std::string> seats_swap;

    seats_swap = seats;

    while (true) {
        for (size_t y = 0; y < seats.size(); ++y) {
            for (size_t x = 0; x < seats[0].length(); ++x) {
                if (seats_swap[y][x] == 'L' && f(seats_swap, x, y) == 0) {
                    seats[y][x] = '#';
                } else if (seats_swap[y][x] == '#' && f(seats_swap, x, y) >= tolerancy_limit) {
                    seats[y][x] = 'L';
                }
            }
        }

        if (vec_equal(seats, seats_swap)) {
            break;
        }

        seats_swap = seats;
    }

    for (size_t y = 0; y < seats.size(); ++y) {
        for (size_t x = 0; x < seats[0].length(); ++x) {
            if (seats[y][x] == '#') {
                occupied_seats++;
            }
        }
    }

    return occupied_seats;
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::vector<std::string> seats;

    std::string line;
    while (std::getline(input, line)) {
        seats.push_back(line);
    }

    std::cout << "part 1: " << occupied_seats(seats, get_nearby_seats, 4) << '\n';
    std::cout << "part 2: " << occupied_seats(seats, get_visible_seats, 5) << '\n';

    return 0;
}
