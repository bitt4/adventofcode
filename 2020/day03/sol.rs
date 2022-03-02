use std::fs;

fn main() {
    let input = fs::read_to_string("input")
        .expect("Can't read puzzle input file.");

    let part_1 = part1(&input);
    let part_2 = part2(&input);
    println!("part 1: {}", part_1);
    println!("part 2: {}", part_2);
}

fn part1(map: &str) -> usize {
    let mut position: usize = 0;
    map.lines().filter(|line| {
        let result = line.chars().nth(position).unwrap() == '#';
        position = (position + 3) % line.len();
        result
    }).count()
}

fn part2(map: &str) -> usize {
    let traverse = |&(right, down)| {
        let mut position: usize = 0;
        map.lines()
            .step_by(down)
            .filter(|line| {
            let result = line.chars().nth(position).unwrap() == '#';
            position = (position + right) % line.len();
            result
        }).count()
    };
    let slopes = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)];
    slopes.iter()
        .map(traverse)
        .product()
}
