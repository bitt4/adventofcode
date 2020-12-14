#include <iostream>

int main(){

    const size_t input_size = 795;

    int x = 0, y = 0;
    int direction = 90;

    for(size_t i = 0; i < input_size; i++){
        std::string line;
        std::cin >> line;

        char action = line[0];
        int units = std::stoi(line.substr(1));

        switch(action){
        case 'N': y += units; break;
        case 'S': y -= units; break;
        case 'E': x += units; break;
        case 'W': x -= units; break;
        case 'L': direction -= units; break;
        case 'R': direction += units; break;
        case 'F':
            switch(direction){
                case 0:   y += units; break;
                case 90:  x += units; break;
                case 180: y -= units; break;
                case 270: x -= units; break;
            }
            break;
        }

        if     (direction >= 360) direction -= 360;
        else if(direction < 0)    direction += 360;
    }

    std::cout << abs(x) + abs(y) << '\n';

    return 0;
}
