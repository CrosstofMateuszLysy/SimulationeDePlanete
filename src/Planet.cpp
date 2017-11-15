#include "Planet.hpp"

static vec3_t theVec(float pitch, float yaw)
{
    vec3_t vec = {0,1,0};
    vec = rotateZ(vec, pitch);
    vec = rotateY(vec, yaw);

    return vec;
}

void Planet::update(float deltaTime)
{
}

void Planet::render()
{
    glPushMatrix();
        glTranslatef(m_pos.x, m_pos.y, m_pos.z);
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
