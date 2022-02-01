//
// Created by Алексей Гладков on 31.01.2022.
//

#ifndef DROGON_TEST_LIFEGAMEMODEL_HPP
#define DROGON_TEST_LIFEGAMEMODEL_HPP

#include <vector>


class LifeGameModel
{
private:
    const int fieldSize = 35;
    std::vector<std::vector<int>> field;
    std::string seed;

    [[nodiscard]] int getNeighborsCount(int xCell, int yCell) const;

    [[nodiscard]] int mod(int value) const;

public:

    ~LifeGameModel() = default;

    explicit LifeGameModel(const std::string& seed);

    LifeGameModel(LifeGameModel&) = delete;

    void operator=(const LifeGameModel&) = delete;

    void newEpoch();

    [[nodiscard]] std::vector<std::string> getEpoch() const;

    const std::string& getSeed();
};


#endif //DROGON_TEST_LIFEGAMEMODEL_HPP
