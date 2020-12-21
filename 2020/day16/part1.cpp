#include <iostream>
#include <vector>

typedef struct {
    int min1,
        max1,
        min2,
        max2;

    bool in_range(int num){
        return (min1 <= num && num <= max1) || (min2 <= num && num <= max2);
    }
} Range;

std::vector<std::string> split_string(std::string target, char delimeter = ' '){
    std::vector<std::string> out;
    int position = 0;
    size_t length = target.length();

    for(size_t i = 0; i < length; i++){
        if(target[i] == delimeter){
            out.push_back(std::string(target, position, i - position));
            position = i+1;
            continue;
        }
        if(i == length - 1){
            out.push_back(std::string(target, position, length - position));
        }
    }

    return out;
}

int main(){

    std::string my_ticket;
    uint32_t error_rate = 0;
    std::vector<Range> notes_fields;

    for(size_t i = 0; i < 20; i++){
        std::string line;
        std::getline(std::cin, line);

        auto line_splitted = split_string(line);
        size_t line_items = line_splitted.size();

        auto range1 = split_string(line_splitted[line_items - 3], '-');
        auto range2 = split_string(line_splitted[line_items - 1], '-');

        int from1 = std::stoi(range1[0]);
        int to1 = std::stoi(range1[1]);

        int from2 = std::stoi(range2[0]);
        int to2 = std::stoi(range2[1]);

        Range field = {};
        field.min1 = from1;
        field.min2 = from2;
        field.max1 = to1;
        field.max2 = to2;

        notes_fields.push_back(field);
    }

    std::cin.ignore();
    std::cin.ignore(256, '\n');
    std::getline(std::cin, my_ticket);

    std::cin.ignore();
    std::cin.ignore(256, '\n');

    std::string nearby_ticket;
    for(size_t i = 0; i < 241; i++){
        std::cin >> nearby_ticket;
        auto nearby_ticket_fields = split_string(nearby_ticket, ',');

        for(auto &x : nearby_ticket_fields){
            bool in_range = false;
            int current_field = std::stoi(x);
            for(auto &field : notes_fields){    /* bad variable naming */
                if(field.in_range(current_field)){
                        in_range = true;
                }
            }
            if (!in_range) {
                error_rate += current_field;
                break;
            }
        }
    }

    std::cout << error_rate << '\n';

    return 0;
}
