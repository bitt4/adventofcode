#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

std::vector<std::string> split_string(std::string s,
                                      const std::string delim = " ",
                                      std::vector<std::string> acc = {}) {
    auto pos = s.find(delim);
    if (pos != std::string::npos) {
        acc.push_back(s.substr(0, pos));
        return split_string(s.substr(pos + delim.length()), delim, acc);
    } else {
        acc.push_back(s);
        return acc;
    }
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::vector<std::string> ingredients;
    std::map<std::string, std::set<std::string>> allergen_to_ings;

    std::string line;
    while (std::getline(input, line)) {
        auto ings_and_algs = split_string(line, " (contains ");
        auto ings = split_string(ings_and_algs[0]);
        ingredients.insert(ingredients.end(), ings.begin(), ings.end());

        auto algs = split_string(ings_and_algs[1], ", ");
        algs.back().pop_back();

        auto ing_set_1 = std::set(ings.begin(), ings.end());

        for (const auto& alg : algs) {
            if (allergen_to_ings.contains(alg)) {
                const auto& ing_set_2 = allergen_to_ings[alg];
                std::set<std::string> common_ings;
                std::set_intersection(ing_set_1.begin(), ing_set_1.end(),
                                      ing_set_2.begin(), ing_set_2.end(),
                                      std::inserter(common_ings, common_ings.begin()));
                allergen_to_ings[alg] = common_ings;
            } else {
                allergen_to_ings[alg] = ing_set_1;
            }
        }
    }

    std::set<std::string> possibly_contains_allergen;
    for (const auto& [_, ings] : allergen_to_ings) {
        possibly_contains_allergen.insert(ings.begin(), ings.end());
    }

    uint64_t part1 = 0;
    for (const auto& ing : ingredients) {
        if (!possibly_contains_allergen.contains(ing)) {
            part1++;
        }
    }

    std::cout << "part 1: " << part1 << '\n';

    std::vector<std::pair<std::string, std::string>> alg_to_ing_complete;
    alg_to_ing_complete.reserve(allergen_to_ings.size());

    while (alg_to_ing_complete.size() < allergen_to_ings.size()) {
        for (const auto& [alg, ings] : allergen_to_ings) {
            if (ings.size() == 1) {
                auto ing = *ings.begin();
                alg_to_ing_complete.push_back({ alg, ing });

                for (auto& [_, other_ings] : allergen_to_ings) {
                    other_ings.erase(ing);
                }
            }
        }
    }

    std::sort(alg_to_ing_complete.begin(), alg_to_ing_complete.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    std::string part2;
    for (const auto& [_, alg] : alg_to_ing_complete) {
        part2 += alg + ',';
    }
    part2.pop_back();

    std::cout << "part 2: " << part2 << '\n';

    return 0;
}
