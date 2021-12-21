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

int main(){
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

	size_t valid = 0;

	for (const auto& passport : passports) {
		if (passport.contains_required_fields()){
			valid++;
		}
	}

	std::cout << valid << '\n';

	return 0;
}
