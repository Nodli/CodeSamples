#include "Buffer2D.hpp"
#include <utility>

#include "Buffer2D.hpp" // testing include guard

Buffer2D<int>&& rValue(){
	Buffer2D<int> X(2, 3);

	return std::move(X);
};

int main(){

	Buffer2D<int> A;
	Buffer2D<float> B(0, 0);
	Buffer2D<int> C(3, 4);
	Buffer2D<int> D(rValue());
	Buffer2D<int> E(B);
	Buffer2D<int> F(Buffer2D<float>(2, 2));

	D = C;
	D = rValue();

	int valC = C[0];
	int& refC = C[0];

	int valCoordC = C(0, 0);
	int& refCoordC = C(0, 0);

	D.set(0);

	return 0;
}
