#pragma once
#include "vec.h"

struct Circle{
    vec2 center;
    float radius;
};

struct AABB{
    vec2 min;
    vec2 max;
};

struct Capsule{
    vec2 A;
    vec2 B;
    float radius;
};

struct Ray{
    vec2 origin;
    vec2 inv_direction; // NOTE(hugo): Faster for collision detection
    float length;
};

bool Inside(vec2* A, Circle* B);
bool Inside(vec2* A, AABB* B);
bool Inside(vec2* P, Capsule* C);

bool Collision(Circle* A, Circle* B);
bool Collision(Circle* A, AABB* B);
bool Collision(Circle* A, Capsule* B);
bool Collision(Circle* A, Ray* B);
bool Collision(AABB* A, AABB* B);
//bool Collision(AABB* A, Capsule* B); // NOTE(hugo): GJK
bool CollisionX(AABB* A, Ray* B);
bool CollisionY(AABB* A, Ray* B);
bool Collision(AABB* A, Ray* B);
//bool Collision(Capsule* A, Capsule* B); // NOTE(hugo): ?
//bool Collision(Capsule* A, Ray* B);
//bool Collision(Ray* A, Ray* B);
