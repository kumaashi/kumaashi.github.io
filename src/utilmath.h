#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

inline float FloatMix(float a, float b, float t)
{
	return (1 - t) * a + b * t;
}

inline float FloatClamp(float x, float a, float b)
{
	return x < a ? a : x > b ? b : x;
}

inline float FloatSmoothStep(float e0, float e1, float x)
{
	float t = FloatClamp((x - e0) / (e1 - e0), 0.0, 1.0);
	return t * t * (3 - 2 * t);
}

inline void VecSet(float *dest, float x, float y, float z, float w)
{
	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
	dest[3] = w;
}

inline void VecSet(float *dest, float *src)
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
}

inline void VecMix(float *dest, float *a, float *b, float t)
{
	VecSet(dest, FloatMix(a[0], b[0], t), FloatMix(a[1], b[1], t), FloatMix(a[2], b[2], t), FloatMix(a[3], b[3], t));
}

inline float VecDot(float *a, float *b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

inline float VecLength(float *a)
{
	return sqrt(VecDot(a, a));
}

inline void VecNormalize(float *v)
{
	float len = VecLength(v);
	if (len != 0)
	{
		len = 1.0f / len;
		VecSet(v, v[0] * len, v[1] * len, v[2] * len, v[3] * len);
	}
}

inline void VecAdd(float *dest, float *a, float *b)
{
	VecSet(dest, a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
}

inline void VecSub(float *dest, float *a, float *b)
{
	VecSet(dest, a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
}

inline void VecMul(float *dest, float *a, float *b)
{
	VecSet(dest, a[0] * b[0], a[1] * b[1], a[2] * b[2], a[3] * b[3]);
}

inline void VecDiv(float *dest, float *a, float *b)
{
	VecSet(dest, a[0] / b[0], a[1] / b[1], a[2] / b[2], a[3] / b[3]);
}

inline void VecFloatAdd(float *dest, float *a, float b)
{
	VecSet(dest, a[0] + b, a[1] + b, a[2] + b, a[3] + b);
}

inline void VecFloatSub(float *dest, float *a, float b)
{
	VecSet(dest, a[0] - b, a[1] - b, a[2] - b, a[3] - b);
}

inline void VecFloatMul(float *dest, float *a, float b)
{
	VecSet(dest, a[0] * b, a[1] * b, a[2] * b, a[3] * b);
}

inline void VecFloatDiv(float *dest, float *a, float b)
{
	VecSet(dest, a[0] / b, a[1] / b, a[2] / b, a[3] / b);
}

inline void VecCross(float *dest, float *a, float *b)
{
	VecSet(dest, a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0], 0.0f);
}

inline void VecMulMatrix(float *dest, float *v, float *m)
{
	VecSet(dest,
		   v[0] * m[0x0] + v[1] * m[0x4] + v[2] * m[0x8] + v[3] * m[0xC],
		   v[0] * m[0x1] + v[1] * m[0x5] + v[2] * m[0x9] + v[3] * m[0xD],
		   v[0] * m[0x2] + v[1] * m[0x6] + v[2] * m[0xA] + v[3] * m[0xE],
		   v[0] * m[0x3] + v[1] * m[0x7] + v[2] * m[0xB] + v[3] * m[0xF]);
}

inline void MatrixIdent(float *dest)
{
	VecSet(&dest[4 * 0], 1, 0, 0, 0);
	VecSet(&dest[4 * 1], 0, 1, 0, 0);
	VecSet(&dest[4 * 2], 0, 0, 1, 0);
	VecSet(&dest[4 * 3], 0, 0, 0, 1);
}

inline void MatrixTranslate(float *dest, float x, float y, float z)
{
	VecSet(&dest[4 * 0], 1, 0, 0, 0);
	VecSet(&dest[4 * 1], 0, 1, 0, 0);
	VecSet(&dest[4 * 2], 0, 0, 1, 0);
	VecSet(&dest[4 * 3], x, y, z, 1);
}

inline void MatrixScale(float *dest, float x, float y, float z)
{
	VecSet(&dest[4 * 0], x, 0, 0, 0);
	VecSet(&dest[4 * 1], 0, y, 0, 0);
	VecSet(&dest[4 * 2], 0, 0, z, 0);
	VecSet(&dest[4 * 3], 0, 0, 0, 1);
}

inline void MatrixRotation(float *dest, float x, float y, float z)
{
	MatrixIdent(dest);
	float sin_a = sin(x);
	float cos_a = cos(x);
	float sin_b = sin(y);
	float cos_b = cos(y);
	float sin_c = sin(z);
	float cos_c = cos(z);
	dest[0 + 0] = cos_b * cos_c;
	dest[0 + 1] = -cos_b * sin_c;
	dest[0 + 2] = sin_b;
	dest[4 + 0] = sin_a * sin_b * cos_c + cos_a * sin_c;
	dest[4 + 1] = -sin_a * sin_b * sin_c + cos_a * cos_c;
	dest[4 + 2] = -sin_a * cos_b;
	dest[8 + 0] = -cos_a * sin_b * cos_c + sin_a * sin_c;
	dest[8 + 1] = cos_a * sin_b * sin_c + sin_a * cos_c;
	dest[8 + 2] = cos_a * cos_b;
}

inline void MatrixMult(float *dest, float *a, float *b)
{
	float temp[16];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			int yi = y * 4;
			float value = 0;
			value += b[yi + 0] * a[x + 0];
			value += b[yi + 1] * a[x + 4];
			value += b[yi + 2] * a[x + 8];
			value += b[yi + 3] * a[x + 12];
			temp[x + y * 4] = value;
		}
	}
	for (int i = 0; i < 16; i++)
	{
		dest[i] = temp[i];
	}
}

inline void MatrixLookAt(float *dest, float *pos, float *at, float *up)
{
	float Z[4];
	float Y[4];
	float X[4];
	VecSet(Z, at[0] - pos[0], at[1] - pos[1], at[2] - pos[2], 0);
	VecNormalize(Z);

	VecSet(Y, up[0], up[1], up[2], 0);
	VecCross(X, Y, Z);
	VecNormalize(X);
	VecCross(Y, Z, X);

	VecSet(&dest[4 * 0], X[0], Y[0], Z[0], 0);
	VecSet(&dest[4 * 1], X[1], Y[1], Z[1], 0);
	VecSet(&dest[4 * 2], X[2], Y[2], Z[2], 0);
	VecSet(&dest[4 * 3], -VecDot(X, pos), -VecDot(Y, pos), -VecDot(Z, pos), 1);
}

inline void MatrixProjection(float *dest, float fovy, float aspect, float znear, float zfar)
{
	float tanhfov = tan(fovy / 2.0f);
	float a = 1.0f / (aspect * tanhfov);
	float b = 1.0f / tanhfov;
	float c = (zfar + znear) / (zfar - znear);
	float d = 1.0f;
	float e = -(2 * zfar * znear) / (zfar - znear);
	VecSet(&dest[4 * 0], a, 0, 0, 0);
	VecSet(&dest[4 * 1], 0, b, 0, 0);
	VecSet(&dest[4 * 2], 0, 0, c, d);
	VecSet(&dest[4 * 3], 0, 0, e, 0);
}


inline void VecPrint(float *a)
{
	for (int i = 0; i < 4; i++)
	{
		printf("%6.6f, ", a[i]);
	}
	printf("\n");
}

inline void MatrixPrint(float *a)
{
	for (int i = 0; i < 4; i++)
	{
		VecPrint(&a[4 * i]);
	}
	printf("\n");
}
