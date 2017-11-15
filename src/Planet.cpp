#include "Planet.hpp"
#include "Texture.hpp"

static vec3_t theVec(float pitch, float yaw)
{
    vec3_t vec = {0,1,0};
    vec = rotateZ(vec, pitch);
    vec = rotateY(vec, yaw);

    return vec;
}

static void theCoord(float pitch, float yaw)
{
    float x = yaw / RAD_FULL;
    float y = pitch / M_PI;

    glTexCoord2f(x, y);
}

Planet::Planet(const vec3_t& pz, float radz, const vec3_t& color) : 
    m_pos(pz), m_radius(radz), m_color(color)
{
    m_texture = loadTexture("Textures/sun.png");
}

void Planet::update(float deltaTime)
{
}

void Planet::render()
{
    glPushMatrix();
        glTranslatef(m_pos.x, m_pos.y, m_pos.z);
        glRotatef(0,0,1,0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glBegin(GL_QUADS);

        for (auto i = 0.f; i < M_PI; i += STEP)
        {
            for (auto j = 0.f; j < RAD_FULL; j += STEP)
            {
                vec3_t vecs[4] = {
                    theVec(i, j) * m_radius,
                    theVec(i + STEP, j) * m_radius,
                    theVec(i + STEP, j + STEP) * m_radius,
                    theVec(i, j + STEP) * m_radius
                };

                // glColor3f(m_color.x, m_color.y, m_color.z);
                glColor3f(1.f, 1.f, 1.f);
                glNormal3f(vecs[0].x, vecs[0].y, vecs[0].z);

                theCoord(i, j);
                glVertex3f(vecs[0].x, vecs[0].y, vecs[0].z);

                theCoord(i + STEP, j);
                glVertex3f(vecs[1].x, vecs[1].y, vecs[1].z);

                theCoord(i + STEP, j + STEP);
                glVertex3f(vecs[2].x, vecs[2].y, vecs[2].z);

                theCoord(i, j + STEP);
                glVertex3f(vecs[3].x, vecs[3].y, vecs[3].z);
            }
        }

        glEnd();
    glPopMatrix();
}
