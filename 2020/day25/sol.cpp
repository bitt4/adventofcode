#include <fstream>
#include <iostream>

using u64 = uint64_t;

u64 transform(u64 subject_number, int loop_size, int mod) {
    u64 value = 1;
    for (int i = 0; i < loop_size; ++i) {
        value = (value * subject_number) % mod;
    }

    return value;
}

int bruteforce_card_loop_size(u64 card_pub_key, int mod) {
    constexpr int card_subject_number = 7;
    int loop_size = 0;

    u64 value = 1;
    while (value != card_pub_key) {
        value = (value * transform(card_subject_number, 1, mod)) % mod;
        loop_size++;
    }

    return loop_size;
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::string line;
    std::getline(input, line);
    u64 card_pub_key = std::stoull(line);

    std::getline(input, line);
    u64 door_pub_key = std::stoull(line);

    constexpr int mod = 20201227;

    int card_loop_size = bruteforce_card_loop_size(card_pub_key, mod);
    u64 encryption_key = transform(door_pub_key, card_loop_size, mod);

    std::cout << "part 1: " << encryption_key << '\n';

    return 0;
}
