#include <iostream>
#include <vector>

uint32_t check_slope(std::vector<std::string> area, int xs, int ys){
    uint32_t trees = 0;
    uint32_t pos_x = 0;
    uint32_t pos_y = 0;

    while (pos_y < area.size()) {
        pos_x %= area[pos_y].length();

        if(area[pos_y][pos_x] == '#')
            trees++;

        pos_x += xs;
        pos_y += ys;
    }

    return trees;
}

int main(){

    std::vector<std::string> input;
    input.resize(323);

    for(int i = 0; i < 323; i++){
        std::cin >> input[i];
    }

    std::cout <<
        check_slope(input, 1, 1) *
        check_slope(input, 3, 1) *
        check_slope(input, 5, 1) *
        check_slope(input, 7, 1) *
        check_slope(input, 1, 2) << '\n';

    return 0;
}
