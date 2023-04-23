use std::collections::HashMap;
use std::fs;

struct Rule {
    c: char,
    subrules: Vec<Vec<u32>>,
}

type Ruleset = HashMap<u32, Rule>;

fn match_rule(message: &str, rules: &Ruleset, index: u32) -> Vec<String> {
    let rule = &rules[&index];
    if rule.c != '\0' {
        if message.starts_with(rule.c) {
            vec![message.chars().skip(1).collect()]
        } else {
            vec![]
        }
    } else if rule.subrules.len() == 1 {
        match_rule_list(message, rules, &rule.subrules[0])
    } else {
        rule.subrules
            .iter()
            .flat_map(|rule_list| match_rule_list(message, rules, rule_list))
            .collect()
    }
}

fn match_rule_list(message: &str, rules: &Ruleset, list: &Vec<u32>) -> Vec<String> {
    let mut inputs = vec![message.to_owned()];

    for &subindex in list {
        inputs = inputs
            .iter()
            .flat_map(|input| match_rule(input, rules, subindex))
            .collect();

        if inputs.is_empty() {
            break;
        }
    }

    inputs
}

fn any_empty(inputs: &[String]) -> bool {
    inputs.iter().any(|input| input.is_empty())
}

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut rules: HashMap<u32, Rule> = HashMap::new();

    let mut lines_iter = input.lines();

    lines_iter
        .by_ref()
        .take_while(|line| !line.is_empty())
        .for_each(|line| {
            let (id, rest) = line.split_once(": ").unwrap();
            let id = id.parse::<u32>().unwrap();

            if let Some(quotes) = rest.find('\"') {
                rules.insert(
                    id,
                    Rule {
                        c: rest.chars().nth(quotes + 1).unwrap(),
                        subrules: vec![],
                    },
                );
            } else {
                let subrules = rest
                    .split(" | ")
                    .map(|subrules_raw| {
                        subrules_raw
                            .split_whitespace()
                            .map(|subrule| subrule.parse::<u32>().unwrap())
                            .collect()
                    })
                    .collect();
                rules.insert(id, Rule { c: '\0', subrules });
            }
        });

    let messages = lines_iter.collect::<Vec<_>>();

    let part1 = messages
        .iter()
        .filter(|message| {
            let inputs = match_rule(message, &rules, 0);
            any_empty(&inputs)
        })
        .count();

    println!("part 1: {}", part1);

    rules.insert(
        8,
        Rule {
            c: '\0',
            subrules: vec![vec![42], vec![42, 8]],
        },
    );
    rules.insert(
        11,
        Rule {
            c: '\0',
            subrules: vec![vec![42, 31], vec![42, 11, 31]],
        },
    );

    let part2 = messages
        .iter()
        .filter(|message| {
            let inputs = match_rule(message, &rules, 0);
            any_empty(&inputs)
        })
        .count();

    println!("part 2: {}", part2);
}
