#include <iostream>

int main(){

    const size_t input_size = 795;

    int wx = 10,
        wy = 1;
    int sx = 0,
        sy = 0;

    for(size_t i = 0; i < input_size; i++){
        std::string line;
        std::cin >> line;

        char action = line[0];
        int units = std::stoi(line.substr(1));

        switch(action){
        case 'N': wy += units; break;
        case 'S': wy -= units; break;
        case 'E': wx += units; break;
        case 'W': wx -= units; break;
        case 'R': units = 360 - units;
        case 'L':
            for(int j = units / 90; j > 0; j--){
                int tmp = wx;
                wx = wy * -1;
                wy = tmp;
            }
            break;
        case 'F':
            sx += units * wx;
            sy += units * wy;
            break;
        }
    }

    std::cout << abs(sx) + abs(sy) << '\n';

    return 0;
}
