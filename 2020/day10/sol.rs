use std::collections::BTreeSet;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let adapters: BTreeSet<_> = input
        .lines()
        .map(|line| line.parse::<u32>().unwrap())
        .collect();

    let mut one_jold_diff = 0;
    let mut three_jold_diff = 1; // built-in joltage adapter
    let mut last_adapter = 0;

    adapters.iter().for_each(|&adapter| {
        let difference = adapter - last_adapter;
        if difference == 1 {
            one_jold_diff += 1;
        } else if difference == 3 {
            three_jold_diff += 1;
        }
        last_adapter = adapter;
    });

    println!("part 1: {}", one_jold_diff * three_jold_diff);
}
