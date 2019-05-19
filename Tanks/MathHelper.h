#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <math.h>
#include <iostream>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f
#define RAD_TO_DEG 180.0f / PI

struct Vector2 
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}

	float MagnitudeSqr()
	{
		return x*x + y*y;
	}

	float Magnitude()
	{
		return (float)sqrt(x*x + y*y);
	}

	Vector2 Normalize()
	{
		float mag = Magnitude();

		return Vector2(x / mag, y / mag);
	}

	Vector2 Invert()
	{
		return Vector2(y, x);
	}

	Vector2& operator +=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& operator -=(const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2& operator *=(const float rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	Vector2 operator -() const
	{
		return Vector2(-x, -y);
	}
};

inline Vector2 operator +(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2 operator *(const float& lhs, const Vector2& rhs)
{
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

inline Vector2 operator /(const Vector2& lhs, const Vector2 rhs)
{
	return Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
}

inline Vector2 operator /(const Vector2& lhs, const float& rhs)
{
	return Vector2(lhs.x / rhs, lhs.y / rhs);
}

inline Vector2 operator /(const float& lhs, const Vector2& rhs)
{
	return Vector2(lhs / rhs.x, lhs / rhs.y);
}

inline Vector2 RotateVector(Vector2& vec, float angle)
{
	float radAngle = (float)(angle * DEG_TO_RAD);

	return Vector2(((float)vec.x * cos(radAngle) - vec.y * sin(radAngle)), ((float)(vec.x * sin(radAngle) + vec.y * cos(radAngle))));
}

inline Vector2 Lerp(Vector2& start, Vector2& end, float time)
{
	if (time <= 0.0f)
		return start;
	else if (time >= 1.0f)
		return end;

	Vector2 dir = (end - start).Normalize();
	float mag = (end - start).Magnitude();

	return start + dir * mag * time;
}

inline Vector2 Perp(Vector2& vec)
{
	return Vector2(vec.y, -vec.x);
}

inline float Dot(Vector2& lhs, Vector2& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y);
}

inline bool Overlap(Vector2& lhs, Vector2& rhs)
{
	return !(lhs.x > rhs.y || lhs.y < rhs.x);
}

inline float GetOverlap(Vector2& lhs, Vector2& rhs)
{
	return (lhs.y < rhs.y) ? lhs.y - rhs.x : rhs.y - lhs.x;
}

inline Vector2 ClosestPoint(Vector2 a, Vector2 b, Vector2 c)
{
	Vector2 v = b - a;
	Vector2 p = c - a;

	float proj = Dot(p, v.Normalize());

	if (proj <= 0)
		return a;
	if (proj >= v.Magnitude())
		return b;

	Vector2 proj2 = v.Normalize() * proj;
	Vector2 closest = a + proj2;

	return closest;
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, -1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };

struct BezierCurve
{
	Vector2 p0;
	Vector2 p1;
	Vector2 p2;
	Vector2 p3;

	Vector2 CalculateCurvePoint(float t)
	{
		float tt = t * t;
		float ttt = tt * t;
		float u = 1.0f - t;
		float uu = u * u;
		float uuu = uu * u;

		Vector2 point = (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);
		point.x = round(point.x);
		point.y = round(point.y);

		return point;
	}
};

#endif