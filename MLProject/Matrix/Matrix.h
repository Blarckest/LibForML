#pragma once
#include "Orientation.h"
#include <type_traits>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <exception>
template<typename T>
class __declspec(dllexport) Matrix
{
public:
	 Matrix(const unsigned int x, const unsigned int y);
	 Matrix(const std::vector<std::vector<T>>& data, Orientation orientation);
	 ~Matrix() { delete[] _data; _data = nullptr; }
	 void setColumn(const unsigned int columnNb, const T data[]);
	 void setColumn(const unsigned int columnNb, const std::vector<T>& data);
	 Matrix<T> getColumn(const unsigned int columnNb);
	 void setRow(const unsigned int rowNb, const T data[], int sizeOfArray = -1);
	 void setRow(const unsigned int rowNb, const std::vector<T>& data);
	 Matrix<T> getRow(const unsigned int rowNb);
	 T at(const unsigned int x, const unsigned int y);
	 void setAt(const unsigned int x, const unsigned int y, const T& value);
	 void transpose();
	 std::pair<unsigned int, unsigned int> getDimension();
	 T& operator() (unsigned int x, unsigned int y) { return _data[index(x, y)]; }
	 T operator() (unsigned int x, unsigned int y) const { return _data[index(x, y)]; }
	 friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& val)
	{
		{
			out << "(" << val._x << "," << val._y << ")\n";
			for (unsigned int i = 0; i < val._y; i++)
			{
				for (unsigned int j = 0; j < val._x; j++)
				{
					out << (T)val._data[val.index(j, i)];
					//out << (T)val._data[val.index(j, i)] << "(" << (T)&val._data[val.index(j, i)] << ")";//debug
					out << " ";
				}
				out << "\n";
			}
			return out;
		}
	}
	 friend Matrix<T>& operator+(const Matrix<T>& first, const Matrix<T>& second)
	{
		if (first._x != second._x || first._y != second._y)
		{
			throw std::invalid_argument("cannot add 2 matrices with differents dimensions");
		}
		Matrix<T>* res = new Matrix<T>(first._x, first._y);
		unsigned int nbOfElements = first._x * first._y;
		for (unsigned int i = 0; i < nbOfElements; i++)
		{
			res->_data[i] = first._data[i] + second._data[i];
		}
		return *res;
	}
	 friend Matrix<T>& operator-(const Matrix<T>& first, const Matrix<T>& second)
	{
		if (first._x != second._x || first._y != second._y)
		{
			throw std::invalid_argument("cannot substract 2 matrices with differents dimensions");
		}
		Matrix<T>* res = new Matrix<T>(first._x, first._y);
		unsigned int nbOfElements = first._x * first._y;
		for (unsigned int i = 0; i < nbOfElements; i++)
		{
			res->_data[i] = first._data[i] - second._data[i];
		}
		return *res;
	}
	 friend Matrix<T>& operator*(const Matrix<T>& first, const Matrix<T>& second)
	{
		if (first._y != second._x)
		{
			throw std::invalid_argument("cannot multiply 2 matrices with no match between height and width");
		}
		Matrix<T>* res = new Matrix<T>(first._x, second._y);
		for (size_t i = 0; i < first._x; i++)
		{
			for (size_t j = 0; j < second._y; j++)
			{
				T* dataToChange = res->_data + i + res->_x * j;
				for (size_t k = 0; k < first._y; k++)
				{
					*dataToChange += first(i, k) * second(k, j);
				}
			}
		}
		return *res;
	}
	 Matrix<T>& operator+=(const Matrix<T>& other);
	 Matrix<T>& operator-=(const Matrix<T>& other);
	 Matrix<T>& operator*=(const Matrix<T>& other);

private:	
	unsigned int _x;
	unsigned int _y;
	T* _data;
	size_t index(const unsigned int x, const unsigned int y) const;
	bool columnExist(const unsigned int columnNb) const { return columnNb < _x; }
	bool rowExist(const unsigned int rowNb) const { return rowNb < _y; }
};

/// <summary>
/// init a x,y matrix to 0
/// </summary>
/// <typeparam name="T">numeric type</typeparam>
/// <param name="x">width</param>
/// <param name="y">heigth</param>
template<typename T>
Matrix<T>::Matrix(const unsigned int x, const unsigned int y) :_x(x), _y(y)
{
	static_assert(std::is_arithmetic<T>::value, "Only numeric value are supported");
	_data = new T[x * y]();
}


/// <typeparam name="T">numeric type</typeparam>
/// <param name="data">data</param>
/// <param name="orientation">define if the vector containing the others is the x(horizontal) or y(vertical) axis</param>
template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& data, Orientation orientation)
{
	static_assert(std::is_arithmetic<T>::value, "Only numeric value are supported");
	unsigned int max = 0;
	for (auto vector : data)
	{
		max = max < vector.size() ? vector.size() : max;
	}
	_data = new T[data.size() * max]();

	_x = max;
	_y = data.size();

	int* last = _data;
	for (auto vector : data)
	{
		int size = vector.size() * sizeof(T); //how much we need to copy
		memcpy(last, vector.data(), size); //copy
		last += vector.size(); //move the pointer to the right position
	}

	if (orientation == Orientation::Horizontal)
	{
		transpose();
	}
}

template<typename T>
void Matrix<T>::setColumn(const unsigned int columnNb, const T data[])
{
	if (columnExist(columnNb))
	{
		for (unsigned int y = 0; y < _y; y++)
		{
			_data[index(columnNb, y)] = data[y];
		}
	}
	else
	{
		throw new std::invalid_argument("column number: " + std::to_string(columnNb) + " doesn't exist");
	}
}

template<typename T>
void Matrix<T>::setColumn(const unsigned int columnNb, const std::vector<T>& data)
{
	setColumn(columnNb, data.data());

}

template<typename T>
Matrix<T> Matrix<T>::getColumn(const unsigned int columnNb)
{
	if (columnExist(columnNb))
	{
		Matrix<T>* res=new Matrix<T>(1, _y);
		for (unsigned int y = 0; y < _y; y++)
		{
			res->_data[y] = _data[index(columnNb, y)];
		}
		return *res;
	}
	else
	{
		throw new std::invalid_argument("column number: " + std::to_string(columnNb) + " doesn't exist");
	}
}

template<typename T>
void Matrix<T>::setRow(const unsigned int rowNb, const T data[], int sizeOfArray)
{
	if (rowExist(rowNb))
	{
		if (sizeOfArray == -1)
		{
			for (unsigned int x = 0; x < _y; x++)
			{
				_data[index(x, rowNb)] = data[x];
			}
		}
		else
		{
			memcpy(_data + _x * rowNb, data, sizeOfArray * sizeof(T));
		}
	}
	else
	{
		throw new std::invalid_argument("row number: " + std::to_string(rowNb) + " doesn't exist");
	}
}

template<typename T>
void Matrix<T>::setRow(const unsigned int rowNb, const std::vector<T>& data)
{
	if (rowExist(rowNb))
	{
		memcpy(_data + _x * rowNb, data.data(), data.size() * sizeof(T));
	}
	else
	{
		throw new std::invalid_argument("row number: " + std::to_string(rowNb) + " doesn't exist");
	}
}

template<typename T>
Matrix<T> Matrix<T>::getRow(const unsigned int rowNb)
{
	if (rowExist(rowNb))
	{
		Matrix<T> *res= new Matrix<T>(_x, 1);
		memcpy(res->_data, _data + _x * rowNb, _x * sizeof(T));
		return *res;
	}
	else
	{
		throw new std::invalid_argument("row number: " + std::to_string(rowNb) + " doesn't exist");
	}
}

template<typename T>
T Matrix<T>::at(const unsigned int x, const unsigned int y)
{
	return _data[index(x, y)];
}

template<typename T>
void Matrix<T>::setAt(const unsigned int x, const unsigned int y, const T& value)
{
	_data[index(x, y)] = value;
}

template<typename T>
void Matrix<T>::transpose()
{
	T* dataFinal = new T[_x * _y];
	for (unsigned int y = 0; y < _y; y++)
	{
		for (unsigned int x = 0; x < _x; x++)
		{
			dataFinal[y + _y * x] = _data[index(x, y)]; //could not use index cause of possible different width between the 2 Matrix
		}
	}
	delete[] _data;
	_data = dataFinal;
	std::swap(_x, _y);
}

template<typename T>
std::pair<unsigned int, unsigned int> Matrix<T>::getDimension()
{
	return std::pair<_x, _y>;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
	if (_x != other._x || _y != other._y)
	{
		throw std::invalid_argument("cannot add 2 matrices with differents dimensions");
	}
	unsigned int nbOfElements = _x * _y;
	for (unsigned int i = 0; i < nbOfElements; i++)
	{
		 _data[i] += other._data[i];
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other)
{
	if (_x != other._x || _y != other._y)
	{
		throw std::invalid_argument("cannot substract 2 matrices with differents dimensions");
	}
	unsigned int nbOfElements = _x * _y;
	for (unsigned int i = 0; i < nbOfElements; i++)
	{
		_data[i] -= other._data[i];
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other)
{
	if (_y != other._x)
	{
		throw std::invalid_argument("cannot multiply 2 matrices with no match between height and width");
	}
	T* res = new T[_x * other._y * sizeof(T)](); //init new array cause the final matrix migth have different dimension than this
	for (size_t i = 0; i < _x; i++)
	{
		for (size_t j = 0; j < other._y; j++)
		{
			T* dataToChange = res + i + other._y * j;
			for (size_t k = 0; k < _y; k++)
			{
				*dataToChange += _data[index(i, k)] * other(k, j);
			}
		}
	}
	delete[] _data;
	_data = res;
	return *this;
}

template<typename T>
size_t Matrix<T>::index(const unsigned int x, const unsigned int y) const
{
	 if (x > _x || y > _y) 
	 { 
		 throw std::invalid_argument("incorrect index");
	 } 
	 return  x + _x * y; 
}
