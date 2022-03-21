use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut lines_iter = input.lines();
    let earliest_timestamp = lines_iter.next().unwrap().parse::<usize>().unwrap();

    let bus_ids: Vec<_> = lines_iter
        .next()
        .unwrap()
        .split(',')
        .map(|id| {
            if let Ok(id) = id.parse::<usize>() {
                Some(id)
            } else {
                None
            }
        })
        .collect();

    let (best_time, best_id) = bus_ids
        .iter()
        .filter_map(|id| id.map(|id| (earliest_timestamp + id - earliest_timestamp % id, id)))
        .min()
        .unwrap();

    println!("part 1: {}", (best_time - earliest_timestamp) * best_id);

    let mut time = 0;
    let mut step = bus_ids.first().unwrap().unwrap();

    bus_ids
        .iter()
        .enumerate()
        .filter(|(_, id)| id.is_some())
        .skip(1)
        .for_each(|(i, id)| {
            let id = id.unwrap();
            while (time + i) % id != 0 {
                time += step;
            }
            step *= id;
        });

    println!("part 2: {}", time);
}
