#include <fstream>
#include <iostream>

using u64 = uint64_t;

u64 transform(u64 subject_number, int loop_size, int mod) {
    u64 value = 1;
    subject_number %= mod;

    // binary exponentiation
    while (loop_size > 0) {
        if (loop_size & 1) {
            value = value * subject_number % mod;
        }
        subject_number = subject_number * subject_number % mod;
        loop_size >>= 1;
    }

    return value;
}

int bruteforce_card_loop_size(u64 card_pub_key, int mod) {
    constexpr int CARD_SUBJECT_NUMBER = 7;
    int loop_size = 0;

    u64 value = 1;
    while (value != card_pub_key) {
        value = (value * CARD_SUBJECT_NUMBER) % mod;
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

    constexpr int MOD = 20201227;

    int card_loop_size = bruteforce_card_loop_size(card_pub_key, MOD);
    u64 encryption_key = transform(door_pub_key, card_loop_size, MOD);

    std::cout << "part 1: " << encryption_key << '\n';

    return 0;
}
