#include "GameGrid.hpp"
#include <main.hpp>

GameGrid::GameGrid() {
    // создание поля
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int tcolor = 1 + rand()%(NUMCOLORS-1);
            grid[i][j] = new Square(COLORS[tcolor][0], COLORS[tcolor][1], COLORS[tcolor][2], tcolor);
        }
    }
}

GameGrid::~GameGrid(){
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            delete grid[i][j];
        }
    }
}
void GameGrid::Render() {
    this->draw();
    this->destroySequence();
    this->cleanBlackkBloc();
    this->findBonuses();
}

void GameGrid::draw() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (this->grid[i][j] != nullptr)
                drawSquare(i, j);
        }
    }
    // для красивой анимации 
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void GameGrid::drawSquare(int row, int col) {
    const float border_width = 5.0f; // Ширина границы

    // Нарисовать границу
    glColor3f(0.0f, 0.0f, 0.0f); // Черный цвет
    glLineWidth(border_width); // Толщина линии
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0f + 2.0f * (col) / GRID_SIZE, 1.0f - 2.0f * (row) / GRID_SIZE);
    glVertex2f(-1.0f + 2.0f * (col+1) / GRID_SIZE, 1.0f - 2.0f * (row) / GRID_SIZE);
    glVertex2f(-1.0f + 2.0f * (col+1) / GRID_SIZE, 1.0f - 2.0f * (row+1) / GRID_SIZE);
    glVertex2f(-1.0f + 2.0f * (col) / GRID_SIZE, 1.0f - 2.0f * (row+1) / GRID_SIZE);
    glEnd();

    // Нарисовать внутреннюю часть квадрата
    glColor3f( (*this->grid[row][col]).colorR,  (*this->grid[row][col]).colorG,  (*this->grid[row][col]).colorB);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f + 2.0f * (col) / GRID_SIZE, 1.0f - 2.0f * (row) / GRID_SIZE);
    glVertex2f(-1.0f + 2.0f * (col+1) / GRID_SIZE, 1.0f - 2.0f * (row) / GRID_SIZE);
    glVertex2f(-1.0f + 2.0f * (col+1) / GRID_SIZE, 1.0f - 2.0f * (row+1) / GRID_SIZE);
    glVertex2f(-1.0f + 2.0f * (col) / GRID_SIZE, 1.0f - 2.0f * (row+1) / GRID_SIZE);
    glEnd();
}

bool GameGrid::checkSequence(int row, int col) {
    if (this->grid[row][col]->type <= 0)
        return false;
    int sequenceLength = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        if(i >= 0 && i < GRID_SIZE){
            if(this->grid[i][col]->type == -1 * this->grid[row][col]->type) return true;

            if (this->grid[i][col]->type == this->grid[row][col]->type) sequenceLength++;
        }
    }

    for (int j = col - 1; j <= col + 1; j++) {
         if (j >= 0 && j < GRID_SIZE){
            if(this->grid[row][j]->type == -1 * this->grid[row][col]->type) return true;

            if (this->grid[row][j]->type == this->grid[row][col]->type) sequenceLength++;
         }
    }
    if (sequenceLength >= 4)return true;

    return false;
}

void GameGrid::destroySequence() {
    bool sequenceFound = true;
    while (sequenceFound) {
        sequenceFound = false;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (checkSequence(i, j)) {
                    this->grid[i][j]->type = -1 * this->grid[i][j]->type;
                    sequenceFound = true;
                }
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (this->grid[i][j]->type < 0){
                int randBonus = rand() % 10; 
                if (randBonus == 0)  {
                    delete this->grid[i][j];
                    this->grid[i][j] = new BombBonus;
                }else if (randBonus == 1)  {
                    delete this->grid[i][j];
                    this->grid[i][j] = new PaintBonus;
                }else{
                this->grid[i][j]->type = 0; 
                this->grid[i][j]->colorR = COLORS[0][0];
                this->grid[i][j]->colorG = COLORS[0][1];
                this->grid[i][j]->colorB = COLORS[0][2];

                this->draw();
                }

            }
        }
    }
    
}

void GameGrid::blackBlockUp(){
    bool sequenceBlack = true;
    while (sequenceBlack) {
        sequenceBlack = false;
        for (int i = 1; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (this->grid[i][j]->type == 0 && 
                    this->grid[i-1][j]->type != 0 && 
                    dynamic_cast<Bonus*>(this->grid[i][j]) == nullptr ){
                    sequenceBlack = true;
                    std::swap(grid[i][j], grid[i-1][j]);
                }
            }
            this->draw();
        }
    }
}

void GameGrid::cleanBlackkBloc(){
    bool sequenceBlack = true;
    while (sequenceBlack) {
        blackBlockUp();
        sequenceBlack = false;
        for (int i = 0; i < GRID_SIZE; i++) {
            if (this->grid[0][i]->type == 0 && 
                dynamic_cast<Bonus*>(this->grid[0][i]) == nullptr){
                sequenceBlack = true;    
                int tcolor = 1 + rand()%(NUMCOLORS-1);
                this->grid[0][i]->type = tcolor; 
                this->grid[0][i]->colorR = COLORS[tcolor][0];
                this->grid[0][i]->colorG = COLORS[tcolor][1];
                this->grid[0][i]->colorB = COLORS[tcolor][2];
            }           
        }
        this->draw();
    }
}

void GameGrid::swap(int prevRow, int prevCol, int row, int col){
    std::swap(grid[prevRow][prevCol], grid[row][col]);
}

void GameGrid::findBonuses() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Square *square = grid[i][j];
            Bonus *bonus = dynamic_cast<Bonus*>(square);
            if (bonus != nullptr) {
                bonus->useBonus(i, j, grid);
                delete this->grid[i][j];
                grid[i][j] = new Square( COLORS[0][0],  COLORS[0][1], COLORS[0][2], 0);
                this->draw();
            }
        }
    }
}
