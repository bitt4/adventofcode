#include <fstream>
#include <iostream>
#include <vector>

/* from day02 */
std::vector<std::string> split_string(const std::string& target, char delimeter = ' ') {
    std::vector<std::string> out;
    int position = 0;
    size_t length = target.length();

    for (size_t i = 0; i < length; i++) {
        if (target[i] == delimeter) {
            out.push_back(std::string(target, position, i - position));
            position = i+1;
            continue;
        }
        if (i == length - 1) {
            out.push_back(std::string(target, position, length - position));
        }
    }

    return out;
}

/* maybe kinda useless when there are only 3 instructions */
enum Instruction {
                  JMP,
                  ACC,
                  NOP
};

Instruction get_instruction_type(const std::string& inst) {
    if (inst == "jmp") {
        return JMP;
    } else if (inst == "acc") {
        return ACC;
    }
    return NOP;
}

int run(const std::vector<std::string>& instructions, int64_t repair_index = -1) {
    int acc = 0;             /* accumulator */
    unsigned int ip = 0;     /* instruction pointer */

    bool *has_been_executed = new bool[ instructions.size() ]();

    while (ip < instructions.size()) {
        if (has_been_executed[ip]) {
            if (repair_index == -1) {
                break;
            } else {
                delete[] has_been_executed;
                return run(instructions, repair_index + 1);
                // if emulated program terminates (executes
                // instruction after the last one), it'll exit this
                // while loop and return acc
            }
        } else {
            has_been_executed[ip] = true;
        }

        std::string line = instructions[ip];
        auto inst_arg = split_string(line);
        auto inst = get_instruction_type(inst_arg[0]);
        int arg = std::stoi(inst_arg[1]);

        if (repair_index != -1 &&
            repair_index == ip) {
            if (inst == JMP) {
                inst = NOP;
            } else if (inst == NOP) {
                inst = JMP;
            }
        }

        switch (inst) {
            case JMP:
                ip += arg;
                break;
            case ACC:
                acc += arg;
                [[fallthrough]];
            case NOP:
            default:
                ip++;
        }
    }

    delete[] has_been_executed;
    return acc;
}

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::vector<std::string> instructions;
    instructions.reserve(591);

    std::string line;
    while (std::getline(input, line)) {
        instructions.push_back(line);
    }

    int part1 = run(instructions);
    int part2 = run(instructions, 0);

    std::cout << "part 1: " << part1 << '\n';
    std::cout << "part 2: " << part2 << '\n';

    return 0;
}
