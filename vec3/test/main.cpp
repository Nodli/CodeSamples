#include "vec3.h"

#include <iostream>
#include <cassert>

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

	std::cout << "v.coord[0] " << v.coord[0] << " v.coord[1] " << v.coord[1] << " v.coord[2] " << v.coord[2] << std::endl;
	std::cout << "v.x " << v.x << " v.y " << v.y << " v.z " << v.z << std::endl;
	std::cout << "v.r " << v.r << " v.g " << v.g << " v.b " << v.b << std::endl;

	return 0;
}
