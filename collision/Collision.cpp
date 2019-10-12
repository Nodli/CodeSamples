#include "Collision.h"

#include "utils.h"
#include <cassert>

// TODO(hugo): Get rid of this, this is only for std::min and std::max
#include <algorithm>

bool Inside(vec2* A, AABB* B){
    return !((A->x < B->min.x) | (A->x > B->max.x) | (A->y < (B->min.y)) | (A->y > B->max.y));
}

bool Collision(AABB* A, AABB* B){
    return !((A->max.x < B->min.x) | (B->max.x < A->min.x) | (A->max.y < B->min.y) | (B->max.y < A->min.y));
}

bool CollisionX(AABB* A, Ray* R){
    R->length = std::min((A->min.x - R->origin.x) * R->inv_direction.x,
                         (A->max.x - R->origin.x) * R->inv_direction.x);
    return (R->length > 0.) && (R->origin.y > A->min.y && R->origin.y < A->max.y);
}
bool CollisionY(AABB* A, Ray* R){
    R->length = std::min((A->min.y - R->origin.y) * R->inv_direction.y,
                         (A->max.y - R->origin.y) * R->inv_direction.y);
    return (R->length > 0.) && (R->origin.x > A->min.x && R->origin.x < A->max.x);
}

// NOTE(hugo): https://tavianator.com/fast-branchless-raybounding-box-intersections/
// NOTE(hugo): Wayback Machine Link : https://web.archive.org/web/20190925061713/https://tavianator.com/fast-branchless-raybounding-box-intersections/
// NOTE(hugo): This does not work when one direction is NULL which is expected because this should show a numerical error
bool Collision(AABB* A, Ray* R){
    assert(R->inv_direction.x != 0.f && R->inv_direction.y != 0.f);

    float tmin, tmax;

    float tx1 = (A->min.x - R->origin.x) * R->inv_direction.x;
    float tx2 = (A->max.x - R->origin.x) * R->inv_direction.x;

    tmin = std::min(tx1, tx2);
    tmax = std::max(tx1, tx2);

    float ty1 = (A->min.y - R->origin.y) * R->inv_direction.y;
    float ty2 = (A->max.y - R->origin.y) * R->inv_direction.y;

    tmin = std::max(tmin, std::min(ty1, ty2));
    tmax = std::min(tmax, std::max(ty1, ty2));

    R->length = tmin;
    return (tmax >= tmin);
}

#if 0
bool Inside(vec2* A, Circle* B){
    vec2 sqdistance[2] = {B->center[0] - A->values[0], B->center[1] - A->values[1]};
    return (sqdistance[0] * sqdistance[0] + sqdistance[1] * sqdistance[1]) < (B->radius * B->radius);
}

// NOTE(hugo): https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm
bool Inside(vec2* P, Capsule* C){
    float CAtoP[2] = {P->values[0] - C->A[0], P->values[1] - C->A[1]};
    float CAtoCB[2] = {C->B[0] - C->A[0], C->B[1] - C->A[1]};

    float sqlengthC = CAtoCB[0] * CAtoCB[0] + CAtoCB[1] * CAtoCB[1];
    float paramC = (CAtoP[0] * CAtoCB[0] + CAtoP[1] * CAtoCB[1]) / sqlengthC;
    paramC = clamp(paramC, 0.f, 1.f);

    float orthogonal[2] = {CAtoP[0] - CAtoCB[0] * paramC, CAtoP[1] - CAtoCB[1] * paramC};

    return (orthogonal[0] * orthogonal[0] + orthogonal[1] + orthogonal[1]) < (C->radius * C->radius);
}

bool Collision(Circle* A, Circle* B){
    float center_distance[2] = {B->center[0] - A->center[0], B->center[1] - A->center[1]};
    float collision_sqdistance = B->radius + A->radius;
    return (center_distance[0] * center_distance[0] + center_distance[1] * center_distance[1])
        < (collision_sqdistance * collision_sqdistance);
}

bool Collision(Circle* A, AABB* B){
    float projCenterAonB[2] = {clamp(A->center[0], B->min[0], B->max[0]), clamp(A->center[1], B->min[1], B->max[1])};
    float CenterAtoProj[2] = {projCenterAonB[0] - A->center[0], projCenterAonB[1] - A->center[1]};
    return (CenterAtoProj[0] * CenterAtoProj[0] + CenterAtoProj[1] * CenterAtoProj[1]) < (A->radius * A->radius);
}

// NOTE(hugo): Similar to Inside(vec2*, Capsule*);
bool Collision(Circle* A, Capsule* B){
    float BAtoCircleCenter[2] = {A->center[0] - B->A[0], A->center[1] - B->A[1]};
    float BAtoBB[2] = {B->B[0] - B->A[0], B->B[1] - B->A[1]};

    float sqlengthB = BAtoBB[0] * BAtoBB[0] + BAtoBB[1] * BAtoBB[1];
    float paramB = (BAtoCircleCenter[0] * BAtoBB[0] + BAtoCircleCenter[1] * BAtoBB[1]) / sqlengthB;
    paramB = clamp(paramB, 0.f, 1.f);

    float orthogonal[2] = {BAtoCircleCenter[0] - BAtoBB[0] * paramB, BAtoCircleCenter[1] - BAtoBB[1] * paramB};
    float collision_sqdistance = A->radius + B->radius;

    return (orthogonal[0] * orthogonal[0] + orthogonal[1] * orthogonal[1]) < (collision_sqdistance * collision_sqdistance);
}

#endif
