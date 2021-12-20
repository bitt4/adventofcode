#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

std::vector<std::string> split_string(const std::string& str, char delim = ' ') {
	std::vector<std::string> output;
	output.reserve(std::count(str.begin(), str.end(), delim + 1));
	size_t position = 0;

	for (size_t i = 0; i < str.length(); ++i) {
		if (str[i] == delim) {
			auto slice = str.substr(position, i - position);
			if (slice.length() != 0) {
				output.push_back(slice);
			}
			position = i + 1;
		} else if (i == str.length() - 1) {
			auto slice = str.substr(position, str.length() - position);
			if (slice.length() != 0) {
				output.push_back(slice);
			}
		}
	}

	return output;
}

std::vector<std::pair<std::string, std::string>> parse_passport(const std::string& raw) {
	std::vector<std::pair<std::string, std::string>> output;

	auto fields = split_string(raw);

	for (const auto& f : fields) {
		auto field_split = split_string(f, ':');
		std::pair<std::string, std::string> field = { field_split[0], field_split[1] };
		output.push_back(field);
	}

	return output;
}

bool contains_required_fields(const std::vector<std::pair<std::string, std::string>>& passport) {
	std::array<std::string, 7> required_fields = {
		"byr",
		"iyr",
		"eyr",
		"hgt",
		"hcl",
		"ecl",
		"pid"
	};

	for (const auto& required_field : required_fields) {
		bool contains = false;
		for (const auto& field : passport) {
			if (required_field == field.first) {
				contains = true;
				break;
			}
		}
		if (!contains) {
			return false;
		}
	}

	return true;
}

int main(){

	// bruh type
	// TODO: Make this type nicer (struct Passport or something)
	std::vector<std::vector<std::pair<std::string, std::string>>> passports;

	std::string passport_raw;
	std::string line;

	while(std::getline(std::cin, line)){
		if (line.length() == 0) {
			auto passport = parse_passport(passport_raw);
			passports.push_back(passport);
			passport_raw = "";
		} else if (std::cin.eof()) {
			passport_raw += " " + line;
			auto passport = parse_passport(passport_raw);
			passports.push_back(passport);
			passport_raw = "";
		} else {
			passport_raw += " " + line;
		}
	}

	if (passport_raw.length() != 0) {
		auto passport = parse_passport(passport_raw);
		passports.push_back(passport);
	}

	size_t valid = 0;

	for (const auto& passport : passports) {
		if (contains_required_fields(passport)){
			valid++;
		}
	}

	std::cout << valid << '\n';

	return 0;
}
