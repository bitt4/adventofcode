use std::convert::TryInto;
use std::fs;

enum Operation {
    Jmp,
    Acc,
    Nop,
}

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let instructions: Vec<_> = input
        .lines()
        .map(|line| {
            let (operation, argument) = line.split_once(' ').unwrap();
            let operation = match operation {
                "jmp" => Operation::Jmp,
                "acc" => Operation::Acc,
                _ => Operation::Nop,
            };
            let argument = argument.parse::<i32>().unwrap();
            (operation, argument)
        })
        .collect();

    let part1 = if let Err(result) = run_instructions(&instructions, None) {
        result
    } else {
        -1
    };

    println!("part 1: {}", part1);

    let mut part2 = 0;
    for i in 0..instructions.len() {
        let result = run_instructions(&instructions, Some(&(i as i32)));
        if let Ok(value) = result {
            part2 = value;
            break;
        }
    }

    println!("part 2: {}", part2);
}

fn run_instructions(
    instructions: &[(Operation, i32)],
    bad_instruction_offset: Option<&i32>,
) -> Result<i32, i32> {
    let mut acc = 0;
    let mut ip: i32 = 0;

    let mut executed = vec![false; instructions.len()];

    let mut swap = -1;
    if let Some(offset) = bad_instruction_offset {
        swap = *offset;
    }

    while !executed.get(ip as usize).unwrap() {
        let (operation, argument) = &instructions[ip as usize];

        match operation {
            Operation::Acc => acc += argument,
            Operation::Jmp => {
                if swap == -1 || ip != swap {
                    ip += argument - 1;
                }
            }
            _ => {
                if swap != -1 && ip == swap {
                    ip += argument - 1;
                }
            }
        }
        executed[ip as usize] = true;
        ip += 1;

        if ip >= instructions.len().try_into().unwrap() {
            return Ok(acc);
        }
    }

    Err(acc)
}
