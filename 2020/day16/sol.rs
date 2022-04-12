use std::collections::HashMap;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut lines = input.lines();

    let rules: HashMap<_, _> = lines
        .by_ref()
        .take(20)
        .map(|line| {
            let (field, ranges) = line.split_once(": ").unwrap();
            let (range1, range2) = ranges.split_once(" or ").unwrap();
            let (l1, r1) = range1.split_once('-').unwrap();
            let (l1, r1) = (l1.parse::<u32>().unwrap(), r1.parse::<u32>().unwrap());
            let (l2, r2) = range2.split_once('-').unwrap();
            let (l2, r2) = (l2.parse::<u32>().unwrap(), r2.parse::<u32>().unwrap());
            (field, [(l1, r1), (l2, r2)])
        })
        .collect();

    let _my_ticket: Vec<_> = lines
        .by_ref()
        .skip(2)
        .next()
        .unwrap()
        .split(',')
        .map(|n| n.parse::<u32>().unwrap())
        .collect();

    let tickets: Vec<_> = lines
        .skip(2)
        .map(|line| {
            line.split(',')
                .map(|n| n.parse::<u32>().unwrap())
                .collect::<Vec<_>>()
        })
        .collect();

    let part1: u32 = tickets
        .iter()
        .map(|ticket| passes_rules(&ticket, &rules.values().collect::<Vec<_>>()))
        .sum();

    println!("part 1: {}", part1);
}

fn passes_rules(ticket: &Vec<u32>, rules: &Vec<&[(u32, u32); 2]>) -> u32 {
    ticket
        .iter()
        .filter(|&number| {
            !rules.iter().any(|&rule| {
                rule.iter()
                    .any(|&range| range.0 <= *number && *number <= range.1)
            })
        })
        .sum()
}
