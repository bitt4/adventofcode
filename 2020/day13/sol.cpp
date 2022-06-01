#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using u64 = uint64_t;

std::vector<std::string> split_string (const std::string& target, char delimeter = ' ') {
    std::vector<std::string> out;
    size_t last_delimeter = 0;

    while (true) {
        auto i = target.find(delimeter, last_delimeter);
        if (i == std::string::npos) {
            out.push_back(target.substr(last_delimeter));
            break;
        }
        out.push_back(target.substr(last_delimeter, i - last_delimeter));
        last_delimeter = i + 1;
    }

    return out;
}

int main(){
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    u64 earliest;
    std::string line;

    input >> earliest;
    input >> line;

    input.close();

    auto timings = split_string(line, ',');
    std::vector<std::pair<size_t, u64>> buses;
    for (size_t i = 0; i < timings.size(); ++i) {
        if(timings[i] != "x") {
            buses.emplace_back(i, stoull(timings[i]));
        }
    }

    u64 min = UINT64_MAX;    /* 2^64 - 1 */
    u64 nearest;
    u64 first_bus = 0;
    for (const auto& bus : buses) {
        auto id = bus.second;
        nearest = earliest / id * id + id;
        if (nearest < min) {
            min = nearest;
            first_bus = id;
        }
    }

    std::cout << "part 1: " << first_bus * (min - earliest) << '\n';

    u64 time = 0;
    u64 step = buses[0].second;

    buses.erase(buses.begin());
    for (const auto& bus : buses) {
        auto i = bus.first;
        auto id = bus.second;
        while ((time + i) % id != 0) {
            time += step;
        }
        step *= id;
    }

    std::cout << "part 2: " << time << '\n';

    return 0;
}
