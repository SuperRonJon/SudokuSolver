#include "ArgumentParser.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

ArgumentParser::ArgumentParser(const std::string &description_t, const std::string &usage_t) {
    description_m = description_t;
    usage_m = usage_t;
}

void ArgumentParser::add_option(Option opt) {
    const std::string opt_name = opt.name();
    const char opt_flag = opt.flag();
    if(options_map_m.count(opt_name) != 0) {
        throw std::invalid_argument("Option with name " + opt_name + " already given.");
    }
    if(flag_map_m.count(opt_flag) != 0) {
        throw std::invalid_argument("Option with flag " + std::string{opt_flag} + " already given.");
    }
    options_map_m.insert({opt_name, opt});
    flag_map_m.insert({opt_flag, opt_name});
}

void ArgumentParser::add_option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &default_value_t, const std::string &description_t) {
    add_option(Option(flag_t, name_t, takes_argument_t, default_value_t, description_t));
}

void ArgumentParser::add_option(char flag_t, const std::string &name_t, const std::string &description_t) {
    add_option(Option(flag_t, name_t, description_t));
}

void ArgumentParser::add_option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &description_t) {
    add_option(Option(flag_t, name_t, takes_argument_t, description_t));
}

bool ArgumentParser::was_given(const std::string &name_t) {
    if(options_map_m.count(name_t) != 1) {
        throw std::invalid_argument("Attempting to check option " + name_t + " not expected.");
    }
    return options_map_m.at(name_t).was_given();
}

std::string ArgumentParser::get_value(const std::string &name_t) {
    if(options_map_m.count(name_t) != 1) {
        throw std::invalid_argument("Attempting to check option " + name_t + " not expected.");
    }
    return options_map_m.at(name_t).value();
}

void ArgumentParser::parse(int argc, char **argv) {
    std::unordered_map<int, std::string> indecies;
    program_path_m = argv[0];
    for(int i = 1; i < argc; i++) {
        std::string token = argv[i];
        if(token.substr(0, 2) == "--") {
            std::string command_name = token.substr(2);
            if(options_map_m.count(command_name) == 0) {
                throw std::invalid_argument("Option --" + command_name + " not recognized.");
            }
            Option& curr_option = options_map_m.at(command_name);
            if(curr_option.takes_argument()) {
                indecies.insert({i + 1, command_name});
            }
            else {
                curr_option.set_value();
            }
        }
        else if(token[0] == '-') {
            std::size_t plus_index = 1;
            std::string options = token.substr(1);
            for(std::size_t j = 0; j < options.length(); j++) {
                if(flag_map_m.count(options[j]) == 0) {
                    throw std::invalid_argument("Option -" + std::string{options[j]} + " not recognized.");
                }
                Option& curr_option = options_map_m.at(flag_map_m.at(options[j]));
                if(curr_option.takes_argument()) {
                    indecies.insert({i + plus_index, curr_option.name()});
                    plus_index++;
                }
                else {
                    curr_option.set_value();
                }
            }
        }
        else {
            if(indecies.count(i) != 0) {
                options_map_m.at(indecies.at(i)).set_value(token);
            }
            else {
                dangling.push_back(token);
            }
        }
    }
}

std::size_t ArgumentParser::longest_option_string_length() {
    std::size_t longest = 0;
    for(auto &pair : options_map_m) {
        std::size_t current_length = pair.second.option_flag_string().length();
        if(current_length > longest) {
            longest = current_length;
        }
    }
    return longest;
}

void ArgumentParser::print_usage() {
    std::string usage_string = usage_m.empty() ? "Empty usage." : usage_m;
    std::cout << "Usage:\n       " << usage_string << "\n";
}

void ArgumentParser::print_help() {
    bool printed = false;
    if(!description_m.empty()) {
        std::cout << description_m << "\n\n";
        printed = true;
    }
    if(!usage_m.empty()) {
        print_usage();
    }
    else if(printed) {
        std::cout << "\n";
    }
    std::cout << "Options:\n";
    std::size_t longest_option = longest_option_string_length() + 3;
    for(auto &pair : options_map_m) {
        std::string option_help = pair.second.option_flag_string();
        std::cout << "  " << std::left << std::setw(longest_option) << option_help;
        std::cout << " " << pair.second.description() << "\n";
    }
}

Option::Option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &default_value_t, const std::string &description_t) {
    flag_m = flag_t;
    name_m = name_t;
    takes_arg_m = takes_argument_t;
    value_m = default_value_t;
    description_m = description_t;
    was_given_m = false;
}

Option::Option(char flag_t, const std::string &name_t, const std::string &description_t) {
    flag_m = flag_t;
    name_m = name_t;
    description_m = description_t;
    takes_arg_m = false;
    value_m = "";
    was_given_m = false;
}

Option::Option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &description_t) {
    flag_m = flag_t;
    name_m = name_t;
    takes_arg_m = takes_argument_t;
    value_m = "";
    description_m = description_t;
    was_given_m = false;
}

void Option::set_value(const std::string &val) {
    value_m = val;
    was_given_m = true;
}

void Option::set_value() {
    value_m = "true";
    was_given_m = true;
}

std::string Option::option_flag_string() {
    if(!takes_arg_m) {
        return "--" + name_m + ", -" + std::string{flag_m};
    }
    else {
        return "--" + name_m + ", -" + std::string{flag_m} + " VAL";
    }
}
