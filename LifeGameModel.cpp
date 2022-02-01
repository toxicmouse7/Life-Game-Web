//
// Created by Алексей Гладков on 31.01.2022.
//

#include <random>

#include "LifeGameModel.hpp"

LifeGameModel::LifeGameModel(const std::string& seed) : seed(seed)
{
    this->field = std::vector(this->fieldSize,
                              std::vector(this->fieldSize, 0));

    std::seed_seq seedSeq(seed.begin(), seed.end());
    std::mt19937 rng(seedSeq);
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, this->fieldSize - 1);

    for (int i = 0; i < std::pow(this->fieldSize, 2) / 2; ++i)
        this->field[ dist(rng) ][ dist(rng) ] = 1;
}

int LifeGameModel::getNeighborsCount(int xCell, int yCell) const
{
    int neighbors = 0;

    neighbors += this->field[ mod(xCell + 1) ][ mod(yCell) ];
    neighbors += this->field[ mod(xCell + 1) ][ mod(yCell + 1) ];
    neighbors += this->field[ mod(xCell + 1) ][ mod(yCell - 1) ];

    neighbors += this->field[ mod(xCell - 1) ][ mod(yCell) ];
    neighbors += this->field[ mod(xCell - 1) ][ mod(yCell + 1) ];
    neighbors += this->field[ mod(xCell - 1) ][ mod(yCell - 1) ];

    neighbors += this->field[ mod(xCell) ][ mod(yCell + 1) ];
    neighbors += this->field[ mod(xCell) ][ mod(yCell - 1) ];

    return neighbors;
}

std::vector<std::string> LifeGameModel::getEpoch() const
{
    std::vector<std::string> res(this->fieldSize);
    for (int i = 0; i < this->fieldSize; ++i)
    {
        for (int j = 0; j < this->fieldSize; ++j)
        {
            if (this->field[ i ][ j ] == 0)
                res[ i ].push_back('O');
            else
                res[ i ].push_back('@');
        }
    }

    return res;
}

void LifeGameModel::newEpoch()
{
    for (int x = 0; x < this->fieldSize; ++x)
    {
        for (int y = 0; y < this->fieldSize; ++y)
        {
            auto neighbors = this->getNeighborsCount(x, y);

            if (this->field[ x ][ y ] == 0 && neighbors == 3)
                this->field[ x ][ y ] = 1;
            else if (this->field[ x ][ y ] == 1 && (neighbors > 3 || neighbors < 2))
                this->field[ x ][ y ] = 0;
        }
    }
}

int LifeGameModel::mod(int value) const
{
    return ((value % this->fieldSize) + fieldSize) % fieldSize;
}

const std::string& LifeGameModel::getSeed()
{
    return this->seed;
}

