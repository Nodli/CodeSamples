#ifndef H_VEC3_POD
#define H_VEC3_POD

// POD for compatiblity with C
struct vec3{
	union{
		float coord[3];

		struct{
			float x;
			float y;
			float z;
		};

		struct{
			float r;
			float g;
			float b;
		};
	};
};

#endif
