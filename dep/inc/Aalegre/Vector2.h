#pragma once

#include <iostream>
#include <math.h>
#include <algorithm>
#define PI 3.14159265

using namespace std;

class Vector2
{
public:

	float x;
	float y;

	//Construct
	Vector2();
	Vector2(const Vector2& copy_);
	Vector2(const Vector2 origin_, const Vector2 end_);
	Vector2(float x_, float y_);

	Vector2 zero();
	Vector2 right();
	Vector2 left();
	Vector2 up();
	Vector2 down();

	//Read
	const float Magnitude();
	const float Distance(Vector2 to_);
	const float Distance(Vector2 lineStart_, Vector2 lineEnd_);
	const float GetEulerAngle();
	const float xProduct(const Vector2& scalar_);
	const bool onSegment(Vector2 segment1_, Vector2 segment2_);

	//Modify
	void Add(const Vector2 add_);
	void Scale(const float scalar_);
	void LookAt(const Vector2 look_);
	void Normalize();
	void Project(const Vector2 vectorToProject_);
	void Clamp(const float magnitude_);
	void FromEulerAngle(const float eulerAngle_);
	void RotateOnAxis(const float eulerAngle_);

	//Operators
	Vector2 operator+(const Vector2 vector_);
	Vector2 operator-(const Vector2 vector_);
	Vector2 operator*(const Vector2 vector_);
	friend bool operator==(const Vector2 vector0_, const Vector2 vector1_);
	friend bool operator!=(const Vector2 vector0_, const Vector2 vector1_);

	//Utils
	friend int pointsOrientation(Vector2 p, Vector2 q, Vector2 r);
	friend bool segmentsIntersect(Vector2 segmentA_1_, Vector2 segmentA_2_, Vector2 segmentB_1_, Vector2 segmentB_2_);
};
class Vector2Int
{
public:

	int x;
	int y;
};
