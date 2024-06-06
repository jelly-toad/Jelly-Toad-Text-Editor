//
// Created by ssullivan on 6/6/2024.
//

#include <iostream>
#include <SDL3/SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL_opengl.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD)) {
        std::cout << "Error initiating SDL!\n";
    }
    // for(int i = 0; i < SDL_GetNumRenderDrivers()-1; i++) {
    //     std::cout << "Driver Available: " << SDL_GetRenderDriver(i) << '\n';
    // }

    window = SDL_CreateWindow("Hello SDL", 800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, "opengl");
    SDL_SetRenderVSync(renderer, 1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    bool show_demo_window = true;
    bool show_other_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done = false;
    while(!done) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if(event.type == SDL_EVENT_QUIT) {
                done = true;
            }
            if(event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window)) {
                done = true;
            }
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        if(show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, World!");

        ImGui::Text("This is some useful text.");
        ImGui::Checkbox("Demo Window", &show_demo_window);
        ImGui::Checkbox("Another Window", &show_other_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float*)&clear_color);

        if(ImGui::Button("Button")) {
            counter++;
        }

        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

        if(show_other_window) {
            ImGui::Begin("Another Window", &show_other_window);
            ImGui::Text("Hello from another Window!");
            if(ImGui::Button("Close Me")) {
                show_other_window = false;
            }
            ImGui::End();
        }

        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
