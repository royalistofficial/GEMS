#pragma once
#include "const.hpp"
#include "Square.hpp"
#include <bonus.hpp>

class GameGrid {
public:
    GameGrid();
    void Render();
    ~GameGrid();
    void swap(int prevRow, int prevCol, int row, int col);
private:
    void draw();
    bool checkSequence(int row, int col);
    void destroySequence();
    void blackBlockUp();
    void cleanBlackkBloc();
    void findBonuses();
    Square *grid[GRID_SIZE][GRID_SIZE];
    void drawSquare(int row, int col);
};