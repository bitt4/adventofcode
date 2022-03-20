use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut lines_iter = input.lines();
    let earliest_timestamp = lines_iter.next().unwrap().parse::<u32>().unwrap();

    let bus_ids: Vec<_> = lines_iter
        .next()
        .unwrap()
        .split(',')
        .map(|id| {
            if let Ok(id) = id.parse::<u32>() {
                Some(id)
            } else {
                None
            }
        })
        .collect();

    let (best_time, best_id) = bus_ids
        .iter()
        .filter_map(|id| {
            if let Some(id) = id {
                Some((earliest_timestamp + id - earliest_timestamp % id, id))
            } else {
                None
            }
        })
        .min()
        .unwrap();

    println!("part 1: {}", (best_time - earliest_timestamp) * best_id);
}
