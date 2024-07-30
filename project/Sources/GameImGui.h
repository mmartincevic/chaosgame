#pragma once

#include "SDLImgui.h"
#include "../../vendors/imgui/imgui.h"
#include "../../helpers/Game/State/StateGame.h"

const char* algorithms[] = { "Bubble Sort", "Cycle Sort", "Radix Sort", "Merge Sort", "Test Sort"};

class GameImGui : public SDLImguiMenuItem
{
public:
    GameImGui(StateGame& gameState) : m_gameState(gameState)
    {
        //selected_algo = m_gameState.getAlgorithmSelected();
    }

    const char* GetName() const override
    {
        return "Game Settings";
    }

    virtual void RenderWindow() override
    {

        ImGui::SeparatorText("Algorithms");
        ImGui::Begin("Game stuff", &isOpen);

        if (ImGui::BeginCombo("Select an algorithm", algorithms[selected_algo]))
        {
            for (int n = 0; n < IM_ARRAYSIZE(algorithms); n++)
            {
                bool is_selected = (selected_algo == n);
                if (ImGui::Selectable(algorithms[n], is_selected))
                {
                    selected_algo = n;
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button("Go!"))
        {
            //m_gameState.setAlgorithmSelected(selected_algo);
        }

        ImGui::End();
    }
private:
    StateGame& m_gameState;
    int selected_algo;
};