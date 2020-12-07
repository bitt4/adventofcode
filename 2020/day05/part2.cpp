#include <iostream>
#include <map>

int main(){
    std::string line;
    int row_lower,
        row_upper,
        column_upper,
        column_lower,
        max = 0;

    std::map<int, bool> seats;

    for(int i = 0; i < 965; i++){
        std::cin >> line;
        row_upper = 128;
        row_lower = 0;
        column_upper = 8;
        column_lower = 0;

        for(int j = 0; j < 7; j++){
            int m = 6 - j;
            if(line[j] == 'F'){
                row_upper -= 1 << m;
            }
            else {
                row_lower += 1 << m;
            }
        }

        for(int j = 7; j < 10; j++){
            int m = 9 - j;
            if(line[j] == 'L'){
                column_upper -= 1 << m;
            }
            else {
                column_lower += 1 << m;
            }
        }

        int seat_id = row_lower * 8 + column_lower;
        if(seat_id > max){
            max = seat_id;
        }

        seats[seat_id] = true;
    }

    for(int id = 1; id < 128 * 8 - 2; id++){
        if(seats[id-1] && !seats[id] && seats[id+1]){
            std::cout << id << '\n';
            return 0;
        }
    }

    return 0;
}
