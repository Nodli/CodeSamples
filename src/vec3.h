#ifndef H_VEC3
#define H_VEC3

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
	}
};



#endif
