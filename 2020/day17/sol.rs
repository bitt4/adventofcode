use std::fs;

type V4 = (i32, i32, i32, i32);
type Grid4d = [[[[u8; 20]; 20]; 13]; 13];

fn get_nearby_cubes(grid: &Grid4d, (x, y, z, w): V4, four_dim: bool) -> usize {
    let mut count = 0;

    let (from, to) = if four_dim { (-1, 1) } else { (0, 0) };
    for dw in from..=to {
        for dz in -1..=1 {
            for dy in -1..=1 {
                for dx in -1..=1 {
                    if (dw, dz, dy, dx) == (0, 0, 0, 0) {
                        continue;
                    }

                    let (nw, nz, ny, nx) = (w + dw, z + dz, y + dy, x + dx);
                    if nw < 0 || nz < 0 || ny < 0 || nx < 0 {
                        continue;
                    }

                    let (nw, nz, ny, nx) = (nw as usize, nz as usize, ny as usize, nx as usize);
                    if nw >= grid.len()
                        || nz >= grid[0].len()
                        || ny >= grid[0][0].len()
                        || nx >= grid[0][0][0].len()
                    {
                        continue;
                    }

                    if grid[nw][nz][ny][nx] == b'#' {
                        count += 1;
                    }
                }
            }
        }
    }

    count
}

fn cycle(grid: &Grid4d, four_dim: bool) -> Grid4d {
    let mut next_state: Grid4d = [[[[0; 20]; 20]; 13]; 13];

    let (from, to) = if four_dim { (0, grid.len()) } else { (6, 7) };
    for w in from..to {
        for z in 0..grid[0].len() {
            for y in 0..grid[0][0].len() {
                for x in 0..grid[0][0][0].len() {
                    let nearby =
                        get_nearby_cubes(grid, (x as i32, y as i32, z as i32, w as i32), four_dim);

                    let current_cube = grid[w][z][y][x];
                    let next_cube = &mut next_state[w][z][y][x];

                    if current_cube == b'#' {
                        if (2..=3).contains(&nearby) {
                            *next_cube = b'#';
                        } else {
                            *next_cube = b'.';
                        }
                    } else if nearby == 3 {
                        *next_cube = b'#';
                    } else {
                        *next_cube = b'.';
                    }
                }
            }
        }
    }

    next_state
}

fn count_active(grid: &Grid4d, four_dim: bool) -> usize {
    // if we count only in 3 dimensions, we can skip other 3d cubes
    let (from, to) = if four_dim { (0, grid.len()) } else { (6, 7) };

    grid.iter()
        .skip(from)
        .take(to - from)
        .flatten()
        .flatten()
        .flatten()
        .filter(|&c| c == &b'#')
        .count()
}

fn simulate(mut grid: Grid4d, four_dim: bool) -> usize {
    for _ in 0..6 {
        grid = cycle(&grid, four_dim);
    }

    count_active(&grid, four_dim)
}

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut grid: Grid4d = [[[[0; 20]; 20]; 13]; 13];
    input.lines().enumerate().for_each(|(y, line)| {
        line.chars().enumerate().for_each(|(x, c)| {
            grid[6][6][y + 6][x + 6] = c as u8;
        });
    });

    println!("part 1: {}", simulate(grid, false));
    println!("part 2: {}", simulate(grid, true));
}
