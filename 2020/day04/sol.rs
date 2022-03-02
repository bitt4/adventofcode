use std::collections::HashMap;
use std::fs;

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let passports_present_fields: Vec<_> = input
        .split("\n\n")
        .map(|passport| passport.replace('\n', " "))
        .map(|passport| passport.trim().to_owned())
        .map(parse_passport)
        .filter(contains_required_fields)
        .collect();

    let passports_valid_fields = passports_present_fields
        .iter()
        .filter(|x| has_valid_data(x))
        .count();
    println!("part 1: {}", passports_present_fields.len());
    println!("part 2: {}", passports_valid_fields);
}

fn parse_passport(raw_passport: String) -> HashMap<String, String> {
    let mut passport = HashMap::with_capacity(8);
    let pairs: Vec<_> = raw_passport.split(' ').collect();

    pairs.iter().for_each(|pair| {
        let (key, value) = pair.split_once(':').unwrap();
        passport.insert(key.to_owned(), value.to_owned());
    });

    passport
}

fn contains_required_fields(passport: &HashMap<String, String>) -> bool {
    let required_fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"];
    required_fields
        .iter()
        .all(|&field| passport.contains_key(field))
}

fn has_valid_data(passport: &HashMap<String, String>) -> bool {
    let byr = passport.get("byr").unwrap().parse::<u32>().unwrap();
    if !(1920..=2002).contains(&byr) {
        return false;
    }

    let iyr = passport.get("iyr").unwrap().parse::<u32>().unwrap();
    if !(2010..=2020).contains(&iyr) {
        return false;
    }

    let eyr = passport.get("eyr").unwrap().parse::<u32>().unwrap();
    if !(2020..=2030).contains(&eyr) {
        return false;
    }
    let eyr = passport.get("hgt").unwrap();
    if eyr.len() < 4 {
        return false;
    }

    let (value, unit) = eyr.split_at(eyr.len() - 2);
    let value = match value.parse::<u32>() {
        Ok(value) => value,
        Err(_) => return false,
    };
    match unit {
        "cm" => {
            if !(150..=193).contains(&value) {
                return false;
            }
        }
        "in" => {
            if !(59..=76).contains(&value) {
                return false;
            }
        }
        _ => return false,
    };

    let hcl = passport.get("hcl").unwrap();
    if !hcl.starts_with('#')
        || hcl.len() != 7
        || hcl
            .chars()
            .skip(1)
            .any(|c| !matches!(c, '0'..='9' | 'a'..='f'))
    {
        return false;
    }

    let ecl = passport.get("ecl").unwrap();
    if !["amb", "blu", "brn", "gry", "grn", "hzl", "oth"].contains(&ecl.as_str()) {
        return false;
    }

    let pid = passport.get("pid").unwrap();
    if pid.len() != 9 || !pid.chars().all(|c| c.is_ascii_digit()) {
        return false;
    }
    true
}
