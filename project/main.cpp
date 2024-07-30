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

#include <iostream>
#include <SDL.h>
#undef main

#include "Sources/definitions.h"
#include "../helpers/Game/myGame.h"

myGame* game;


const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main(int argc, const char* args[])
{
    myGameParams gameParam;
    gameParam.screenWidth = SCREEN_WIDTH;
    gameParam.screenHeight = SCREEN_HEIGHT;
    gameParam.gameTitle = "Snake AI Game";

    game = new myGame(gameParam);
    game->Init();
    game->Start();

    Uint32 lastUpdateTime = SDL_GetTicks();

    while (game->IsRunning())
    {
        Uint32 frameStart = SDL_GetTicks();

        game->Clear();
        game->handleEvents();

        /*Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastUpdateTime >= MILLISECONDS_PER_MOVE)
        {
            game->Update(SDL_GetTicks64());
            lastUpdateTime = currentTime;
        }*/
        game->Update(SDL_GetTicks64());
        game->Draw(SDL_GetTicks64());

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_DELAY)
        {
            //SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    delete game;
    return 1;
}
