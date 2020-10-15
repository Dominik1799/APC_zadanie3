#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

const unsigned int BUFFER_SIZE = 4;


struct Arguments {
    std::string inputFile;
    std::string pattern;
    uint32_t n;
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
    arguments.n = std::stoul(argv[3]);
}



void findAllOccurences(std::string& pattern, std::string& mainBuffer,std::vector<size_t>& positions, size_t filePos){
    size_t foundAt = mainBuffer.find(pattern);
    while (true){
        if (foundAt == std::string::npos)
            return;
        const size_t foundPosition = filePos+foundAt;
        if (positions.empty() || foundPosition != positions.back()) {
            positions.push_back(foundPosition);
        }
        foundAt = mainBuffer.find(pattern,foundAt+1);
    }
}

bool isValidFromBack(size_t& currentIndex,std::vector<size_t>& positions,uint32_t& range){
    if (currentIndex == 0 || positions[currentIndex] - positions[currentIndex-1] > range)
        return false;
    return true;
}

bool isValidFromFront(size_t& currentIndex,std::vector<size_t>& positions,uint32_t& range){
    if (currentIndex == positions.size()-1 || positions[currentIndex+1] - positions[currentIndex] > range)
        return false;
    return true;
}

std::vector<size_t> filter(std::vector<size_t>& positions,uint32_t range){
    std::vector<size_t> result;
    for (size_t i = 0; i < positions.size(); i++) {
        if (isValidFromBack(i,positions,range) || isValidFromFront(i,positions,range))
            result.push_back(positions[i]);
    }
    return result;
}



int main(int argc, char* argv[]) {
    Arguments arguments{};
    readArguments(arguments,argc,argv);
    std::ifstream inputFile(arguments.inputFile);
    if (!inputFile.good()){
        std::cerr << "Input file error" << "\n";
        return 1;
    }
    std::string buffer;
    std::string mainBuffer;
    std::vector<size_t> positions;
    buffer.resize(BUFFER_SIZE);
    size_t prevFilePosition = 0;
    while (inputFile.read(buffer.data(),buffer.size()) || inputFile.gcount() != 0){
        if (inputFile.gcount() != BUFFER_SIZE){
            buffer.resize(inputFile.gcount());
        }
        findAllOccurences(arguments.pattern,buffer,positions,prevFilePosition);
        size_t tempPos = inputFile.tellg();
        inputFile.seekg(tempPos - arguments.pattern.length()+1);
        prevFilePosition = inputFile.tellg();
    }

    return 0;
}
