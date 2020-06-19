#include "argument_parser.h"

ArgumentParser::ArgumentParser(){
    given_arguments.push_back( std::make_tuple(nullptr, 'h', "help", "Print all information about the arguments") );
}

void ArgumentParser::add_single_argument(bool *argument_switcher, char argument, std::string full_argument, std::string help){
    given_arguments.push_back( std::make_tuple(argument_switcher, argument, full_argument, help) );
}

void ArgumentParser::add_value_argument(int *value, char argument, std::string full_argument, std::string help){
    given_arguments_value.push_back( std::make_tuple(value, argument, full_argument, help) );
}

void ArgumentParser::print_information(){
    puts("Available arguments");

    for (auto arg : given_arguments){
        std::cout << '-' << std::get<1>(arg) << " [--" << std::get<2>(arg) << "]| " << std::get<3>(arg) << std::endl;
    }
    for (auto arg : given_arguments_value){
        std::cout << '-' << std::get<1>(arg) << " VALUE [--" << std::get<2>(arg) << "=VALUE]| " << std::get<3>(arg) << std::endl;
    }
}

int ArgumentParser::parse_arguments(int argc, char *argv[]){

    if (argc == 1){
        // No arguments were given, nothing to be done :^)
        return 0;
    }

    for (int i = 1; i < argc; i++){
        
        // Argument detection area
        if (argv[i][0] == '-'){
            bool has_matched = false;

            if (argv[i][1] == '-'){
                // Detected the full argument name
                //puts("Detected the full argument");
                //int str_len = strlen(argv[i]);
                std::string str = argv[i];
                if( str.length() > 2){
                    
                    str = str.substr(2, str.length() - 1);
                    for (auto arg : given_arguments){
                        if (str == std::get<2>(arg)){
                        //printf("Argument parsed :^)\n");
                        if (str == "help"){
                            print_information();
                            return 2;
                        }
                         *std::get<0>(arg) = true;
                         has_matched = true;
                        }
                    }

                    if(!has_matched){
                        // Do the value type argument scan
                        int split_index = str.find('=', 0);
                        std::string sub_str = str.substr(0, split_index);
                        std::string value = str.substr(split_index + 1, str.length() - 1);

                        // std::cout << "DEBUG: parsed argument: " << sub_str << std::endl;
                        // std::cout << "DEBUG: parsed value: " << value << std::endl;

                        for (auto arg : given_arguments_value){
                            if (sub_str == std::get<2>(arg)){
                                if(str.length() == sub_str.length()){
                                   std::cout << "ERROR Invalid value for --" << sub_str << " argument!\n";
                                    return -1;
                                }
                                printf("Argument parsed :^)\n");
                                *std::get<0>(arg) = std::stoi(value);
                                has_matched = true;
                            }

                        }
                    }
                }
        }
        else {

            for (int j = 1; j < strlen(argv[i]); j++){
                
                for (auto arg : given_arguments){
                    if (argv[i][j] == std::get<1>(arg)){
                        printf("Argument parsed :^)\n");
                        if (argv[i][j] == 'h'){
                            print_information();
                            return 2;
                        }

                        *std::get<0>(arg) = true;
                        has_matched = true;
                    }
                }

                if(!has_matched){
                    // Do the value type argument scan
                    for (auto arg : given_arguments_value){
                        if (argv[i][j] == std::get<1>(arg)){
                            //puts("DEBUG: Detected the full argument"); 
                            if(i + 1 >= argc){
                                std::cout << "ERROR: value for -" << argv[i][j] << " was not specified\n";
                                return -1;
                            }
                            *std::get<0>(arg) = std::stoi(argv[i + 1]);
                            has_matched = true;   
                        }
                    }
                }
            }
        }
            if (!has_matched){
                // No arguments were matched
                // That means there was no argument that exists
                printf("ERROR: argument \"%s\" doesnt exist!\n", argv[i]);
                print_information();
                puts("");
                return -1;
            }
        }
    }

    return 0;
}