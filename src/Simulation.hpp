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
        SDL_Window* m_window;
        SDL_GLContext m_context;
        SDL_Event m_event;

        bool m_isRunning = true;

        float m_deltaTime = 0.f;
        float m_prevTime = 0.f;
        float m_currTime = 0.f;

        float m_angle = 0.f;

        float m_cameraPitch = 0.f;
        float m_cameraYaw = 0.f;
        float m_cameraDist = 5.f;

        float m_lightPos[4] = {0.f};

        Planet m_sun;
        Planet m_earth;
};

#endif
