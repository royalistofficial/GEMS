#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

const int WIDTH = 600;
const int HEIGHT = 600;
const int GRID_SIZE = 20; // размер сетки (GRID_SIZExGRID_SIZE квадратов)
const float SQUARE_SIZE = WIDTH / GRID_SIZE; // размер каждого квадрата
const int NUMCOLORS = 25;
// Цвета квадратов
const float COLORS[NUMCOLORS][3] = {
    { 0.0, 0.0, 0.0 },
    { 0.0, 0.0, 0.5 },
    { 0.0, 0.0, 1.0 },
    { 0.0, 0.5, 0.0 },
    { 0.0, 0.5, 0.5 },
    { 0.0, 0.5, 1.0 },
    { 0.0, 1.0, 0.0 },
    { 0.0, 1.0, 0.5 },
    { 0.0, 1.0, 1.0 },
    { 0.5, 0.0, 0.0 },
    { 0.5, 0.0, 0.5 },
    { 0.5, 0.0, 1.0 },
    { 0.5, 0.5, 0.0 },
    { 0.5, 0.5, 0.5 },
    { 0.5, 0.5, 1.0 },
    { 0.5, 1.0, 0.0 },
    { 0.5, 1.0, 0.5 },
    { 0.5, 1.0, 1.0 },
    { 1.0, 0.0, 0.0 },
    { 1.0, 0.0, 0.5 },
    { 1.0, 0.0, 1.0 },
    { 1.0, 0.5, 0.0 },
    { 1.0, 0.5, 0.5 },
    { 1.0, 0.5, 1.0 },
    { 1.0, 1.0, 0.0 },
    // { 1.0, 1.0, 0.5 }, под 2 бонуса
    // { 1.0, 1.0, 1.0 },
};

