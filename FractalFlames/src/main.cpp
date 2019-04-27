#include "Buffer2D.hpp"
#include "FlameFunctor.hpp"
#include "ppm.hpp"

int main(){

	//Buffer2D<unsigned int> solution = IFS::solve(IFS::Library::serpinski_gasket(), 500, 10, 20, 0.5f, 0.5f, 1.f);
	//Buffer2D<unsigned int> solution = IFS::solve(IFS::Library::levy_curve(), 500, 10, 20, 0.5f, 0.5f, 2.f);
	//Buffer2D<unsigned int> solution = IFS::solve(IFS::Library::heighway_dragon_cartesian(), 500, 10, 20, 0.5f, 0.f, 2.f);

	//Buffer2D<unsigned int> solution = IFS::solve(IFS::Library::barnsley_fern(), 500, 10, 20, 7.5f, 9.f, 10.f);
	//Buffer2D<unsigned int> solution = IFS::solve(IFS::Library::barnsley_fern_mutated(), 500, 10, 20, 7.5f, 9.f, 10.f);

	//Buffer2D<unsigned int> solution = IFS::solve_complex(IFS::Library::heighway_dragon_complex(), 500, 20, 0.4f, 0.2f, 1.f);
	//Buffer2D<unsigned int> solution = IFS::solve_complex(IFS::Library::twin_dragon_complex(), 500, 20, 0.5f, 0.f, 1.f);
	Buffer2D<unsigned int> solution = IFS::solve_complex(IFS::Library::ter_dragon_complex(), 500, 15, 0.5f, 0.f, 1.f);

	Buffer2D<RGB> image = IFS::render(solution);
	//Buffer2D<RGB> image = IFS::binary_render(solution);
	//Buffer2D<RGB> image = IFS::log_render(solution);

	//writeP3("serpinski_gasket.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));
	//writeP3("levy_curve.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));
	//writeP3("heighway_dragon_cartesian.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));

	//writeP3("barnsley_fern.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));
	//writeP3("barnsley_fern_mutated.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));

	//writeP3("heighway_dragon_complex.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));
	//writeP3("twin_dragon_complex.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));
	writeP3("ter_dragon_complex.ppm", image.sizeX, image.sizeY, (unsigned char*)(image.data));

	return 0;
}
