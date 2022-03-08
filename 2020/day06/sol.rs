use std::collections::HashMap;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let groups: Vec<_> = input
        .split("\n\n")
        .map(|group| {
            let mut answers: HashMap<char, _> = HashMap::new();
            group
                .chars()
                .filter(|&c| c != '\n')
                .for_each(|c| *answers.entry(c).or_insert(0) += 1);
            (answers, group.lines().count())
        })
        .collect();

    let part1: usize = groups.iter().map(|(group, _)| group.len()).sum();
    println!("part 1: {}", part1);

    let part2: usize = groups
        .iter()
        .map(|(group, people)| group.iter().filter(|(_, value)| *value == people).count())
        .sum();
    println!("part 2: {}", part2);
}
