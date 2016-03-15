#include "Matrix4.h"

const Matrix4 Matrix4::Zero;
const Matrix4 Matrix4::I(1, 0, 0, 1);

const Matrix4& getMatForRot90()
{
	static Matrix4 s_mat(0, 1, -1, 0);
	return s_mat;
}

const Matrix4& getMatForRot180()
{
	static Matrix4 s_mat(-1, 0, 0, -1);
	return s_mat;
}

const Matrix4& getMatForRot270()
{
	static Matrix4 s_mat(0, -1, 1, 0);
	return s_mat;
}