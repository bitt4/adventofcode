#include <fstream>
#include <iostream>
#include <vector>

using u64 = uint64_t;

std::vector<std::string> tokenize(std::string expr) {
    std::vector<std::string> out = {};

    u64 pos = 0;
    u64 last = 0;
    while (pos < expr.length()) {
        if (expr[pos] == '(') {
            int paren = 1;
            while (paren != 0) {
                pos++;
                if (expr[pos] == '(') {
                    paren++;
                } else if (expr[pos] == ')') {
                    paren--;
                }
            }
        }
        if (expr[pos] == ' ') {
            out.push_back(expr.substr(last, pos - last));
            last = pos + 1;
        }
        pos++;
        if (pos >= expr.length()) {
            out.push_back(expr.substr(last));
        }
    }

    return out;
}

std::string remove_parens(const std::string& s) {
    return s.substr(1, s.length() - 2);
}

u64 eval(std::string line) {
    auto tokens = tokenize(line);
    auto& first_token = tokens[0];
    u64 acc = [first_token]() {
        if (first_token[0] == '(') {
            return eval(remove_parens(first_token));
        } else {
            return std::stoul(first_token);
        }
    }();

    for (size_t i = 1; i < tokens.size(); i += 2) {
        auto op = tokens[i];
        auto value = [i, &tokens]() {
            auto& expr = tokens[i + 1];
            if (expr[0] == '(') {
                return eval(remove_parens(expr));
            } else {
                return std::stoul(expr);
            }
        }();

        if (op == "+") {
            acc += value;
        } else {
            acc *= value;
        }
    }

    return acc;
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    u64 sum = 0;
    std::string line;
    while (std::getline(input, line)) {
        sum += eval(line);
    }

    std::cout << "part 1: " << sum << '\n';

    return 0;
}
