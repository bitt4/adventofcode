#include <iostream>
#include <vector>
#include <algorithm>

struct Passport {
    std::string byr;
    std::string iyr;
    std::string eyr;
    std::string hgt;
    std::string hcl;
    std::string ecl;
    std::string pid;
    std::string cid;

    bool contains_required_fields() const {
        return !(byr.empty() ||
                 iyr.empty() ||
                 eyr.empty() ||
                 hgt.empty() ||
                 hcl.empty() ||
                 ecl.empty() ||
                 pid.empty()
                 );
    }

    bool valid() const {
        int birth_year = std::stoi(byr); // bruh, don't catch exceptions
        if (!(1920 <= birth_year && birth_year <= 2002)) { return false; }

        int issue_year = std::stoi(iyr);
        if (!(2010 <= issue_year && issue_year <= 2020)) { return false; }

        int expiration_year = std::stoi(eyr);
        if (!(2020 <= expiration_year && expiration_year <= 2030)) { return false; }

        if (hgt.length() < 4) { return false; }
        int height = std::stoi(hgt.substr(0, hgt.length() - 2));
        bool valid_height = false;
        if (hgt.find("cm") != std::string::npos) {
            valid_height = (150 <= height && height <= 193);
        } else if (hgt.find("in") != std::string::npos) {
            valid_height = (59 <= height && height <= 76);
        }

        if (!valid_height) { return false; }

        if (hcl[0] != '#' ||
            hcl.length() != 7 ||
            hcl.substr(1).find_first_not_of("0123456789abcdef") != std::string::npos)
        {
            return false;
        }

        if (ecl != "amb" &&
            ecl != "blu" &&
            ecl != "brn" &&
            ecl != "gry" &&
            ecl != "grn" &&
            ecl != "hzl" &&
            ecl != "oth")
        {
            return false;
        }

        if (pid.length() != 9 || pid.find_first_not_of("0123456789") != std::string::npos) {
            return false;
        }

        return true;
    }
};

std::vector<std::string> split_string(const std::string& str, char delim = ' ') {
	std::vector<std::string> output;
	output.reserve(std::count(str.begin(), str.end(), delim) + 1);
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

Passport parse_passport(const std::string& raw) {
    Passport output;

	auto fields = split_string(raw);

	for (const auto& f : fields) {
		auto field_split = split_string(f, ':');
        auto field = field_split[0];
        auto value = field_split[1];

             if (field.find("byr") == 0) { output.byr = value; }
        else if (field.find("iyr") == 0) { output.iyr = value; }
        else if (field.find("eyr") == 0) { output.eyr = value; }
        else if (field.find("hgt") == 0) { output.hgt = value; }
        else if (field.find("hcl") == 0) { output.hcl = value; }
        else if (field.find("ecl") == 0) { output.ecl = value; }
        else if (field.find("pid") == 0) { output.pid = value; }
        else if (field.find("cid") == 0) { output.cid = value; }
    }

    return output;
}

int main() {
	std::vector<Passport> passports;

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

	size_t part1 = 0,
           part2 = 0;

	for (const auto& passport : passports) {
		if (passport.contains_required_fields()) {
            part1++;
            if (passport.valid()) {
                part2++;
            }
		}
	}

    std::cout << "part 1: " << part1 << '\n';
    std::cout << "part 2: " << part2 << '\n';

	return 0;
}
