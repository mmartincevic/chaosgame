#pragma once

#include <SDL.h>
#include <vector>
#include <memory>

class SDLImguiMenuItem
{
public:
    virtual ~SDLImguiMenuItem() = default;
    virtual const char* GetName() const = 0;
    virtual void RenderWindow() = 0;
    bool isOpen = false;
};

class SDLImgui
{
public:
    static SDLImgui& Instance();

    void AddImguiWindow(std::shared_ptr<SDLImguiMenuItem> imguiWindow);

    void Initialize(SDL_Window* window, SDL_Renderer* renderer);
    void Update();
    void Render();
    void Shutdown();
    void AddImGui();

private:
    SDLImgui() = default;
    ~SDLImgui();
    SDLImgui(const SDLImgui&) = delete;
    SDLImgui& operator=(const SDLImgui&) = delete;

private:
    std::vector<std::shared_ptr<SDLImguiMenuItem>> menuItems;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;
    bool m_initialized = false;
};