#ifndef BMP_H
#define BMP_H

#include <fstream>

// NOTE(hugo): Reference Documentation
// https://en.wikipedia.org/wiki/BMP_file_format
// http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm

// sizeX is the number of rows
// sizeY is the number of columns
// data have a size of sizeX * sizeY * 3
// data is formated as row-major, RGB, top to bottom
void writeBMP(std::ofstream& file,
		const int sizeX, const int sizeY,
		const char* const data);
bool writeBMP(const char* const filename,
		const int sizeX, const int sizeY,
		const char* const data);

#endif
