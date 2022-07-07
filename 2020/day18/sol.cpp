#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
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
    u64 acc = [first_token]() -> u64 {
        if (first_token[0] == '(') {
            return eval(remove_parens(first_token));
        } else {
            return std::stoul(first_token);
        }
    }();

    for (size_t i = 1; i < tokens.size(); i += 2) {
        auto op = tokens[i];
        auto value = [i, &tokens]() -> u64 {
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

std::vector<std::string> split_string(std::string s, const std::string delim = " ", std::vector<std::string> acc = {}) {
    auto pos = s.find(delim);
    if (pos != std::string::npos) {
        acc.push_back(s.substr(0, pos));
        return split_string(s.substr(pos + delim.length()), delim, acc);
    } else {
        acc.push_back(s);
        return acc;
    }
}

u64 eval_with_precedence(std::string line) {
    // shunting yard algorithm
    std::stack<std::string> operators;
    std::queue<std::string> output;

    auto tokens = split_string(line);
    for (auto token : tokens) {
        if (token.find_first_not_of("0123456789") == std::string::npos) { // if the token is a number
            output.push(token);
        } else if (token[0] == '+' || token[0] == '*') {
            while (!operators.empty() && operators.top() == "+") {
                output.push("+");
                operators.pop();
            }
            operators.push(token);
        } else if (token[0] == '(') {
            auto digit_position = token.find_first_of("0123456789");
            for (size_t i = 0; i < digit_position; ++i) {
                operators.push("(");
            }
            output.push(token.substr(digit_position));
        } else if (token.find(')') != std::string::npos) {
            auto first_bracket_pos = token.find_first_not_of("0123456789");
            output.push(token.substr(0, first_bracket_pos));
            for (size_t i = first_bracket_pos; i < token.length(); ++i) {
                while (operators.top() != "(") {
                    output.push(operators.top());
                    operators.pop();
                }
                operators.pop();
            }
        }
    }

    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    std::stack<u64> execution;
    while (!output.empty()) {
        if (output.front() == "+" || output.front() == "*") {
            auto val1 = execution.top();
            execution.pop();
            auto val2 = execution.top();
            execution.pop();

            if (output.front() == "+") {
                val2 += val1;
            } else {
                val2 *= val1;
            }

            execution.push(val2);
        } else {
            execution.push(std::stoull(output.front()));
        }
        output.pop();
    }

    return execution.top();
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    u64 sum1 = 0;
    u64 sum2 = 0;
    std::string line;
    while (std::getline(input, line)) {
        sum1 += eval(line);
        sum2 += eval_with_precedence(line);
    }

    std::cout << "part 1: " << sum1 << '\n';
    std::cout << "part 2: " << sum2 << '\n';

    return 0;
}
