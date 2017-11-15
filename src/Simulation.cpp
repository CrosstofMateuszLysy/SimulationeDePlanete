#include "Simulation.hpp"

Simulation::Simulation()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    window = SDL_CreateWindow(
        "Planetsy",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    context = SDL_GL_CreateContext(window);
    event;

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

    float diffuse[] = {1.f,1.f,1.f,1.f};
    float ambient[] = {0.2f,0.2f,0.2f,1.f};

    pos[0] = 2.f;
    pos[1] = 2.f;
    pos[2] = 2.f;
    pos[3] = 1.f;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sun = Planet({0,0,0}, 1.f);
}

Simulation::~Simulation()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Simulation::mainLoop()
{
    while (isRunning)
    {
        processEvents();
        update();
        render();
        SDL_GL_SwapWindow(window);
    }
}

void Simulation::processEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            isRunning = false;
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            isRunning = false;
    }
}

void Simulation::update()
{
    prevTime = currTime;
    currTime = SDL_GetTicks();
    deltaTime = (currTime - prevTime) / 1000.f;

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    if (keys[SDL_SCANCODE_UP])
    {
        cameraPitch += 100.f * deltaTime;
    }
    else if (keys[SDL_SCANCODE_DOWN])
    {
        cameraPitch -= 100.f * deltaTime;
    }

    if (keys[SDL_SCANCODE_LEFT])
    {
        cameraYaw += 100.f * deltaTime;
    }
    else if (keys[SDL_SCANCODE_RIGHT])
    {
        cameraYaw -= 100.f * deltaTime;
    }

    if (keys[SDL_SCANCODE_EQUALS])
    {
        cameraDist -= 2.f * deltaTime;
    }
    else if (keys[SDL_SCANCODE_MINUS])
    {
        cameraDist += 2.f * deltaTime;
    }

    sun.update(deltaTime);
}

void Simulation::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0,0,-cameraDist);
    glRotatef(cameraPitch, 1,0,0);
    glRotatef(cameraYaw, 0,1,0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    sun.render();
}
