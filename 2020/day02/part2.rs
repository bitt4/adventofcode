fn main(){
    let mut valid_passwords: u32 = 0;

    for _ in 0..1000 {
        let mut line = String::new();

        std::io::stdin()
            .read_line(&mut line)
            .expect("Failed to read from stdin.");

        let line = line.split_whitespace();
        let line: Vec<&str> = line.collect();
        let range: Vec<&str> = line[0].split("-").collect();
        let rule = line[1];
        let password = line[2];

        let first_pos: usize = range[0].parse::<usize>().expect("Bad input") - 1;
        let second_pos: usize = range[1].parse::<usize>().expect("Bad input") - 1;

        let character = rule.chars().nth(0).unwrap();

        let first = password.chars().nth(first_pos).unwrap() == character;
        let second = password.chars().nth(second_pos).unwrap() == character;
        if first ^ second {
            valid_passwords += 1;
        }
    }

    println!("{}", valid_passwords);
}
