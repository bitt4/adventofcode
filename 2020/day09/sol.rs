use std::fs;
use std::ops::ControlFlow;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let numbers: Vec<_> = input
        .lines()
        .map(|line| line.parse::<i64>().unwrap())
        .collect();

    let invalid_number = numbers
        .iter()
        .by_ref()
        .skip(25)
        .enumerate()
        .take_while(|(i, _)| i <= &(numbers.len() - 25))
        .try_for_each(|(i, n)| {
            let preamble = &numbers[i..i + 25];
            let found = preamble
                .iter()
                .any(|&p| preamble.contains(&(n - p).abs()) && p != n - p);
            if !found {
                return ControlFlow::Break(n);
            }
            ControlFlow::Continue(())
        });

    let invalid_number = if let ControlFlow::Break(inv) = invalid_number {
        *inv
    } else {
        -1
    };

    println!("part 1: {}", invalid_number);

    let mut prefix_sum = Vec::with_capacity(numbers.len() + 1);
    prefix_sum.push(0);

    numbers.iter().enumerate().for_each(|(i, n)| {
        prefix_sum.push(prefix_sum[i] + n);
    });

    let mut l = 0;
    let mut r = 1;
    let mut set_sum = prefix_sum[r] - prefix_sum[l];
    while invalid_number != set_sum {
        if invalid_number > set_sum {
            r += 1;
        } else {
            l += 1;
        }
        set_sum = prefix_sum[r] - prefix_sum[l];
    }

    let min = *numbers[l..=r - 1].iter().min().unwrap();
    let max = *numbers[l..=r - 1].iter().max().unwrap();

    println!("part 2: {}", min + max);
}
