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

RigidBody2D::RigidBody2D(Vector2 center_, const vector<Vector2> & points_, bool isStatic_)
{
	center = center_;
	points = vector<Vector2>(points_);
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

const pair<Vector2, Vector2> RigidBody2D::getBoundaries()
{
	return pair<Vector2, Vector2>();
}

const vector<Vector2> RigidBody2D::getPoints()
{
	vector<Vector2> newPoints;
	switch (type)
	{
	case CIRCLE:
		for (float angle = 0; angle <= 2 * PI + 0.1; angle += 0.1)
		{
			newPoints.push_back({ center.x + points[0].x * cos(angle), center.y + points[0].x * sin(angle) });
		}
		return newPoints;
	case BOX:
		if (rotation == 0) {
			newPoints.push_back({ center.x + (points[0].x / 2), center.y - (points[0].y / 2) });
			newPoints.push_back({ center.x + (points[0].x / 2), center.y + (points[0].y / 2) });
			newPoints.push_back({ center.x - (points[0].x / 2), center.y + (points[0].y / 2) });
			newPoints.push_back({ center.x - (points[0].x / 2), center.y - (points[0].y / 2) });
		}
		else {
			Vector2 tempPoint;
			tempPoint = { points[0].x / 2, -points[0].y / 2 };
			tempPoint.RotateOnAxis(rotation);
			newPoints.push_back({ center.x + tempPoint.x, center.y + tempPoint.y });
			tempPoint = { points[0].x / 2, points[0].y / 2 };
			tempPoint.RotateOnAxis(rotation);
			newPoints.push_back({ center.x + tempPoint.x, center.y + tempPoint.y });
			tempPoint = { -points[0].x / 2, points[0].y / 2 };
			tempPoint.RotateOnAxis(rotation);
			newPoints.push_back({ center.x + tempPoint.x, center.y + tempPoint.y });
			tempPoint = { -points[0].x / 2, -points[0].y / 2 };
			tempPoint.RotateOnAxis(rotation);
			newPoints.push_back({ center.x + tempPoint.x, center.y + tempPoint.y });
		}
		return newPoints;
	default:
		for (vector<Vector2>::iterator it = points.begin(); it != points.end(); ++it)
		{
			Vector2 tempPoint(*it);
			if(rotation != 0)
				tempPoint.RotateOnAxis(rotation);
			newPoints.push_back({ center.x + tempPoint.x, center.y + tempPoint.y });
		}
		return newPoints;
	}
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
	return rotation;
}

const BODY_TYPE RigidBody2D::getType()
{
	return BODY_TYPE();
}

const bool RigidBody2D::isColliding(RigidBody2D rb_)
{
	vector<Vector2> rb1 = this->getPoints();
	vector<Vector2> rb2 = rb_.getPoints();
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
	default:
		switch (rb_.type)
		{
		case CIRCLE:
			return false;
		default:
			for (std::vector<Vector2>::iterator it = rb1.begin(); it != rb1.end(); ++it) {
				if (rb_.isInBoundaries(*it)) return true;
			}
			for (std::vector<Vector2>::iterator it = rb2.begin(); it != rb2.end(); ++it) {
				if (this->isInBoundaries(*it)) return true;
			}
			return false;
		}
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
			else
				return false;
		}
	default:
		vector<Vector2> rbp = this->getPoints();
		int n = rbp.size();
		if (n < 3)  return false;

		Vector2 extreme = { numeric_limits<float>::max(), point_.y };

		int count = 0, i = 0;
		do
		{
			int next = (i + 1) % n;

			if (segmentsIntersect(rbp[i], rbp[next], point_, extreme))
			{
				if (pointsOrientation(rbp[i], point_, rbp[next]) == 0)
					return point_.onSegment(rbp[i], rbp[next]);

				count++;
			}
			i = next;
		} while (i != 0);

		return count & 1;
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
		renderPoint = { center.x - (points[0].x), center.y - (points[0].x) };
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

void RigidBody2D::rotate(float eulerAngle_)
{
	rotation = eulerAngle_;
	rotation = fmod(rotation, 360);
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
