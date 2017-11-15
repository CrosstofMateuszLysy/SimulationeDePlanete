#include "Simulation.hpp"
#include <SDL2/SDL_image.h>

Simulation::Simulation()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    m_window = SDL_CreateWindow(
        "Planetsy",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    m_context = SDL_GL_CreateContext(m_window);

    glClearColor(0,0,0,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, 4.f/3.f, 0.1f, 100.f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);

    float diffuse[] = {1.f,1.f,1.f,1.f};
    float ambient[] = {0.2f,0.2f,0.2f,1.f};

    m_lightPos[0] = 2.f;
    m_lightPos[1] = 2.f;
    m_lightPos[2] = 2.f;
    m_lightPos[3] = 1.f;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_sun = Planet({0.f,0.f,0.f}, 1.f, {1.f,0.5f,0.f});
    m_earth = Planet({2.f,0.f,0.f}, 0.2f, {0.2f, 0.5f, 1.f});
}

Simulation::~Simulation()
{
    SDL_DestroyWindow(m_window);
    IMG_Quit();
    SDL_Quit();
}

void Simulation::mainLoop()
{
    while (m_isRunning)
    {
        processEvents();
        update();
        render();
        SDL_GL_SwapWindow(m_window);
    }
}

void Simulation::processEvents()
{
    while (SDL_PollEvent(&m_event))
    {
        if (m_event.type == SDL_QUIT)
            m_isRunning = false;
        if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE)
            m_isRunning = false;
    }
}

void Simulation::update()
{
    m_prevTime = m_currTime;
    m_currTime = SDL_GetTicks();
    m_deltaTime = (m_currTime - m_prevTime) / 1000.f;

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_UP])
    {
        m_cameraPitch += 100.f * m_deltaTime;
    }
    else if (keys[SDL_SCANCODE_DOWN])
    {
        m_cameraPitch -= 100.f * m_deltaTime;
    }

    if (keys[SDL_SCANCODE_LEFT])
    {
        m_cameraYaw += 100.f * m_deltaTime;
    }
    else if (keys[SDL_SCANCODE_RIGHT])
    {
        m_cameraYaw -= 100.f * m_deltaTime;
    }

    if (keys[SDL_SCANCODE_EQUALS])
    {
        m_cameraDist -= 2.f * m_deltaTime;
    }
    else if (keys[SDL_SCANCODE_MINUS])
    {
        m_cameraDist += 2.f * m_deltaTime;
    }

    m_sun.update(m_deltaTime);
    m_earth.update(m_deltaTime);
}

void Simulation::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-m_cameraDist);
    glRotatef(m_cameraPitch, 1,0,0);
    glRotatef(m_cameraYaw, 0,1,0);

    glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos);

    m_sun.render();
    m_earth.render();
}
