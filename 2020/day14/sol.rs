use std::collections::HashMap;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut memory: HashMap<u64, u64> = HashMap::new();
    let mut mask: String = String::new();
    let mut program: Vec<_> = Vec::new();

    input.lines().by_ref().for_each(|line| {
        if line.starts_with("mask") {
            let (_, value) = line.rsplit_once(' ').unwrap();
            mask = value.to_owned();
        } else {
            let (address, value) = line
                .split_once('[')
                .unwrap()
                .1
                .split_once("] = ")
                .map(|(a, v)| (a.parse::<u64>().unwrap(), v.parse::<u64>().unwrap()))
                .unwrap();

            program.push((address, value, mask.clone()));
            memory.insert(address, apply_mask(value, &mask));
        }
    });

    let memory_sum: u64 = memory.values().sum();

    println!("part 1: {}", memory_sum);

    memory.clear();

    program.iter().for_each(|(address, value, m)| {
        fill_memory(&mut memory, *address, *value, 36, m);
    });

    println!("part 2: {}", memory.values().sum::<u64>());
}

fn apply_mask(value: u64, mask: &str) -> u64 {
    let mut masked_value: u64 = value;

    mask.chars().enumerate().for_each(|(i, c)| match c {
        '0' => masked_value &= !(1 << (35 - i)),
        '1' => masked_value |= 1 << (35 - i),
        _ => {}
    });

    masked_value
}

fn fill_memory(memory: &mut HashMap<u64, u64>, address: u64, value: u64, index: usize, mask: &str) {
    if index == 0 {
        memory.insert(address, value);
        return;
    }

    let next_bit = mask.chars().nth(index - 1).unwrap();

    match next_bit {
        '0' => fill_memory(memory, address, value, index - 1, mask),
        '1' => fill_memory(
            memory,
            address | (1 << (36 - index)),
            value,
            index - 1,
            mask,
        ),
        'X' => {
            fill_memory(
                memory,
                address | (1 << (36 - index)),
                value,
                index - 1,
                mask,
            );
            fill_memory(
                memory,
                address & !(1 << (36 - index)),
                value,
                index - 1,
                mask,
            );
        }
        _ => {}
    }
}
