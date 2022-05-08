#include <fstream>
#include <iostream>
#include <map>

int main() {
    std::ifstream input("input");

    int max = 0;
    std::map<int, bool> seats;

    std::string line;
    while (std::getline(input, line)) {
        int row_lower = 0;
        int column_lower = 0;

        for (int j = 0; j < 7; ++j) {
            int m = 6 - j;
            if (line[j] == 'B') {
                row_lower += 1 << m;
            }
        }

        for (int j = 7; j < 10; ++j) {
            int m = 9 - j;
            if (line[j] == 'R') {
                column_lower += 1 << m;
            }
        }

        int seat_id = row_lower * 8 + column_lower;
        if (seat_id > max) {
            max = seat_id;
        }

        seats[seat_id] = true;
    }

    std::cout << "part 1: " << max << '\n';

    for (int id = 1; id < 128 * 8 - 2; ++id) {
        if (seats[id - 1] && !seats[id] && seats[id + 1]) {
            std::cout << "part 2: " << id << '\n';
            return 0;
        }
    }

    return 0;
}
