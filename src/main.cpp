#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "vec3.hpp"

vec3_t theVec(float pitch, float yaw)
{
	vec3_t vec = {0,1,0};
	vec = rotateZ(vec, pitch);
	vec = rotateY(vec, yaw);

	return vec;
}

struct Planet
{
    vec3_t pos = {0.f,0.f,0.f};
    float radius = 1.f;

    void render()
    {
        glPushMatrix();
            glTranslatef(pos.x, pos.y, pos.z);
            glRotatef(0,0,1,0);

            glBegin(GL_QUADS);

            for (auto i = 0.f; i < M_PI; i += STEP)
            {
                for (auto j = 0.f; j < RAD_FULL; j += STEP)
                {
                    vec3_t vecs[4] = {
                        theVec(i, j),
                        theVec(i + STEP, j),
                        theVec(i + STEP, j + STEP),
                        theVec(i, j + STEP)
                    };

                    glColor3f(1.f,0.5f,0.f);
                    glNormal3f(vecs[0].x, vecs[0].y, vecs[0].z);
                    glVertex3f(vecs[0].x, vecs[0].y, vecs[0].z);
                    glVertex3f(vecs[1].x, vecs[1].y, vecs[1].z);
                    glVertex3f(vecs[2].x, vecs[2].y, vecs[2].z);
                    glVertex3f(vecs[3].x, vecs[3].y, vecs[3].z);
                }
            }

            glEnd();
        glPopMatrix();
    }
};

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_Window* window = SDL_CreateWindow(
		"Planetsy",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
	);

	SDL_GLContext context = SDL_GL_CreateContext(window);
	SDL_Event event;

	bool isRunning = true;

	float deltaTime = 0.f;
	float prevTime = 0.f;
	float currTime = 0.f;

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
    float pos[] = {2.f,2.f,2.f,1.f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float angle = 0.f;

    float cameraPitch = 0.f;
    float cameraYaw = 0.f;
    float cameraDist = 5.f;

    Planet sun;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isRunning = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;
		}
		
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

        //ass

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		glTranslatef(0,0,-cameraDist);
        glRotatef(cameraPitch, 1,0,0);
        glRotatef(cameraYaw, 0,1,0);

        glLightfv(GL_LIGHT0, GL_POSITION, pos);

        sun.render();

		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
