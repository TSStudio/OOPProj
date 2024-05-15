#include "GameFile.h"
#include <filesystem>
#include <fstream>

using namespace sfSnake;

GameFile::GameFile(std::string path) {
    path_ = path;
    if (!fileExists() || !validateGameFile()) {
        initGameFile();
    }
}

void GameFile::storeData(GameData _data) {
    data_ = _data;
    std::ofstream file(path_, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }
    file.write(reinterpret_cast<char*>(&data_), sizeof(GameData));
    if (!file) {
        throw std::runtime_error("Could not write to file");
    }
}

bool GameFile::fileExists() {
    return std::filesystem::exists(path_);
}

bool GameFile::validateGameFile() {
    std::ifstream file(path_, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }
    GameData result;
    file.read(reinterpret_cast<char*>(&result), sizeof(GameData));
    if (!file) {
        return false;
    }
    data_ = result;
    return true;
}

void GameFile::initGameFile() {
    storeData(GameData());
}