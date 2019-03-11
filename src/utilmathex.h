#pragma once

#include "utilmath.h"

namespace util
{
namespace math
{

struct vec4
{
	union {
		struct
		{
			float x, y, z, w;
		};
		float raw[4];
	};
	vec4()
	{
		VecSet(raw, 0, 0, 0, 0);
	}
	vec4(float a)
	{
		VecSet(raw, a, a, a, a);
	}
	vec4(float a, float b, float c, float d)
	{
		VecSet(raw, a, b, c, d);
	}
	vec4 operator+(const vec4 &v)
	{
		vec4 a;
		VecAdd(a.raw, raw, (float *)v.raw);
		return a;
	}
	vec4 operator-(const vec4 &v)
	{
		vec4 a;
		VecSub(a.raw, raw, (float *)v.raw);
		return a;
	}
	vec4 operator*(const vec4 &v)
	{
		vec4 a;
		VecMul(a.raw, raw, (float *)v.raw);
		return a;
	}
	vec4 operator/(const vec4 &v)
	{
		vec4 a;
		VecDiv(a.raw, raw, (float *)v.raw);
		return a;
	}
	vec4 operator+=(const vec4 &v)
	{
		VecAdd(raw, raw, (float *)v.raw);
		return *this;
	}
	vec4 operator-=(const vec4 &v)
	{
		VecSub(raw, raw, (float *)v.raw);
		return *this;
	}
	vec4 operator*=(const vec4 &v)
	{
		VecMul(raw, raw, (float *)v.raw);
		return *this;
	}
	vec4 operator/=(const vec4 &v)
	{
		VecDiv(raw, raw, (float *)v.raw);
		return *this;
	}
	vec4 operator+(float x)
	{
		vec4 a;
		VecFloatAdd(a.raw, raw, x);
		return a;
	}
	vec4 operator-(float x)
	{
		vec4 a;
		VecFloatSub(a.raw, raw, x);
		return a;
	}
	vec4 operator*(float x)
	{
		vec4 a;
		VecFloatMul(a.raw, raw, x);
		return a;
	}
	vec4 operator/(float x)
	{
		vec4 a;
		VecFloatDiv(a.raw, raw, x);
		return a;
	}
	vec4 operator+=(float x)
	{
		VecFloatAdd(raw, raw, x);
		return *this;
	}
	vec4 operator-=(float x)
	{
		VecFloatSub(raw, raw, x);
		return *this;
	}
	vec4 operator*=(float x)
	{
		VecFloatMul(raw, raw, x);
		return *this;
	}
	vec4 operator/=(float x)
	{
		VecFloatDiv(raw, raw, x);
		return *this;
	}
	float dot(const vec4 &v)
	{
		return VecDot(raw, (float *)v.raw);
	}
	vec4 cross(const vec4 &v)
	{
		vec4 a;
		VecCross(a.raw, raw, (float *)v.raw);
		return a;
	}
	vec4 normalize()
	{
		VecNormalize(raw);
		return *this;
	}
	void print()
	{
		VecPrint(raw);
	}
};

struct mat4
{
	float raw[16];
	mat4()
	{
		MatrixIdent(raw);
	}
	vec4 operator*(const vec4 &x)
	{
		vec4 a;
		VecMulMatrix(a.raw, (float *)x.raw, raw);
		return a;
	}
	mat4 operator*(const mat4 &x)
	{
		MatrixMult(raw, raw, (float *)x.raw);
		return *this;
	}
	void translate(float x, float y, float z)
	{
		MatrixTranslate(raw, x, y, z);
	}
	void scale(float x, float y, float z)
	{
		MatrixScale(raw, x, y, z);
	}
	void rotation(float x, float y, float z)
	{
		MatrixRotation(raw, x, y, z);
	}
	void lookat(const vec4 & pos, const vec4 & at, const vec4 & up)
	{
		MatrixLookAt(raw, (float *)pos.raw, (float *)at.raw, (float *)up.raw);
	}
	void projection(float fovy, float aspect, float znear, float zfar)
	{
		MatrixProjection(raw, fovy, aspect, znear, zfar);
	}
	void print()
	{
		MatrixPrint(raw);
	}
};

}; // namespace math

}; // namespace util
