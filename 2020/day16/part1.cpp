#include <fstream>
#include <iostream>
#include <vector>

struct Range {
    int min1,
    max1,
    min2,
    max2;

    bool in_range(int num) const {
        return (min1 <= num && num <= max1) || (min2 <= num && num <= max2);
    }
};

std::vector<std::string> split_string(std::string s, const std::string delim, std::vector<std::string> acc = {}) {
    auto pos = s.find(delim);
    if (pos != std::string::npos) {
        acc.push_back(s.substr(0, pos));
        return split_string(s.substr(pos + delim.length()), delim, acc);
    } else {
        acc.push_back(s);
        return acc;
    }
}

int main(){
    std::ifstream input("input");
    std::vector<Range> notes_fields;

    for (size_t i = 0; i < 20; i++) {
        std::string line;
        std::getline(input, line);

        auto line_splitted = split_string(line, " ");
        size_t line_items = line_splitted.size();

        auto range1 = split_string(line_splitted[line_items - 3], "-");
        auto range2 = split_string(line_splitted[line_items - 1], "-");

        int from1 = std::stoi(range1[0]);
        int to1 = std::stoi(range1[1]);

        int from2 = std::stoi(range2[0]);
        int to2 = std::stoi(range2[1]);

        Range field {
            from1,
            to1,
            from2,
            to2
        };

        notes_fields.push_back(field);
    }

    input.ignore();
    input.ignore(256, '\n');

    std::string my_ticket;
    std::getline(input, my_ticket);

    input.ignore();
    input.ignore(256, '\n');

    uint32_t error_rate = 0;

    std::string nearby_ticket;
    while (std::getline(input, nearby_ticket)) {
        auto nearby_ticket_fields = split_string(nearby_ticket, ",");

        for (auto &x : nearby_ticket_fields) {
            bool in_range = false;
            int current_field = std::stoi(x);
            for (auto &field : notes_fields) {    /* bad variable naming */
                if (field.in_range(current_field)) {
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
