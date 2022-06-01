#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> split(std::string s, const std::string delim, std::vector<std::string> acc = {}) {
    auto pos = s.find(delim);
    if (pos != std::string::npos) {
        acc.push_back(s.substr(0, pos));
        return split(s.substr(pos + delim.length()), delim, acc);
    } else {
        acc.push_back(s);
        return acc;
    }
}

struct Bag {
    std::string color;
    bool searched = false;
    std::vector<Bag*> parents;
    std::vector<std::pair<int, Bag*>> children;

    int parents_count() {
        int count = 0;
        for (auto& parent : parents) {
            if (!parent->searched) {
                count++;
            }
            parent->searched = true;
            count += parent->parents_count();
        }

        return count;
    }

    int children_sum() {
        int sum = 0;
        for (auto& child : children) {
            int amount = child.first;
            sum += amount;
            sum += amount * child.second->children_sum();
        }
        return sum;
    }
};

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::map<std::string, Bag*> bags;

    auto get_bag = [&bags](std::string color) {
        if (bags.find(color) != bags.end()) {
            return bags[color];
        } else {
            auto bag = new Bag();
            bag->color = color;
            bags.insert({ color, bag });
            return bag;
        }
    };

    std::string line;
    while (std::getline(input, line)) {
        const std::string split_by = " bags contain ";
        auto pos = line.find(split_by);
        std::string color = line.substr(0, pos);
        std::string rule = line.substr(pos + split_by.length());
        auto contains = split(rule, ", ");

        for (const auto& bag : contains) {
            auto first_space = bag.find(' ');
            auto last_space = bag.rfind(' ');
            auto amount_str = bag.substr(0, first_space);
            auto child_bag_color = bag.substr(first_space + 1, last_space - first_space - 1);
            auto amount = 0;

            if (amount_str != "no") {
                amount = std::stoi(amount_str);
            }
            if (child_bag_color == "other") {
                child_bag_color.clear();
            }

            auto current_bag = get_bag(color);
            auto child_bag = get_bag(child_bag_color);

            current_bag->children.push_back({ amount, child_bag });
            child_bag->parents.push_back(current_bag);
        }
    }

    std::cout << "part 1: " << bags["shiny gold"]->parents_count() << '\n';
    std::cout << "part 2: " << bags["shiny gold"]->children_sum() << '\n';

    return 0;
}
