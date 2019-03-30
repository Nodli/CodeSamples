#ifndef BUFFER_H
#define BUFFER_H
#include <cassert>
#include <iostream>
#include <fstream>

#include <string> // temporary while no ASCII conversion for import & export

// Generic 2D Array class
template <typename T>
struct Buffer{
	Buffer();
	Buffer(const unsigned int& input_sizeX, const unsigned int& input_sizeY);
	Buffer(const Buffer<T>& src);
	~Buffer();

	// does not keep old data
	void allocate(const unsigned int& input_sizeX, const unsigned int& input_sizeY);

	Buffer<T>& operator=(const Buffer<T>& src);

	inline T operator[](const unsigned int& index) const;
	inline T& operator[](const unsigned int& index);

	inline T value(const unsigned int& x, const unsigned int& y) const;
	inline T& value(const unsigned int&  x, const unsigned int& y);

	void display() const;

	int sizeX;
	int sizeY;

	T* data;
};

template<typename T>
Buffer<T>::Buffer(): sizeX(0), sizeY(0){
	data = nullptr;
}

template<typename T>
Buffer<T>::Buffer(const unsigned int& input_sizeX, const unsigned int& input_sizeY)
: sizeX(input_sizeX), sizeY(input_sizeY){
	
	if(sizeX * sizeY){
		data = new T[sizeX * sizeY];
	}else{
		data = nullptr;
	}
}

template<typename T>
Buffer<T>::Buffer(const Buffer<T>& src): sizeX(src.sizeX), sizeY(src.sizeY){

	if(src.data){
		data = new T[sizeX * sizeY];

		for(unsigned int i = 0; i != sizeX * sizeY; ++i){
			data[i] = src.data[i];
		}
	}else{
		data = nullptr;
	}
}

template<typename T>
Buffer<T>::~Buffer(){
	if(data){
		delete[] data;
	}
}

template<typename T>
void Buffer<T>::allocate(const unsigned int& input_sizeX, const unsigned int& input_sizeY){

	if(input_sizeX * input_sizeY != sizeX * sizeY){
		if(data){
			delete[] data;
		}

		if(input_sizeX * input_sizeY != 0){
			data = new T[input_sizeX * input_sizeY];
		}else{
			data = nullptr;
		}
	}

	sizeX = input_sizeX;
	sizeY = input_sizeY;
}

template<typename T>
inline T Buffer<T>::operator[](const unsigned int& index) const{
	assert(index < sizeX * sizeY);
	return data[index];
}

template<typename T>
inline T& Buffer<T>::operator[](const unsigned int& index){
	assert(index < sizeX * sizeY);
	return data[index];
}

template<typename T>
inline T Buffer<T>::value(const unsigned int& x, const unsigned int& y) const{
	assert(x < sizeX && y < sizeY);
	return data[y * sizeX + x];
}

template<typename T>
inline T& Buffer<T>::value(const unsigned int& x, const unsigned int& y){
	assert(x < sizeX && y < sizeY);
	return data[y * sizeX + x];
}

template<typename T>
void Buffer<T>::display() const{
	std::cout << "Buffer<T> at " << this << std::endl;
	for(unsigned y = 0; y != sizeY; ++y){
		for(unsigned int x = 0; x != sizeX; ++x){
			std::cout << data[y * sizeX + x] << " ";
		}

		std::cout << std::endl;
	}
}

// ----- EXPORT FUNCTIONS ----- //

// storing color in a padded int as ABGR (word-order) ie RGBA (byte-order) like in OpenGL
inline char red(const int& rgb){
	return (rgb >> 16) & 0xff;
}

inline char green(const int& rgb){
	return (rgb >> 8) & 0xff;
}

inline char blue(const int& rgb){
	return rgb & 0xff;
}

char maxValue(const Buffer<int>& src){
	char max = 0;

	for(unsigned int i = 0; i != src.sizeX * src.sizeY; ++i){
		for(unsigned int bit_offset = 0; bit_offset != 24; bit_offset += 8){
			char val = (src[i] >> bit_offset) & 0xff;

			if(val > max){
				val = max;
			}
		}
	}

	return max;
}

// storing color in a struct
struct RGB24{
	char r;
	char g;
	char b;
};

std::ostream& operator<<(std::ostream& stream, const RGB24& src){
	stream << +src.r << ' ' << +src.g << ' ' << +src.b;
}

char maxValue(const Buffer<RGB24>& src){
	char max = 0;
	for(unsigned int i = 0; i != src.sizeX * src.sizeY; ++i){
		if(src[i].r > max){
			max = src[i].r;
		}if(src[i].g > max){
			max = src[i].g;
		}if(src[i].b > max){
			max = src[i].b;
		}
	}
	return max;
}

namespace BufferIO{
	void exportBMP(const Buffer<RGB24>& src){

	}

	void importBMP(Buffer<RGB24>& src){

	}

	// exports a plain / raw PPM
	void exportP3(const Buffer<RGB24>& src){
		std::ofstream file("exportP3.ppm", std::ios::out);

		file << "P3 " << static_cast<int>(src.sizeX) << ' ' << static_cast<int>(src.sizeY) << ' ' << static_cast<int>(maxValue(src)) << std::endl;

		for(unsigned int i = 0; i != src.sizeX * src.sizeY; ++i){
			// casting to int for ASCII output
			file << +src[i].r << ' ';
			file << +src[i].g << ' ';
			file << +src[i].b << ' ';
		}

		file.close();
	}

	// imports a plain / raw PPM
	void importP3(Buffer<RGB24>& dest){
		std::ifstream file("exportP3.ppm", std::ios::in);
		std::string buffer;

		file >> buffer;
		assert(buffer == "P3");

		file >> buffer;
		int sizeX = std::stoi(buffer);

		file >> buffer;
		int sizeY = std::stoi(buffer);

		dest.allocate(sizeX, sizeY);

		file >> buffer; // max value
		assert(std::stoi(buffer) < 256);

		file.get(); // skipping end line

		for(unsigned int i; i != sizeX * sizeY; ++i){
			file >> buffer;
			std::cout << buffer << ' ';
			dest[i].r = static_cast<char>(std::stoi(buffer));
			file >> buffer;
			std::cout << buffer << ' ';
			dest[i].g = static_cast<char>(std::stoi(buffer));
			file >> buffer;
			std::cout << buffer << std::endl;
			dest[i].b = static_cast<char>(std::stoi(buffer));
		}

		file.close();
	}

	// export a PPM
	void exportP6(const Buffer<RGB24>& src){
		std::ofstream file("exportP6.ppm", std::ios::out | std::ios::binary);

		file << "P6 " << static_cast<int>(src.sizeX) << ' ' << static_cast<int>(src.sizeY) << ' ' << static_cast<int>(maxValue(src)) << std::endl;

		char write_buffer[3 * src.sizeX * src.sizeY];

		for(unsigned int i = 0; i != src.sizeX * src.sizeY; ++i){
			write_buffer[3 * i] = src[i].r;
			write_buffer[3 * i + 1] = src[i].g;
			write_buffer[3 * i + 2] = src[i].b;
		}

		file.write(write_buffer, 3 * src.sizeX * src.sizeY);
		file.close();
	}

	// imports a PPM
	void importP6(Buffer<RGB24>& dest){
		std::ifstream file("exportP6.ppm", std::ios::in | std::ios::binary);
		std::string buffer;
		
		file >> buffer;
		assert(buffer == "P6");

		file >> buffer;
		int sizeX = std::stoi(buffer);

		file >> buffer;
		int sizeY = std::stoi(buffer);

		dest.allocate(sizeX, sizeY);

		file >> buffer; // max value
		assert(std::stoi(buffer) < 256);

		file.get(); // skipping end line

		// raster data
		char read_buffer[3 * sizeX * sizeY];

		// data structure is POD of strict RGB values
		file.read(static_cast<char*>(static_cast<void*>(dest.data)), 3 * sizeX * sizeY);

		// data structure is not POD
		/*
		file.read(read_buffer, 3 * sizeX * sizeY);

		for(unsigned int i = 0; i != sizeX * sizeY; ++i){
			dest[i] = {read_buffer[3 * i], read_buffer[3 * i + 1], read_buffer[3 * i + 2]};
		}
		*/

		file.close();
	}
}

#endif
