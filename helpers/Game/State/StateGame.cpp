#include "StateGame.h"

#include <iostream>

#include "../../../helpers/SDL/SDLManager.h"
#include "../../../project/Sources/functions.h"
#include "../../../project/Sources/SDLImgui.h"
#include "../../vendors/imgui/imgui.h"
#include "../../project/Sources/GameImGui.h"

void StateGame::Enter(StateManager* manager)
{
    std::cout << "State game enter" << '\n';

    SDLImgui::Instance().Initialize(SDLManager::Instance().Window(), SDLManager::Instance().Renderer());
    SDLImgui::Instance().AddImguiWindow(std::make_shared<GameImGui>(*this));
    points[0] = { 400, 150 };
    points[1] = { 100, 550 };
    points[2] = { 700, 550 };
    m_mainPoint = getRandomExcluding(0, 2);
}

void StateGame::Update(StateManager* manager)
{
    SDL_Point point;
    SDL_Point startPoint;

    if (m_trianglePoints.empty())
    {
        startPoint = getRandomPoint();
    }
    else
    {
        startPoint = m_trianglePoints[m_trianglePoints.size() - 1];
        m_mainPoint = getRandomExcluding(0, 2, -1);

        std::cout << "Main point selected: " << m_mainPoint << "\n";
    }

    point = getMidpoint(startPoint, points[m_mainPoint]);
    m_trianglePoints.push_back(point);
    SDLImgui::Instance().Update();
}

void StateGame::Draw(StateManager* manager)
{
    drawTriangle(SDLManager::Instance().Renderer(), points);

    for (auto& const point : m_trianglePoints)
    {
        SDL_RenderDrawPoint(SDLManager::Instance().Renderer(), point.x, point.y);
    }
    SDLImgui::Instance().Render();
}

void StateGame::Exit(StateManager* manager) 
{
    // Cleanup on exit this state
}

void StateGame::Toggle(StateManager* manager) {}


void StateGame::DrawSomething()
{
    char buffer[50];
    std::sprintf(buffer, "SCORE: %d", randomIntInRange(2, 100));

    SDL_Color color = { 123, 123, 123, 255 };
    SDL_Texture* textTexture = SDLManager::Instance().renderText(buffer, color);

    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect destRect = { 10, 70, textWidth, textHeight };  // Position at (100, 100)
    SDL_RenderCopy(SDLManager::Instance().Renderer(), textTexture, nullptr, &destRect);
}


SDL_Point StateGame::getRandomPoint() const
{
    float u = static_cast<float>(rand()) / RAND_MAX;
    float v = static_cast<float>(rand()) / RAND_MAX;

    // Ensure u + v <= 1
    if (u + v > 1.0f)
    {
        u = 1.0f - u;
        v = 1.0f - v;
    }

    float w = 1.0f - u - v;

    SDL_Point randomPoint;
    randomPoint.x = static_cast<int>(w * points[0].x + u * points[1].x + v * points[2].x);
    randomPoint.y = static_cast<int>(w * points[0].y + u * points[1].y + v * points[2].y);

    return randomPoint;
}