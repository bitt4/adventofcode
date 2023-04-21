use std::collections::VecDeque;
use std::fs;

fn tokenize(expr: &str) -> Vec<String> {
    let mut ret = vec![];

    let mut pos = 0;
    let mut last = 0;

    while pos < expr.len() {
        if expr.chars().nth(pos) == Some('(') {
            let mut paren = 1;
            while paren != 0 {
                pos += 1;
                if expr.chars().nth(pos) == Some('(') {
                    paren += 1;
                } else if expr.chars().nth(pos) == Some(')') {
                    paren -= 1;
                }
            }
        }
        if expr.chars().nth(pos) == Some(' ') {
            ret.push(expr.chars().skip(last).take(pos - last).collect());
            last = pos + 1;
        }
        pos += 1;
        if pos >= expr.len() {
            ret.push(expr.chars().skip(last).collect());
        }
    }

    ret
}

fn remove_parens(s: &str) -> String {
    s.chars().skip(1).take(s.len() - 2).collect()
}

fn eval(line: &str) -> usize {
    let tokens = tokenize(line);
    let first_token = &tokens[0];

    let mut acc = if first_token.starts_with('(') {
        eval(&remove_parens(first_token))
    } else {
        first_token.parse::<usize>().unwrap()
    };

    for i in (1..tokens.len()).step_by(2) {
        let op = &tokens[i];
        let value = {
            let expr = &tokens[i + 1];
            if expr.starts_with('(') {
                eval(&remove_parens(expr))
            } else {
                expr.parse::<usize>().unwrap()
            }
        };

        if op == "+" {
            acc += value;
        } else {
            acc *= value;
        }
    }

    acc
}

fn eval_with_precedence(line: &str) -> usize {
    let mut operators: Vec<String> = vec![];
    let mut output: VecDeque<String> = VecDeque::new();

    let tokens = line.split_whitespace().collect::<Vec<_>>();
    for token in tokens {
        if token.chars().all(|c| c.is_ascii_digit()) {
            output.push_back(token.to_owned());
        } else if token.starts_with('+') || token.starts_with('*') {
            while !operators.is_empty() && operators.last() == Some(&"+".to_string()) {
                output.push_back("+".to_owned());
                operators.pop();
            }
            operators.push(token.to_owned());
        } else if token.starts_with('(') {
            let (digit_position, _) = token
                .chars()
                .enumerate()
                .find(|(_, c)| c.is_ascii_digit())
                .unwrap();

            for _ in 0..digit_position {
                operators.push("(".to_owned());
            }

            output.push_back(token.chars().skip(digit_position).collect());
        } else if token.contains(')') {
            let (first_bracket_pos, _) = token
                .chars()
                .enumerate()
                .find(|(_, c)| !c.is_ascii_digit())
                .unwrap();
            output.push_back(token.chars().take(first_bracket_pos).collect());
            for _ in first_bracket_pos..token.len() {
                while operators.last() != Some(&"(".to_string()) {
                    output.push_back(operators.pop().unwrap().to_string());
                }
                operators.pop();
            }
        }
    }

    while !operators.is_empty() {
        output.push_back(operators.pop().unwrap().to_string());
    }

    let mut execution = vec![];
    while !output.is_empty() {
        if let Some(operation) = output.front() {
            if operation == "+" || operation == "*" {
                let val1: usize = *execution.last().unwrap();
                execution.pop();
                let mut val2 = *execution.last().unwrap();
                execution.pop();

                if operation == "+" {
                    val2 += val1;
                } else {
                    val2 *= val1;
                }

                execution.push(val2);
            } else {
                execution.push(output.front().unwrap().parse::<usize>().unwrap());
            }
            output.pop_front();
        }
    }

    execution.pop().unwrap()
}

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let part1 = input.lines().map(eval).sum::<usize>();
    let part2 = input.lines().map(eval_with_precedence).sum::<usize>();

    println!("part 1: {}", part1);
    println!("part 2: {}", part2);
}
