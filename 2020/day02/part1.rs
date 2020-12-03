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

        let from: i32 = range[0].parse().expect("Bad input");
        let to: i32 = range[1].parse().expect("Bad input");

        let character = rule.chars().nth(0).unwrap();

        let mut char_occ: i32 = 0;

        for i in password.chars() {
            if i == character {
                char_occ += 1;
            }
        }

        if from <= char_occ && char_occ <= to {
            valid_passwords += 1;
        }
    }

    println!("{}", valid_passwords);
}
