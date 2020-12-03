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

    numbers.sort();

    for i in 0..199 {
        for j in 1..200 {
            if let Ok(k) = numbers.binary_search(&(2020 - numbers[i] - numbers[j])) {
                println!("{}", numbers[i] * numbers[j] * numbers[k]);
                return;
            }
        }
    }

    println!("No solutions found");
}
