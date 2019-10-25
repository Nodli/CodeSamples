#include "bmp.hpp"

void writeBMP(std::ofstream& file,
		const int sizeX, const int sizeY,
		const char* const data){

    int header_size = 14;
    int info_header_size = 40;
    int total_header_size = 14 + 40;

    int row_end_bytes = 3 * sizeX % 4;
    int padding_bytes_per_row = (row_end_bytes != 0) ? 4 - row_end_bytes : 0;
    int alloc_bytes_per_row = 3 * sizeX + padding_bytes_per_row;

    int alloc_size = alloc_bytes_per_row * sizeY;
    int file_size = total_header_size + alloc_size;

    int* iptr = (&file_size);
    char* cptr = (char*)iptr;

    char header[header_size] = {
        'B', 'M',
        ((char*)&file_size)[0], ((char*)&file_size)[1], ((char*)&file_size)[2], ((char*)&file_size)[3],
        0, 0, 0, 0,
        ((char*)&total_header_size)[0], ((char*)&total_header_size)[1], ((char*)&total_header_size)[2], ((char*)&total_header_size)[3]
    };

    short bits_per_pixel = 24;

    char info_header[info_header_size] = {
        ((char*)&info_header_size)[0], ((char*)&info_header_size)[1], ((char*)&info_header_size)[2], ((char*)&info_header_size)[3],
        ((char*)&sizeX)[0], ((char*)&sizeX)[1], ((char*)&sizeX)[2], ((char*)&sizeX)[3],
        ((char*)&sizeY)[0], ((char*)&sizeY)[1], ((char*)&sizeY)[2], ((char*)&sizeY)[3],
        1, 0,
        ((char*)&bits_per_pixel)[0], ((char*)&bits_per_pixel)[1],
        0, 0, 0, 0,
        ((char*)&alloc_size)[0], ((char*)&alloc_size)[1], ((char*)&alloc_size)[2], ((char*)&alloc_size)[3],
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    file.write(header, header_size);
    file.write(info_header, info_header_size);

    // NOTE(hugo): Translating data to insert padding when needed, order as BGR and bottom to top
    char* alloc_data = (char*)malloc(alloc_size);
    if(alloc_data){
        for(int iy = 0; iy != sizeY; ++iy){
            for(int ix = 0; ix != sizeX; ++ix){
                alloc_data[alloc_bytes_per_row * iy + 3 * ix] = data[3 * (sizeX * (sizeY - 1 - iy) + ix) + 2];
                alloc_data[alloc_bytes_per_row * iy + 3 * ix + 1] = data[3 * (sizeX * (sizeY - 1 - iy) + ix) + 1];
                alloc_data[alloc_bytes_per_row * iy + 3 * ix + 2] = data[3 * (sizeX * (sizeY - 1 - iy) + ix)];
            }
        }

        file.write(alloc_data, alloc_size);

        free(alloc_data);
    }
}

bool writeBMP(const std::string& filename,
		const int sizeX, const int sizeY,
		const char* const data){

    std::ofstream file(filename);
    if(!file.is_open()){
        return false;
    }

    writeBMP(file, sizeX, sizeY, data);

    return true;
}


