#include "RigidBody2D.h"

RigidBody2D::RigidBody2D(Vector2 center_, float radius_, bool isStatic_)
{
	center = center_;
	points = { { radius_, 0 } };
	isStatic = isStatic_;

	rotation = 0;
	type = CIRCLE;
	calculateBoundaries();
	calculateRenderPoint();
}

RigidBody2D::RigidBody2D(Vector2 center_, Vector2 size_, bool isStatic_)
{
	center = center_;
	points = { size_ };
	isStatic = isStatic_;

	rotation = 0;
	type = BOX;
	calculateBoundaries();
	calculateRenderPoint();
}

RigidBody2D::RigidBody2D(Vector2 center_, const std::vector<Vector2> & points_, bool isStatic_)
{
	center = center_;
	points = std::vector<Vector2>(points_);
	isStatic = isStatic_;

	rotation = 0;
	type = POLYGON;
	calculateBoundaries();
	calculateRenderPoint();
}

const float RigidBody2D::getRadius()
{
	return 0.0f;
}

const Vector2 RigidBody2D::getSize()
{
	switch (type)
	{
	case CIRCLE:
		return Vector2(points[0].x, points[0].x);
		break;
	case BOX:
		return Vector2(points[0]);
		break;
	case POLYGON:
		break;
	default:
		break;
	}
	return Vector2();
}

const std::pair<Vector2, Vector2> RigidBody2D::getBoundaries()
{
	return std::pair<Vector2, Vector2>();
}

const std::vector<Vector2> RigidBody2D::getPoints()
{
	return std::vector<Vector2>();
}

const Vector2 RigidBody2D::getCenter()
{
	return Vector2(center);
}

const Vector2 RigidBody2D::getRenderPoint()
{
	return Vector2(renderPoint);
}

const Vector2 RigidBody2D::getCurrentForce()
{
	return Vector2();
}

const Vector2 RigidBody2D::getDirection()
{
	return Vector2();
}

const float RigidBody2D::getRotation()
{
	return 0.0f;
}

const BODY_TYPE RigidBody2D::getType()
{
	return BODY_TYPE();
}

const bool RigidBody2D::isColliding(RigidBody2D rb_)
{
	switch (type)
	{
	case CIRCLE:
		switch (rb_.type)
		{
		case CIRCLE:
			return center.Distance(rb_.center) - points[0].x - rb_.points[0].x <= 0;
		case BOX:
			return false;
		case POLYGON:
			return false;
		default:
			return false;
		}
		return false;
	case BOX:
		switch (rb_.type)
		{
		case CIRCLE:
			return false;
		case BOX:
			return false;
		case POLYGON:
			return false;
		default:
			break;
		}
		return false;
	case POLYGON:
		switch (rb_.type)
		{
		case CIRCLE:
			return false;
		case BOX:
			return false;
		case POLYGON:
			return false;
		default:
			break;
		}
		return false;
	default:
		return false;
	}
	return false;
}

const bool RigidBody2D::isInBoundaries(Vector2 point_)
{
	switch (type)
	{
	case CIRCLE:
		return center.Distance(point_) - points[0].x <= 0;
	case BOX:
		if (rotation == 0) {
			if ((center.y + (points[0].y / 2) >= point_.y) &&
				(center.y - (points[0].y / 2) <= point_.y) && 
				(center.x + (points[0].x / 2) >= point_.x) && 
				(center.x - (points[0].x / 2) <= point_.x)) return true;
		}
		else {

		}
		return false;
	case POLYGON:
		return false;
	default:
		return false;
	}
	return false;
}

void RigidBody2D::calculateBoundaries()
{
}

void RigidBody2D::calculateRenderPoint()
{
	switch (type)
	{
	case CIRCLE:
		renderPoint = { center.x - (points[0].x / 2), center.y - (points[0].x / 2) };
		break;
	case BOX:
		renderPoint = { center.x - (points[0].x / 2), center.y - (points[0].y / 2) };
		break;
	case POLYGON:
		break;
	default:
		break;
	}
}

void RigidBody2D::move(Vector2 force_)
{
	calculateBoundaries();
	calculateRenderPoint();
}

void RigidBody2D::teleport(Vector2 position_)
{
	center = position_;
	calculateBoundaries();
	calculateRenderPoint();
}
