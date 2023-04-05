use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut part1 = 0;
    let mut part2 = 0;

    input.lines().for_each(|line| {
        let tokens = line.split_whitespace().collect::<Vec<_>>();

        let range = tokens[0];
        let rule = tokens[1].chars().next().unwrap();
        let password = tokens[2];

        let (from, to): (usize, usize) = range
            .split_once('-')
            .map(|(n1, n2)| (n1.parse().unwrap(), n2.parse().unwrap()))
            .unwrap();

        let character_occurences = password.chars().filter(|c| c == &rule).count();

        if from <= character_occurences && character_occurences <= to {
            part1 += 1;
        }

        if (password.chars().nth(from - 1).unwrap() == rule)
            ^ (password.chars().nth(to - 1).unwrap() == rule)
        {
            part2 += 1;
        }
    });

    println!("part 1: {}", part1);
    println!("part 2: {}", part2);
}
