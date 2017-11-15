#ifndef VEC3_HPP
#define VEC3_HPP
#include <cmath>

#define M_PI 3.14159265357989f

#define RAD_FULL (M_PI * 2)
#define STEP (RAD_FULL / 64.f)

struct vec3_t
{
    float x = 0;
    float y = 0;
    float z = 0;

    vec3_t() = default;
    vec3_t(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
};

static vec3_t operator+(vec3_t a, vec3_t b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

static vec3_t operator-(vec3_t a, vec3_t b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

static vec3_t operator*(vec3_t v, float s)
{
    return {v.x * s, v.y * s, v.z * s};
}

static vec3_t operator/(vec3_t v, float s)
{
    return {v.x / s, v.y / s, v.z / s};
}

static vec3_t& operator+=(vec3_t& a, vec3_t b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;

    return a;
}

static vec3_t& operator-=(vec3_t& a, vec3_t b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

static float length(vec3_t v)
{
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

static float sqrLength(vec3_t v)
{
    return (v.x*v.x + v.y*v.y + v.z*v.z);
}

static vec3_t normalize(vec3_t v)
{
    auto len = length(v);
    return {v.x / len, v.y / len, v.z / len};
}

static vec3_t rotateZ(vec3_t vec, float angle)
{
    vec3_t ret;
    ret.x = vec.x * cos(angle) - vec.y * sin(angle);
    ret.y = vec.x * sin(angle) + vec.y * cos(angle);
    ret.z = vec.z;

    return ret;
}

static vec3_t rotateY(vec3_t vec, float angle)
{
    vec3_t ret;
    ret.x = vec.x * cos(angle) + vec.z * sin(angle);
    ret.y = vec.y;
    ret.z = -vec.x * sin(angle) + vec.z * cos(angle);

    return ret;
}

#endif