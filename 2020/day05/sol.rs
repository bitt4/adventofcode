use std::collections::HashSet;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let seat_ids: Vec<_> = input.lines().map(seat_id).collect();
    let max_seat_id = seat_ids.iter().by_ref().max().unwrap();

    println!("part 1: {}", max_seat_id);

    let seats: HashSet<_> = seat_ids.iter().cloned().collect();
    let min_seat_id = seat_ids.iter().by_ref().min().unwrap();

    (min_seat_id + 1..max_seat_id - 1).for_each(|i| {
        if seats.contains(&(i - 1)) && !seats.contains(&i) && seats.contains(&(i + 1)) {
            println!("part 2: {}", i);
        }
    });
}

fn seat_id(boarding_pass: &str) -> u32 {
    let mut boarding_pass_chars = boarding_pass.chars();
    let row: u32 = boarding_pass_chars
        .by_ref()
        .take(7)
        .enumerate()
        .map(|(i, c)| match c {
            'B' => 1 << (6 - i),
            _ => 0,
        })
        .sum();

    let column: u32 = boarding_pass_chars
        .take(3)
        .enumerate()
        .map(|(i, c)| match c {
            'R' => 1 << (2 - i),
            _ => 0,
        })
        .sum();

    row * 8 + column
}
