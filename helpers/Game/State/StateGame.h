/*
*           ___            __    ___  __    ___       _ _                 _       _
*          / __\ __  _ __ / _\  /   \/ /   / __\ ___ (_) | ___ _ __ _ __ | | __ _| |_ ___
*         / / | '_ \| '_ \\ \  / /\ / /   /__\/// _ \| | |/ _ \ '__| '_ \| |/ _` | __/ _ \
*        / /__| |_) | |_) |\ \/ /_// /___/ \/  \ (_) | | |  __/ |  | |_) | | (_| | ||  __/
*        \____/ .__/| .__/\__/___,'\____/\_____/\___/|_|_|\___|_|  | .__/|_|\__,_|\__\___|
*             |_|   |_|                                            |_|
*
* Created by:   djomla
* Updated by:   djomla
*/
#pragma once

#include "GameState.h"
#include "StateManager.h"
#include "../../../project/Sources/definitions.h"
#include "../../Input/SimpleInputManager.h"
#include <thread>
#include <mutex>

class StateGame : public IGameState
{
public:
    void Enter(StateManager* manager) override;
    void Exit(StateManager* manager) override;
    void Update(StateManager* manager) override;
    void Draw(StateManager* manager) override;
    void Toggle(StateManager* manager) override;

public:
    void DrawSomething();

private:
    SDL_Point StateGame::getRandomPoint() const;

private:
    bool isOpen = false;

    int m_mainPoint;
    std::vector<SDL_Point> m_trianglePoints;
    SDL_Point points[3];

};
