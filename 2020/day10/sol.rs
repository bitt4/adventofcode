use std::collections::BTreeSet;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let adapters: BTreeSet<_> = input
        .lines()
        .map(|line| line.parse::<u64>().unwrap())
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

    let mut dp: Vec<u64> = vec![0; (*adapters.iter().last().unwrap() + 1) as usize];
    dp[0] = 1;

    adapters.iter().for_each(|&d| {
        let d = d as usize;
        dp[d] = dp.iter().rev().skip(dp.len() - d).take(3).sum();
    });

    println!("part 2: {}", dp.last().unwrap());
}
