#include "vec2.h"

#include <iostream>
#include <cassert>

int main(){
	vec2 v = {1., 2.};
	vec2 v2 = {1., 1.};

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

	length(v);
	squared_length(v);

	std::cout << "v.coord[0] " << v.coord[0] << " v.coord[1] " << v.coord[1] << std::endl;
	std::cout << "v.x " << v.x << " v.y " << v.y << std::endl;
	std::cout << "v.u " << v.u << " v.v " << v.v << std::endl;
	

	return 0;
}
