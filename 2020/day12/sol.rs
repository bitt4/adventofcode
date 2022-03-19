use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let instructions: Vec<_> = input
        .lines()
        .map(|line| {
            let (action, value) = line.split_at(1);
            let action = action.chars().next().unwrap();
            let value = value.parse::<i32>().unwrap();
            (action, value)
        })
        .collect();

    let mut north = 0;
    let mut east = 0;
    let mut direction = 90;

    instructions
        .iter()
        .for_each(|&(action, value)| match action {
            'N' => north += value,
            'S' => north -= value,
            'E' => east += value,
            'W' => east -= value,
            'L' => {
                direction += 360 - value;
                direction %= 360;
            }
            'R' => {
                direction += value;
                direction %= 360;
            }
            'F' => match direction {
                0 => north += value,
                90 => east += value,
                180 => north -= value,
                270 => east -= value,
                _ => {}
            },
            _ => {}
        });

    println!("part 1: {}", north.abs() + east.abs());

    let mut waypoint_x = 10;
    let mut waypoint_y = 1;
    let mut ship_x = 0;
    let mut ship_y = 0;

    instructions
        .iter()
        .for_each(|&(action, value)| match action {
            'N' => waypoint_y += value,
            'S' => waypoint_y -= value,
            'E' => waypoint_x += value,
            'W' => waypoint_x -= value,
            'L' => {
                for _ in 0..value / 90 {
                    core::mem::swap(&mut waypoint_x, &mut waypoint_y);
                    waypoint_x = -waypoint_x;
                }
            }
            'R' => {
                for _ in 0..value / 90 {
                    core::mem::swap(&mut waypoint_x, &mut waypoint_y);
                    waypoint_y = -waypoint_y;
                }
            }
            'F' => {
                ship_x += value * waypoint_x;
                ship_y += value * waypoint_y;
            }
            _ => {}
        });

    println!("part 2: {}", ship_x.abs() + ship_y.abs());
}
