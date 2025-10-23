#pragma once
#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class Option {
public:
    Option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &default_value_t, const std::string &description_t);
    Option(char flag_t, const std::string &name_t, const std::string &description);
    Option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &description_t);
    
    void set_value(const std::string &val);
    void set_value();

    bool was_given() { return was_given_m; }
    std::string value() { return value_m; }
    char flag() { return flag_m; }
    bool takes_argument() { return takes_arg_m; }
    std::string name() { return name_m; }
    std::string description() { return description_m; }
    std::string option_flag_string();
private:
    char flag_m;
    bool takes_arg_m;
    bool was_given_m;
    std::string name_m;
    std::string description_m;
    std::string value_m;
};

class ArgumentParser {
public:
    ArgumentParser(const std::string &description_t, const std::string &usage_t);

    void add_option(Option opt);
    void add_option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &default_value_t, const std::string &description_t);
    void add_option(char flag_t, const std::string &name_t, const std::string &description_t);
    void add_option(char flag_t, const std::string &name_t, bool takes_argument_t, const std::string &description_t);
    
    void parse(int argc, char **argv);

    std::string description() { return description_m; }
    bool was_given(const std::string &name_t);
    std::string get_value(const std::string &name_t);
    std::string get_unflagged_argument(const std::size_t &index) { return dangling.at(index); }
    std::vector<std::string> get_unflagged_arguments() { return dangling; }
    void print_help();
    void print_usage();
private:
    std::size_t longest_option_string_length();

    std::string description_m;
    std::string usage_m;
    std::string program_path_m;
    std::unordered_map<std::string, Option> options_map_m;
    std::unordered_map<char, std::string> flag_map_m;
    std::vector<std::string> dangling;
};
