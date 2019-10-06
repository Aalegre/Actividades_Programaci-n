#pragma once

#include "Vector2.h"

namespace Interpolation
{
	Vector2 Linear(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_ = true);
	Vector2 Exponential(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_ = true);
	Vector2 EaseIn(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_ = true);
	Vector2 EaseOut(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_ = true);
	Vector2 Smoothstep(const Vector2 origin_, const Vector2 end_, float value_, bool clamp_ = true);
}
