use std::collections::HashMap;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut numbers: HashMap<_, _> = input
        .split(',')
        .enumerate()
        .map(|(i, line)| (line.parse::<u32>().unwrap() as usize, i + 1))
        .collect();

    let mut last = 0;

    for turn in numbers.len() + 1..30_000_000 {
        if !numbers.contains_key(&last) {
            numbers.insert(last, turn);
            last = 0;
        } else {
            let tmp = last;
            last = turn - numbers[&last];
            numbers.insert(tmp, turn);
        }

        if turn == 2020 - 1 {
            println!("part 1: {}", last);
        }
    }

    println!("part 2: {}", last);
}
