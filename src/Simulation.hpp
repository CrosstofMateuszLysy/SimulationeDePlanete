#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "Planet.hpp"

class Simulation
{
    public:
        Simulation();
        ~Simulation();

        void mainLoop();

    private:
        void processEvents();
        void update();
        void render();

    private:
        SDL_Window* window;
        SDL_GLContext context;
        SDL_Event event;

        bool isRunning = true;

        float deltaTime = 0.f;
        float prevTime = 0.f;
        float currTime = 0.f;

        float angle = 0.f;

        float cameraPitch = 0.f;
        float cameraYaw = 0.f;
        float cameraDist = 5.f;

        float pos[4] = {0.f};

        Planet sun;
};

#endif
