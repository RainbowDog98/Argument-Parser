#pragma once

#include <iostream>
#include <string.h>
#include <vector>
#include <tuple>

class ArgumentParser
{
private:
    std::vector<std::tuple<bool *, char, std::string, std::string>> given_arguments;
    std::vector<std::tuple<int *, char, std::string, std::string>> given_arguments_value;
public:
    void add_single_argument(bool *argument_switcher, char argument, std::string full_argument, std::string help);
    void add_value_argument(int *value, char argument, std::string full_argument, std::string help);
    int parse_arguments(int argc, char* argv[]);  
    void print_information();  
    ArgumentParser();
};

