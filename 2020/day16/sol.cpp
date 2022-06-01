#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using Ticket = std::vector<int>;

struct Rule {
    int min1,
        max1,
        min2,
        max2;

    bool is_valid(int num) const {
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

std::vector<int> string_vec_to_int_vec(std::vector<std::string> src) {
    std::vector<int> result;
    result.reserve(src.size());

    for (auto s : src) {
        result.push_back(std::stoi(s));
    }

    return result;
}

int main(){
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::vector<Rule> rules;

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

        Rule field {
            from1,
            to1,
            from2,
            to2
        };

        rules.push_back(field);
    }

    input.ignore();
    input.ignore(256, '\n');

    std::string my_ticket_raw;
    std::getline(input, my_ticket_raw);

    auto my_ticket = string_vec_to_int_vec(split_string(my_ticket_raw, ","));

    input.ignore();
    input.ignore(256, '\n');

    uint32_t error_rate = 0;

    std::vector<Ticket> almost_valid_tickets;

    std::string nearby_ticket_raw;
    while (std::getline(input, nearby_ticket_raw)) {
        auto nearby_ticket = string_vec_to_int_vec(split_string(nearby_ticket_raw, ","));

        bool has_valid_field = false;
        for (auto &current_field : nearby_ticket) {
            bool in_range = false;
            for (auto &rule : rules) {
                if (rule.is_valid(current_field)) {
                    in_range = true;
                    break;
                }
            }
            if (!in_range) {
                error_rate += current_field;
                break;
            }
            has_valid_field = true;
        }

        if (has_valid_field) {
            almost_valid_tickets.push_back(nearby_ticket);
        }
    }

    std::cout << "part 1: " << error_rate << '\n';

    std::vector<Ticket> valid_tickets;
    for (auto ticket : almost_valid_tickets) {
        bool all_fields_valid = true;
        for (auto &field : ticket) {
            bool valid_field = false;
            for (auto &rule : rules) {
                if (rule.is_valid(field)) {
                    valid_field = true;
                    break;
                }
            }
            if (!valid_field) {
                all_fields_valid = false;
                break;
            }
        }
        if (all_fields_valid) {
            valid_tickets.push_back(ticket);
        }
    }

    std::vector<uint32_t> possible_fields(rules.size());

    for (size_t i = 0; i < rules.size(); ++i) {
        for (size_t j = 0; j < rules.size(); ++j) {
            bool rule_passes = true;
            for (const auto& ticket : valid_tickets) {
                if (!rules[i].is_valid(ticket[j])) {
                    rule_passes = false;
                    break;
                }
            }
            if (rule_passes) {
                possible_fields[i] |= (1 << j);
            }
        }
    }

    uint32_t resolved = 0;
    for (size_t i = 0; i < rules.size() - 1; ++i) {
        for (size_t j = 0; j < possible_fields.size(); ++j) {
            auto field = possible_fields[j];
            if (__builtin_popcount(field) == 1) {
                if (!(resolved & field)) {
                    resolved |= field;
                    for (size_t k = 0; k < possible_fields.size(); ++k) {
                        if (k != j) {
                            possible_fields[k] &= ~field;
                        }
                    }
                }
            }
        }
    }

    uint64_t part2 = 1;
    for (int i = 0; i < 6; ++i) {    // i need only first 6 fields
        part2 *= my_ticket[__builtin_ctz(possible_fields[i])];
    }

    std::cout << "part 2: " << part2 << '\n';

    return 0;
}
