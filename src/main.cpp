// UI realised with the help: https://retifrav.github.io/blog/2019/05/26/sdl-imgui/
// don't listen to MS complains, we want cross-platform code
//#define _CRT_SECURE_NO_DEPRECATE

// SDL
#include <glad/glad.h>
#include <SDL.h>

// Dear ImGui
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "../includes/controller.h"
#include <iostream>

static const int windowWidth = 400;
static const int windowHeight = 350;

int main()
{
    // initiate SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("[ERROR] %s\n", SDL_GetError());
        return -1;
    }

    // setup SDL window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
        );

    std::string glsl_version;
#ifdef __APPLE__
    // GL 3.2 Core + GLSL 150
    glsl_version = "#version 150";
    SDL_GL_SetAttribute( // required on Mac OS
        SDL_GL_CONTEXT_FLAGS,
        SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
        );
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#elif __linux__
    // GL 3.2 Core + GLSL 150
    glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#elif _WIN32
    // GL 3.0 + GLSL 130
    glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#endif
    
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow("Fint Calculator",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,  window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    // enable VSync
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) return -1;
    glViewport(0, 0, windowWidth, windowHeight);

    // setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // setup Dear ImGui style
    ImGui::StyleColorsDark();
    // setup platform/renderer bindings
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
    // colors are set in RGBA, but as float
    ImVec4 background = ImVec4(35/255.0f, 35/255.0f, 35/255.0f, 1.00f);

    glClearColor(background.x, background.y, background.z, background.w);
    // ON instancie un nouveau controller
    Controller controller;

    bool isRendering = true;
    while (isRendering)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // without it you won't have keyboard input and other things
            ImGui_ImplSDL2_ProcessEvent(&event);
            // you might also want to check io.WantCaptureMouse and io.WantCaptureKeyboard
            // before processing events
            switch (event.type)
            {
                case SDL_QUIT:
                    isRendering = false;
                    break;
                case SDL_WINDOWEVENT:
                    break;
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            isRendering = false;
                            break;
                    }
                    break;
                }
            }
        }

        // start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // a window is defined by Begin/End pair
        {


            int sdl_width = 0, sdl_height = 0;
            // get the window size as a base for calculating widgets geometry
            SDL_GetWindowSize(window, &sdl_width, &sdl_height);
            // position the controls widget in the top-right corner with some margin
            ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
            // here we set the calculated width and also make the height to be
            // be the height of the main window also with some margin
            ImGui::SetNextWindowSize(ImVec2(static_cast<float>(sdl_width - 20), static_cast<float>(sdl_height - 20)),ImGuiCond_Always);
            // create a window and append into it
            controller.DrawGui();
        }
        
        // rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
