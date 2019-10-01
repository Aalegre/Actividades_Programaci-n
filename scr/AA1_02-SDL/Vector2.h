#pragma once

#include <math.h>
#define PI 3.14159265

class Vector2
{
	public:

	float x;
	float y;

	//Construct
	Vector2();
	Vector2(const Vector2& copy_);
	Vector2(const Vector2& origin_, const Vector2& end_);
	Vector2(float x_, float y_);

	//Read
	const float Magnitude();
	const float Distance(Vector2 to_);
	const float GetEulerAngle();
	const float xProduct(const Vector2 & scalar_);

	//Modify
	void Add(const Vector2 & add_);
	void Scale(const float scalar_);
	void LookAt(const Vector2 & look_);
	void Normalize();
	void Project(const Vector2 & vectorToProject_);
	void Clamp(const float magnitude_);
	void FromEulerAngle(const float eulerAngle_);
	void Lerp(const Vector2& end_, float position_, bool clamp_ = false);

	//Operators
	Vector2 operator+(const Vector2& vector_);
	Vector2 operator-(const Vector2& vector_);
	Vector2 operator*(const Vector2& vector_);
	friend bool operator==(const Vector2& vector0_, const Vector2& vector1_);
	friend bool operator!=(const Vector2& vector0_, const Vector2& vector1_);
};

