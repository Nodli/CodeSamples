#include "vec3_pod.h"
#include "vec3_operator.h"
#include "vec3_math.h"

#include <stdio.h>

int main(){
	vec3 v = {1., 2., 3.};
	vec3 v2 = {1., 1., 1.};

	v += v2;
	v -= v2;

	v += 1.f;
	v -= 1.f;
	v *= 1.f;
	v /= 1.f;

	v + v2;
	v - v2;

	v + 1.f;
	v - 1.f;
	v * 1.f;
	v / 1.f;

	dot(v, v2);
	cross(v, v2);

	printf("v.coord[0] %f v.coord[1] %f v.coord[2] %f\n", v.coord[0], v.coord[1], v.coord[2]);
	printf("v.x %f v.y %f v.z %f\n", v.x, v.y, v.z);
	printf("v.r %f v.g %f v.b %f\n", v.r, v.g, v.b);

	return 0;
}
