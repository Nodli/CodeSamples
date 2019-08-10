#include "Buffer2D.hpp"
#include <utility>

#include "Buffer2D.hpp" // testing include guard

Buffer2D<int> move(){
	Buffer2D<int> X(2, 3);

	return std::move(X);
};

int main(){

	Buffer2D<int> A;

	Buffer2D<float> B(0, 0);
	Buffer2D<int> C(3, 4);

	Buffer2D<int> J(3, 3, 1);

	Buffer2D<int> D(C);
	const Buffer2D<int>& rA = A;
	Buffer2D<int> E(rA);

	Buffer2D<int> F(move());

	Buffer2D<int> G(B);
	const Buffer2D<float>& rB = B;
	Buffer2D<int> H(rB);

	Buffer2D<int> I;
	I = A;
	I = rA;

	I = move();

	I = B;
	I = rB;

	int valC = C[0];
	int& refC = C[0];

	int valCoordC = C(0, 0);
	int& refCoordC = C(0, 0);

	C.fill(0);
	C.resize(1, 2);

	C.min();
	C.max();
}
