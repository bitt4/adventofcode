#include <iostream>
#include <vector>
#include <algorithm>

size_t get_nearby_seats(std::vector<std::string> seats, int x, int y){
    size_t nearby_seats = 0;
    int line_length = seats[0].length();
    int number_of_lines = seats.size();

    for(int rx = -1; rx <= 1; rx++){
        for(int ry = -1; ry <= 1; ry++){
            if(!(rx == 0 && ry == 0)){
                int current_x = x + rx;
                int current_y = y + ry;
                if(   current_x >= 0
                   && current_x < line_length
                   && current_y >= 0
                   && current_y < number_of_lines)
                {
                    if(seats[current_y][current_x] == '#')
                        nearby_seats++;
                }
            }
        }
    }

    return nearby_seats;
}

template <typename T>
bool comp_vec(std::vector<T> a, std::vector<T> b){
    if(a.size() != b.size())
        return false;
    return std::equal(a.begin(), a.end(), b.begin());
}

int main(){

    const size_t input_size = 94;
    size_t occupied_seats = 0;
    std::vector<std::string> seats, seats_swap;
    seats.resize(input_size);
    seats_swap.resize(input_size);

    for(size_t i = 0; i < input_size; i++){
        std::cin >> seats[i];
    }

    seats_swap = seats;

    while(true){
        for(size_t y = 0; y < seats.size(); y++){
            for(size_t x = 0; x < seats[0].length(); x++){
                if(seats_swap[y][x] == 'L' && get_nearby_seats(seats_swap, x, y) == 0){
                    seats[y][x] = '#';
                }
                else if(seats_swap[y][x] == '#' && get_nearby_seats(seats_swap, x, y) >= 4){
                    seats[y][x] = 'L';
                }
                else {
                    seats[y][x] = seats_swap[y][x];
                }
            }
        }

        if(comp_vec(seats, seats_swap))
            break;

        seats_swap = seats;
    }

    for(size_t y = 0; y < seats.size(); y++){
        for(size_t x = 0; x < seats[0].length(); x++){
            if(seats[y][x] == '#')
                occupied_seats++;
        }
    }

    std::cout << occupied_seats << '\n';

    return 0;
}
