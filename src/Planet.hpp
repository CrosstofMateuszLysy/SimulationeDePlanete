#ifndef PLANET_HPP
#define PLANET_HPP
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "vec3.hpp"

class Planet
{
    public:
        Planet() = default;
        Planet(const vec3_t& pz, float radz, const char* tex, const vec3_t& color = vec3_t(1.f,1.f,1.f));

        void update(float deltaTime);
        void render();

    private:
        vec3_t m_color;

        vec3_t m_pos = {0.f,0.f,0.f};
        float m_radius = 1.f;

        float m_mass = 1.f;

        GLuint m_texture;
};

#endif