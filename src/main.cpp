#include <stdio.h>
#include "argument_parser/argument_parser.h"

int main(int argc, char* argv[]){
    ArgumentParser parser;

    bool delete_file = false;
    bool print_uwu = false;
    int value = 69;
    int count = 20;

    parser.add_single_argument(&delete_file, 'd', "delete", "Delete a file");
    parser.add_single_argument(&print_uwu, 'u', "uwu", "Prints UwU");
    parser.add_value_argument(&value, 'v', "value", "Changes the default value (default: 69)");
    parser.add_value_argument(&count, 'c', "count", "Changes the default count (default: 20)");

    int check = parser.parse_arguments(argc, argv);

    if(check == -1){
        puts("Error in parsing :(");
        return -1;
    }
    else if(check == 2){
        return 0;
    }

    std::cout << "Delete file: " << delete_file << std::endl;
    std::cout << "Print UwU: " << print_uwu << std::endl;
    std::cout << "Print value: " << value << std::endl;
    std::cout << "Print count: " << count << std::endl;

    return 0;
}