#pragma once
#include <type_traits>
#include <array>
#include <vector>
#include "Orientation.h"
#include <string>
#include <iostream>
#include <exception>
template<typename T>
class Matrix
{
public:
	__declspec(dllexport) Matrix(const int x, const int y);
	__declspec(dllexport) Matrix(const std::vector<std::vector<T>>& data, Orientation orientation);
	__declspec(dllexport) void setColumn(const int columnNb, const T data[]);
	__declspec(dllexport) void setColumn(const int columnNb, const std::vector<T>& data);
	__declspec(dllexport) Matrix<T> getColumn(const int columnNb);
	__declspec(dllexport) void setRow(const int rowNb, const T data[], int sizeOfArray = -1);
	__declspec(dllexport) void setRow(const int rowNb, const std::vector<T>& data);
	__declspec(dllexport) Matrix<T> getRow(const int rowNb);
	__declspec(dllexport) T at(const int x, const int y);
	__declspec(dllexport) void setAt(const int x, const int y, const T& value);
	__declspec(dllexport) void transpose();
	__declspec(dllexport) std::pair<int,int> getDimension();
	__declspec(dllexport)friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& val)
	{
		out << "(" << val._x << "," << val._y << ")\n";
		for (unsigned int i = 0; i < val._y; i++)
		{
			for (unsigned int j = 0; j < val._x; j++)
			{
				//out << (T)val._data[val.index(j, i)];
				out << (T)val._data[val.index(j, i)] << "(" << (T)&val._data[val.index(j, i)] << ")";//debug
				out << " ";
			}
			out << "\n";
		}
		return out;
	}

private:
	unsigned int _x;
	unsigned int _y;
	T* _data;
	size_t index(const int x, const int y) const { return x + _x * y; }
	bool columnExist(const int columnNb) const { return columnNb < _x; }
	bool rowExist(const int rowNb) const { return rowNb < _y; }
};

/// <summary>
/// init a x,y matrix to 0
/// </summary>
/// <typeparam name="T">numeric type</typeparam>
/// <param name="x">width</param>
/// <param name="y">heigth</param>
template<typename T>
Matrix<T>::Matrix(const int x, const int y) :_x(x), _y(y)
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
void Matrix<T>::setColumn(const int columnNb, const T data[])
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
		throw new std::invalid_argument("column number: " + columnNb + " doesn't exist");
	}
}

template<typename T>
void Matrix<T>::setColumn(const int columnNb, const std::vector<T>& data)
{
	setColumn(columnNb, data.data());

}

template<typename T>
Matrix<T> Matrix<T>::getColumn(const int columnNb)
{
	if (columnExist(columnNb))
	{
		Matrix<T> res(1, _y);
		for (unsigned int y = 0; y < _y; y++)
		{
			res._data[y] = _data[index(columnNb, y)];
		}
		return res;
	}
	else
	{
		throw new std::invalid_argument("column number: " + columnNb + " doesn't exist");
	}
}

template<typename T>
void Matrix<T>::setRow(const int rowNb, const T data[], int sizeOfArray)
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
		throw new std::invalid_argument("row number: " + rowNb + " doesn't exist");
	}
}

template<typename T>
void Matrix<T>::setRow(const int rowNb, const std::vector<T>& data)
{
	if (rowExist(rowNb))
	{
		memcpy(_data + _x * rowNb, data.data(), data.size() * sizeof(T));
	}
	else
	{
		throw new std::invalid_argument("row number: " + rowNb + " doesn't exist");
	}
}

template<typename T>
Matrix<T> Matrix<T>::getRow(const int rowNb)
{
	if (rowExist(rowNb))
	{
		Matrix<T> res(_x, 1);
		memcpy(res._data, _data + _x * rowNb, _x * sizeof(T));
		return res;
	}
	else
	{
		throw new std::invalid_argument("row number: " + rowNb + " doesn't exist");
	}
}

template<typename T>
T Matrix<T>::at(const int x, const int y)
{
	return _data[index(x, y)];
}

template<typename T>
void Matrix<T>::setAt(const const int x, const int y, const T& value)
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
	delete _data;
	_data = dataFinal;
	std::swap(_x, _y);
}

template<typename T>
inline std::pair<int, int> Matrix<T>::getDimension()
{
	return std::pair<_x, _y>;
}
