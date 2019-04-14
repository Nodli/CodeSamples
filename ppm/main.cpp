#include "ppm.hpp"

#include <fstream>
#include <vector>
#include <iostream>

int main(){
	bool status = true;

	int osizeX = 1;
	int osizeY = 5;
	unsigned char odata[15] = {255, 255, 255,
			0, 0, 0,
			255, 0, 0,
			0, 255, 0,
			0, 0, 255};
	std::ofstream ofile;

	unsigned int isizeX;
	unsigned int isizeY;
	std::vector<unsigned char> idata;
	std::ifstream ifile;

	// export & import comparison of a P3 PPM image

	ofile.open("imageP3.ppm");
	writeP3(ofile, osizeX, osizeY, odata);
	ofile.close();

	ifile.open("imageP3.ppm");
	status &= readP3(ifile, isizeX, isizeY, idata);
	ifile.close();

	status &= (isizeX == osizeX);
	status &= (isizeY == osizeY);
	status &= (idata.size() == 15);
	for(unsigned int value = 0; value != 15; ++value){
		status &= (odata[value] == idata[value]);
	}

	// reinitializing
	isizeX = 0;
	isizeY = 0;
	idata.clear();

	// export & import comparison of a P6 PPM image

	ofile.open("imageP6.ppm");
	writeP6(ofile, osizeX, osizeY, odata);
	ofile.close();

	ifile.open("imageP6.ppm");
	status &= readP6(ifile, isizeX, isizeY, idata);
	ifile.close();

	status &= (isizeX == osizeX);
	status &= (isizeY == osizeY);
	status &= (idata.size() == 15);
	for(unsigned int value = 0; value != 15; ++value){
		status &= (odata[value] == idata[value]);
	}

	return status;
}
