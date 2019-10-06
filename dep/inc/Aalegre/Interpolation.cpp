#include "Interpolation.h"

Vector2 Interpolation::Linear(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_)
{
	Vector2 newVector(origin_);
	if (clamp_) {
		if (value_ > 1) value_ = 1;
		else if (value_ < 0) value_ = 0;
	}
	if (origin_ != end_) {
		Vector2 addVector(origin_, end_);
		addVector.x += value_;
		addVector.y += value_;
		newVector.Add(addVector);
	}
	return newVector;
}

Vector2 Interpolation::Exponential(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_)
{
	Vector2 newVector(origin_);
	if (clamp_) {
		if (value_ > 1) value_ = 1;
		else if (value_ < 0) value_ = 0;
	}
	if (origin_ != end_) {
		Vector2 addVector(origin_, end_);
		addVector.x *= value_;
		addVector.y *= value_;
		newVector.Add(addVector);
	}
	return newVector;
}

Vector2 Interpolation::EaseIn(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_)
{
	return Vector2();
}

Vector2 Interpolation::EaseOut(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_)
{
	return Vector2();
}

Vector2 Interpolation::Smoothstep(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_)
{
	return Vector2();
}
