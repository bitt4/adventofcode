#include <iostream>
#include <fstream>

int main(){
    std::ifstream input("input");

    int x = 0, y = 0;
    int wx = 10, wy = 1;
    int ship_x = 0, ship_y = 0;
    int direction = 90;

    std::string line;
    while (std::getline(input, line)) {
        char action = line[0];
        int units = std::stoi(line.substr(1));

        switch (action) {
            case 'N':
                y += units;
                wy += units;
                break;
            case 'S':
                y -= units;
                wy -= units;
                break;
            case 'E':
                x += units;
                wx += units;
                break;
            case 'W':
                x -= units;
                wx -= units;
                break;
            case 'L': {
                for (int j = units / 90; j > 0; j--) {
                    std::swap(wx, wy);
                    wx = -wx;
                }
                direction -= units;
                break;
            }
            case 'R': {
                for (int j = units / 90; j > 0; j--) {
                    std::swap(wx, wy);
                    wy = -wy;
                }
                direction += units;
                break;
            }
            case 'F':
                switch (direction) {
                    case 0:   y += units; break;
                    case 90:  x += units; break;
                    case 180: y -= units; break;
                    case 270: x -= units; break;
                }
                ship_x += units * wx;
                ship_y += units * wy;
                break;
        }

        if      (direction >= 360) direction -= 360;
        else if (direction < 0)    direction += 360;
    }

    std::cout << "part 1: " << abs(x) + abs(y) << '\n';
    std::cout << "part 2: " << abs(ship_x) + abs(ship_y) << '\n';

    return 0;
}
