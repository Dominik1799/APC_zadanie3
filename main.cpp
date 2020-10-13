#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct Arguments {
    std::string inputFile;
    std::string pattern;
    unsigned int n;
};

void readArguments(Arguments& arguments, int& argc, char* argv[]){
    if (argc != 4 || argv[3][0] == '0'){
        std::cerr << "Command arguments error" << "\n";
        exit(1);
    }
    arguments.inputFile = argv[1];
    arguments.pattern = argv[2];
    if (arguments.pattern.length() >= 256){
        std::cerr << "Command arguments error" << "\n";
        exit(1);
    }
    arguments.n = std::stoi(argv[3]);
}

int main(int argc, char* argv[]) {
    Arguments arguments{};
    readArguments(arguments,argc,argv);

    return 0;
}
