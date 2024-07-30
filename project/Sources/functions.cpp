#include "functions.h"
#include <random>
#include <algorithm>
#include <stdexcept>
#include "../../helpers/SDL/SDLManager.h"
#include <ctime>
#include <cstdlib>

std::random_device rd;
std::mt19937 gen(rd());

int randomIntInRange(int min, int max)
{
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

float randomFloatInRange(float min, float max)
{
    std::uniform_real_distribution<> distr(min, max);
    return distr(gen);
}

float randomGaussian(float mean, float stddev)
{
    std::normal_distribution<float> distribution(mean, stddev);
    return distribution(gen);
}

void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + x, centreY - y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + x, centreY + y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - x, centreY - y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - x, centreY + y);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + y, centreY - x);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX + y, centreY + x);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - y, centreY - x);
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void DrawPoint(int32_t centreX, int32_t centreY)
{
    SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), centreX, centreY);
}


void DrawLine(int32_t fromX, int32_t fromY, int32_t toX, int32_t toY, SDL_Color color)
{
    SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(SDLManager::Instance().Renderer(), fromX, fromY, toX, toY);
}

std::vector<int> generateRandomVector(int start, int end)
{
    std::vector<int> vec;
    vec.reserve(end - start + 1);

    for (int i = start; i <= end; ++i)
    {
        vec.push_back(i);
    }
    std::srand(std::time(0));

    for (size_t i = vec.size() - 1; i > 0; --i)
    {
        size_t j = std::rand() % (i + 1);
        std::swap(vec[i], vec[j]);
    }

    return vec;
}


void drawTriangle(SDL_Renderer* renderer, SDL_Point* points)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[1].x, points[1].y);
    SDL_RenderDrawLine(renderer, points[1].x, points[1].y, points[2].x, points[2].y);
    SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[0].x, points[0].y);
}

int getRandomExcluding(int x, int y, int exclude)
{
    if (exclude == -1)
    {
        return x + rand() % (y - x + 1);
    }

    int randomNum;
    do
    {
        randomNum = x + rand() % (y - x + 1);
    } while (randomNum == exclude);
    return randomNum;
}

SDL_Point getMidpoint(const SDL_Point& p1, const SDL_Point& p2)
{
    SDL_Point midpoint;
    midpoint.x = (p1.x + p2.x) / 2;
    midpoint.y = (p1.y + p2.y) / 2;
    return midpoint;
}

void visualize(std::vector<int>& arr, int x, int y, int z)
{
    SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 0, 0, 0, 0);
    SDL_RenderClear(SDLManager::Instance().Renderer());

    int j = 0;
    int rectSize = 1;
    bool complete = false;

    for (int i = 0; i <= 799; i += rectSize)
    {
        SDL_Rect rect = { i, 0, rectSize, arr[j] };
        if (complete)
        {
            SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 100, 180, 100, 0);
            SDL_RenderDrawRect(SDLManager::Instance().Renderer(), &rect);
        }
        else if (j == x || j == z)
        {
            SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 100, 180, 100, 0);
            SDL_RenderFillRect(SDLManager::Instance().Renderer(), &rect);
        }
        else if (j == y)
        {
            SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 165, 105, 189, 0);
            SDL_RenderFillRect(SDLManager::Instance().Renderer(), &rect);
        }
        else
        {
            SDL_SetRenderDrawColor(SDLManager::Instance().Renderer(), 170, 183, 184, 0);
            SDL_RenderDrawRect(SDLManager::Instance().Renderer(), &rect);
        }
        j++;
    }
}