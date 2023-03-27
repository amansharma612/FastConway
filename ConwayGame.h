#include <iostream>
#include <vector>
#include <chrono>


class ConwayGame {
    private:
        int whichGod;
        void setInitCondition();
        


    public:
        std::vector<int> boardPosition;
        std::vector<int> newPosition;
        int gameSize;
        ConwayGame(int gameSize);
        void updatePositions();
};