#ifndef PPM_H
#define PPM_H

#include <fstream>
#include <string>
#include <vector>

// sizeX is the number of rows
// sizeY is the number of columns
// data have a size of sizeX * sizeY * 3
// data is formated as row-major with channels ordered as R, G, B
void writeP3(std::ofstream& file,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);
bool writeP3(const std::string& filename,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);

// sizeX is returned with the number of rows
// sizeY is returned with the number of columns
// data is returned with a size of sizeX * sizeY * 3
// data is formatted as row-major with channels ordered as R, G, B
bool readP3(std::ifstream& file,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);
bool readP3(const std::string& filename,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);

// sizeX is the number of rows
// sizeY is the number of columns
// data have a size of sizeX * sizeY * 3
// data is formated as row-major with channels ordered as R, G, B
void writeP6(std::ofstream& file,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);
bool writeP6(const std::string& filename,
		const unsigned int sizeX, const unsigned int sizeY,
		const unsigned char* const data);

// sizeX is returned with the number of rows
// sizeY is returned with the number of columns
// data is returned with a size of sizeX * sizeY * 3
// data is formatted as row-major with channels ordered as R, G, B
bool readP6(std::ifstream& file,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);
bool readP6(const std::string& filename,
		unsigned int& sizeX, unsigned int& sizeY,
		std::vector<unsigned char>& data);

#endif
