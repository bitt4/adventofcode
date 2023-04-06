use std::cell::RefCell;
use std::collections::HashMap;
use std::fs;

struct Bag {
    searched: bool,
    parents: Vec<String>,
    children: Vec<(usize, String)>,
}

impl Bag {
    pub fn parents_count(&self, bags: &HashMap<String, RefCell<Bag>>) -> usize {
        let mut count = 0;
        for parent_color in &self.parents {
            if !bags[parent_color].borrow().searched {
                count += 1;
            }
            bags[parent_color].borrow_mut().searched = true;
            count += bags[parent_color].borrow().parents_count(bags);
        }

        count
    }

    fn children_sum(&self, bags: &HashMap<String, RefCell<Bag>>) -> usize {
        let mut sum = 0;
        for (amount, child_color) in &self.children {
            sum += amount;
            sum += amount * bags[child_color].borrow().children_sum(bags);
        }

        sum
    }
}

fn main() {
    let input = fs::read_to_string("input").expect("Can't read puzzle input file.");

    let mut bags: HashMap<String, RefCell<Bag>> = HashMap::new();

    input.lines().for_each(|line| {
        let (color, rule) = line.split_once(" bags contain ").unwrap();
        let contains = rule.split(", ").collect::<Vec<_>>();

        for bag in contains {
            let (amount, rest) = bag.split_once(' ').unwrap();
            let (child_bag_color, _) = rest.rsplit_once(' ').unwrap();

            let amount = amount.parse::<usize>().unwrap_or(0);
            let child_bag_color = if child_bag_color == "other" {
                ""
            } else {
                child_bag_color
            };

            bags.entry(color.to_owned())
                .or_insert(RefCell::new(Bag {
                    searched: false,
                    parents: vec![],
                    children: vec![],
                }))
                .borrow_mut()
                .children
                .push((amount, child_bag_color.to_owned()));

            bags.entry(child_bag_color.to_owned())
                .or_insert(RefCell::new(Bag {
                    searched: false,
                    parents: vec![],
                    children: vec![],
                }))
                .borrow_mut()
                .parents
                .push(color.to_owned());
        }
    });

    println!(
        "part 1: {}",
        bags["shiny gold"].borrow().parents_count(&bags)
    );

    println!(
        "part 2: {}",
        bags["shiny gold"].borrow().children_sum(&bags)
    );
}
