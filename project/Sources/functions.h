#pragma once
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <vector>

int randomIntInRange(int min, int max);

float randomFloatInRange(float min, float max);

float randomGaussian(float mean = 0.0f, float stddev = 1.0f);

void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);

void DrawPoint(int32_t centreX, int32_t centreY);

void DrawLine(int32_t fromX, int32_t fromY, int32_t toX, int32_t toY, SDL_Color color = { 0, 255, 0, 255 });

std::vector<int> generateRandomVector(int start, int end);

void visualize(std::vector<int>& arr, int x = -1, int y = -1, int z = -1);

void drawTriangle(SDL_Renderer* renderer, SDL_Point* points);

int getRandomExcluding(int x, int y, int exclude = -1);

SDL_Point getMidpoint(const SDL_Point& p1, const SDL_Point& p2);