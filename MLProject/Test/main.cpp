#include "Model.h"
#include "Matrix.h"
#include <iostream>
int main()
{
	 Matrix<int> mat1(std::vector<std::vector<int>>{ { 3, 3, 1, 4 }, { 2, 1, 2, 6 }, { 3, 3, 1, 5 } }, Orientation::Vertical);
	 Matrix<int> mat2(std::vector<std::vector<int>>{ { 3, 3, 1 }, { 2, 1, 2 }, { 3, 3, 1 } }, Orientation::Vertical);
	 mat1.transpose();
	 std::cout << mat1;
	 std::cout << mat1.getColumn(2);
	 std::cout << mat1.getRow(2);
	 mat1.setColumn(2, std::vector<int> { {2, 2, 2, 2}});
	 std::cout << mat1.getColumn(2);
	 mat1.setRow(2, std::vector<int> { {2, 2, 2}});
	 std::cout << mat1.getRow(2);
	 mat1.setAt(2, 2, 18);
	 std::cout << mat1;
	 Model model(std::vector{ 2,3,3,2,3 });
	std::cout << mat1;
	std::cout << mat1(1,1);
	std::cout << mat1 + mat1;
	std::cout << mat1 - mat1;
	std::cout << mat2 * mat2;
	mat1 += mat1;
	std::cout << mat1;
	mat1 -= mat1;
	std::cout << mat1;
	std::cout << mat2;
	mat2 *= mat2;
	mat2 *= mat2 + mat2 + mat2 * mat2;
	std::cout << mat2;
	std::cout << mat2++;
	std::cout << mat2;
	std::cout << ++mat2;
	std::cout << mat2--;
	std::cout << mat2;
	std::cout << --mat2;
	return 0;
}