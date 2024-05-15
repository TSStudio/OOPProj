#ifndef GAMEFILE_H
#define GAMEFILE_H

#include <string>

namespace sfSnake {
struct GameData {
    GameData() {
        highestScore = 0;
    }
    int highestScore;
};
class GameFile {
public:
    GameFile(std::string path = "gamedat.dat");
    GameData data_;
    void storeData(GameData _data);

private:
    bool fileExists();
    bool validateGameFile();
    void initGameFile();
    std::string path_;
};

}  // namespace sfSnake

#endif