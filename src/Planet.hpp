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
        Planet(const vec3_t& pz, float radz) : m_pos(pz), m_radius(radz) {}

        void update(float deltaTime);
        void render();

    private:
        vec3_t m_pos = {0.f,0.f,0.f};
        float m_radius = 1.f;

        float m_mass = 1.f;
};

#endif