use std::collections::HashSet;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let numbers = input
        .lines()
        .map(|line| line.parse().expect("Not an integer."))
        .collect::<HashSet<i32>>();

    for n in &numbers {
        if let Some(value) = numbers.get(&(2020 - n)) {
            println!("part 1: {}", n * value);
            break;
        }
    }

    let mut i = numbers.iter();
    'base: while let Some(n1) = i.next() {
        let mut j = i.clone().skip(1);
        for n2 in &mut j {
            if let Some(n3) = numbers.get(&(2020 - n1 - n2)) {
                println!("part 2: {}", n1 * n2 * n3);
                break 'base;
            }
        }
    }
}
