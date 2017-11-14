#ifndef VEC3_HPP
#define VEC3_HPP

#define M_PI 3.14159265357989f

#define RAD_FULL (M_PI * 2)
#define STEP (RAD_FULL / 64.f)

struct vec3_t
{
    float x = 0;
    float y = 0;
    float z = 0;
};

vec3_t rotateZ(vec3_t vec, float angle)
{
    vec3_t ret;
    ret.x = vec.x * cos(angle) - vec.y * sin(angle);
    ret.y = vec.x * sin(angle) + vec.y * cos(angle);
    ret.z = vec.z;

    return ret;
}

vec3_t rotateY(vec3_t vec, float angle)
{
    vec3_t ret;
    ret.x = vec.x * cos(angle) + vec.z * sin(angle);
    ret.y = vec.y;
    ret.z = -vec.x * sin(angle) + vec.z * cos(angle);

    return ret;
}

#endif