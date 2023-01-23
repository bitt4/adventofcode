#include <deque>
#include <fstream>
#include <iostream>
#include <set>

using Deck = std::deque<int>;

enum class Player : uint8_t {
    Player1,
    Player2
};

Deck combat(Deck deck1, Deck deck2) {
    while (deck1.size() && deck2.size()) {
        int card1 = deck1.front();
        deck1.pop_front();
        int card2 = deck2.front();
        deck2.pop_front();

        if (card1 > card2) {
            deck1.push_back(card1);
            deck1.push_back(card2);
        } else {
            deck2.push_back(card2);
            deck2.push_back(card1);
        }
    }

    if (deck2.empty()) {
        return deck1;
    } else {
        return deck2;
    }
}

std::pair<Deck, Player> recursive_combat(Deck deck1, Deck deck2) {
    std::set<std::pair<Deck, Deck>> past_rounds;

    while (deck1.size() && deck2.size()) {
        if (past_rounds.contains({ deck1, deck2 })) {
            return { deck1, Player::Player1 };
        }

        past_rounds.insert({ deck1, deck2 });

        int card1 = deck1.front();
        deck1.pop_front();
        int card2 = deck2.front();
        deck2.pop_front();

        Player winner;
        if (std::ssize(deck1) >= card1 && std::ssize(deck2) >= card2) {
            Deck new_deck1(deck1.begin(), deck1.begin() + card1);
            Deck new_deck2(deck2.begin(), deck2.begin() + card2);

            auto [winning_deck, subwinner] = recursive_combat(new_deck1, new_deck2);
            winner = subwinner;
        } else {
            if (card1 > card2) {
                winner = Player::Player1;
            } else {
                winner = Player::Player2;
            }
        }

        if (winner == Player::Player1) {
            deck1.push_back(card1);
            deck1.push_back(card2);
        } else {
            deck2.push_back(card2);
            deck2.push_back(card1);
        }
    }

    if (deck2.empty()) {
        return { deck1, Player::Player1 };
    } else {
        return { deck2, Player::Player2 };
    }
}

uint64_t score(const Deck& deck) {
    uint64_t s = 0;

    int i = 1;
    for (auto it = deck.rbegin(); it != deck.rend(); ++it, ++i) {
        s += *it * i;
    }

    return s;
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    Deck deck1;

    std::string line;

    // parse deck of player 1
    std::getline(input, line); // consume "Player 1:" string
    while (std::getline(input, line) && !line.empty()) {
        deck1.push_back(std::stoi(line));
    }

    Deck deck2;

    // parse deck of player 2 (crab)
    std::getline(input, line); // consume "Player 2:" string
    while (std::getline(input, line)) {
        deck2.push_back(std::stoi(line));
    }

    {
        auto winning_deck = combat(deck1, deck2);
        uint64_t part1 = score(winning_deck);

        std::cout << "part 1: " << part1 << '\n';
    }

    auto [winning_deck, _] = recursive_combat(deck1, deck2);

    uint64_t part2 = score(winning_deck);

    std::cout << "part 2: " << part2 << '\n';

    return 0;
}
