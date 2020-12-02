fn main(){
    let mut numbers: Vec<i32> = Vec::with_capacity(200);

    for _ in 0..200 {
        let mut input = String::new();

        std::io::stdin()
            .read_line(&mut input)
            .expect("Failed to read from stdin.");

        let number: i32 = input.trim().parse().expect("Not a number");
        numbers.push(number);
    }

    'nested: for i in 0..200 {
        for j in 0..200 {
            if numbers[i] + numbers[j] == 2020 {
                println!("{}", numbers[i] * numbers[j]);
                break 'nested;
            }
        }
    }
}
