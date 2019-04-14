#ifndef BUFFER_H
#define BUFFER_H

// implementation is row major
template <typename T>
struct Buffer2D{
	Buffer2D();
	Buffer2D(const unsigned int& sizeX, const unsigned int& sizeY);

	Buffer2D(const Buffer2D<T>& src);
	Buffer2D(Buffer2D<T>&& src);

	template<typename otherT>
	Buffer2D(const Buffer2D<otherT>& src);

	~Buffer2D();

	Buffer2D<T>& operator=(const Buffer2D<T>& src);
	Buffer2D<T>& operator=(Buffer2D<T>&& src);

	template<typename otherT>
	Buffer2D<T>& operator=(const Buffer2D<otherT>& src);

	// access a value using its index
	inline T operator[](const unsigned int& index) const;
	inline T& operator[](const unsigned int& index);

	// access a value using its 2D coordinates
	inline T operator()(const unsigned int& x, const unsigned int& y) const;
	inline T& operator()(const unsigned int& x, const unsigned int& y);

	// set all data values to the provided value
	Buffer2D<T>& set(const T& value);

	int sizeX;
	int sizeY;

	T* data;
};

#include "Buffer2D.inl"

#endif
