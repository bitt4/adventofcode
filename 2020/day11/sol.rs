use std::convert::TryInto;
use std::fs;

fn valid_coordinates(x: i32, y: i32, width: i32, height: i32) -> bool {
    0 <= x && x < width && 0 <= y && y < height
}

fn get_nearby_seats(seats: &Vec<Vec<u8>>, x: i32, y: i32) -> usize {
    let mut nearby_seats = 0;

    for rx in -1..=1 {
        for ry in -1..=1 {
            if rx == 0 && ry == 0 {
                continue;
            }
            let current_x = x + rx;
            let current_y = y + ry;

            if let (Ok(nx), Ok(ny), true) = (
                TryInto::<usize>::try_into(current_x),
                TryInto::<usize>::try_into(current_y),
                valid_coordinates(
                    current_x,
                    current_y,
                    seats[0].len() as i32,
                    seats.len() as i32,
                ),
            ) {
                if seats[ny][nx] == b'#' {
                    nearby_seats += 1;
                }
            }
        }
    }

    nearby_seats
}

fn get_visible_seats(seats: &Vec<Vec<u8>>, x: i32, y: i32) -> usize {
    let mut visible_seats = 0;

    for rx in -1..=1 {
        for ry in -1..=1 {
            if rx == 0 && ry == 0 {
                continue;
            }
            let mut current_x = x + rx;
            let mut current_y = y + ry;

            while let (Ok(nx), Ok(ny), true) = (
                TryInto::<usize>::try_into(current_x),
                TryInto::<usize>::try_into(current_y),
                valid_coordinates(
                    current_x,
                    current_y,
                    seats[0].len() as i32,
                    seats.len() as i32,
                ),
            ) {
                if seats[ny][nx] == b'#' {
                    visible_seats += 1;
                    break;
                } else if seats[ny][nx] == b'L' {
                    break;
                } else {
                    current_x += rx;
                    current_y += ry;
                }
            }
        }
    }

    visible_seats
}

fn occupied_seats(
    mut seats: Vec<Vec<u8>>,
    f: fn(&Vec<Vec<u8>>, i32, i32) -> usize,
    tolerancy_limit: usize,
) -> usize {
    let mut seats_swap = seats.clone();

    loop {
        for y in 0..seats.len() {
            for x in 0..seats[0].len() {
                let adjacent = f(&seats_swap, x as i32, y as i32);
                if seats_swap[y][x] == b'L' && adjacent == 0 {
                    seats[y][x] = b'#';
                } else if seats_swap[y][x] == b'#' && adjacent >= tolerancy_limit {
                    seats[y][x] = b'L';
                }
            }
        }

        if seats == seats_swap {
            break;
        }

        seats_swap = seats.clone();
    }

    seats
        .iter()
        .map(|s| s.iter().filter(|&c| c == &b'#').count())
        .sum()
}

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let seats = input
        .lines()
        .map(|s| s.as_bytes().to_vec())
        .collect::<Vec<_>>();

    println!(
        "part 1: {}",
        occupied_seats(seats.clone(), get_nearby_seats, 4)
    );
    println!("part 2: {}", occupied_seats(seats, get_visible_seats, 5));
}
