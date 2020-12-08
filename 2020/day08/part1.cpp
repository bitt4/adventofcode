#include <iostream>
#include <vector>

/* from day02 */
std::vector<std::string> split_string(std::string target, char delimeter = ' '){
    std::vector<std::string> out;
    int position = 0;
    size_t length = target.length();

    for(size_t i = 0; i < length; i++){
        if(target[i] == delimeter){
            out.push_back(std::string(target, position, i - position));
            position = i+1;
            continue;
        }
        if(i == length - 1){
            out.push_back(std::string(target, position, length - position));
        }
    }

    return out;
}

/* maybe kinda useless when there are only 3 instructions */
enum INSTRUCTION_TYPE {
                       JMP,
                       ACC,
                       NOP
};

int get_instruction_type(std::string inst){
    if(inst == "jmp"){
        return JMP;
    }
    else if(inst == "acc"){
        return ACC;
    }
    return NOP;
}

int main(){
    std::vector<std::string> instructions;
    instructions.resize(591);

    bool has_been_executed[591] = {};

    for(int i = 0; i < 591; i++){
        std::getline(std::cin, instructions[i]);
    }

    int acc = 0;    /* accumulator */
    int ip = 0;     /* instruction pointer */

    while(true){
        if(has_been_executed[ip]){
            break;
        }
        else {
            has_been_executed[ip] = true;
        }

        std::string line = instructions[ip];
        auto inst_arg = split_string(line);
        std::string inst = inst_arg[0];
        int arg = std::stoi(inst_arg[1]);

        switch(get_instruction_type(inst)){
            case JMP:
                ip += arg;
                break;
            case ACC:
                acc += arg;
            case NOP:
            default:
                ip++;
        }
    }

    std::cout << acc << '\n';

    return 0;
}
