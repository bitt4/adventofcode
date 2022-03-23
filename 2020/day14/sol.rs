use std::collections::HashMap;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut memory: HashMap<u64, u64> = HashMap::new();
    let mut mask: String = String::new();

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

            memory.insert(address, apply_mask(value, &mask));
        }
    });

    let memory_sum: u64 = memory.values().sum();

    println!("part 1: {}", memory_sum);
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
