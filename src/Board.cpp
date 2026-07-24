#include "Board.hpp"
#include"../libs/json.hpp"
#include<fstream>
#include<stdexcept>


#include<iostream>

void Chess::Board::generateBoard(const std::string &boardSetupFilePath)
{
    std::ifstream setupJSONFile(boardSetupFilePath);

    if(!setupJSONFile)
        throw std::runtime_error("Failed to load boardSetupFilePath");
    
    nlohmann::json JSON;
    setupJSONFile >> JSON;

    std::cout<<JSON.dump();
}
