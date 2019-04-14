#ifndef PPM_H
#define PPM_H

#include <fstream>
#include <vector>

// sizeX is the number of rows
// sizeY is the number of columns
// data have a size of sizeX * sizeY * 3
// data is formated as row-major with channels ordered as R, G, B
void writeP3(std::ofstream& file, const unsigned int sizeX, const unsigned int sizeY, const unsigned char* const data){

	constexpr int max_value = 255;

	file << "P3 " << (int)(sizeX) << ' ' << (int)(sizeY) << ' ' << max_value << std::endl;

	for(unsigned int y = 0; y != sizeY; ++y){
		for(unsigned int x = 0; x != sizeX; ++x){
			file << (int)data[y * 3 * sizeX + 3 * x]
				<< ' ' << (int)data[y * 3 * sizeX + 3 * x + 1]
				<< ' ' << (int)data[y * 3 * sizeX + 3 * x + 2];

			// no space at the end of a line
			if(x != sizeX - 1){
				file << ' ';
			}
		}

		file << std::endl;
	}

	file.close();
}

// sizeX is returned with the number of rows
// sizeY is returned with the number of columns
// data is returned with a size of sizeX * sizeY * 3
// data is formatted as row-major with channels ordered as R, G, B
bool readP3(std::ifstream& file,
	unsigned int& sizeX, unsigned int& sizeY,
	std::vector<unsigned char>& data){

	bool status = true;

	std::string format_buffer;
	file >> format_buffer;

	status &= (format_buffer == "P3");

	file >> sizeX;
	file >> sizeY;

	int max_value;
	file >> max_value;

	status &= (max_value == 255);

	file.get(); // skipping EOL

	data.resize(sizeX * sizeY * 3);
	for(unsigned int value = 0; value != sizeX * sizeY * 3; ++value){
		int value_buffer; // buffer to make the conversion to int
		file >> value_buffer;

		data[value] = value_buffer;
	}

	return status;
}

// sizeX is the number of rows
// sizeY is the number of columns
// data have a size of sizeX * sizeY * 3
// data is formated as row-major with channels ordered as R, G, B
void writeP6(std::ofstream& file, const unsigned int sizeX, const unsigned int sizeY, const unsigned char* const data){

	constexpr int max_value = 255;

	file << "P6 " << (int)sizeX << ' ' << (int)sizeY << ' ' << (int)max_value << std::endl;

	file.write((char*)data, 3 * sizeX * sizeY);
	file.close();
}

// sizeX is returned with the number of rows
// sizeY is returned with the number of columns
// data is returned with a size of sizeX * sizeY * 3
// data is formatted as row-major with channels ordered as R, G, B
bool readP6(std::ifstream& file,
	unsigned int& sizeX, unsigned int& sizeY,
	std::vector<unsigned char>& data){

	bool status = true;

	std::string format_buffer;
	file >> format_buffer;

	status &= (format_buffer == "P6");

	file >> sizeX;
	file >> sizeY;

	int max_value;
	file >> max_value; // max value

	status &= (max_value == 255);

	file.get(); // skipping EOL

	data.resize(sizeX * sizeY * 3);
	file.read((char*)data.data(), 3 * sizeX * sizeY);

	return status;
}

#endif
