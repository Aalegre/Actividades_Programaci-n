#pragma once

#include <vector>
#include "Vector2.h"

#define GRAVITY_Y = 9.81F;
#define GRAVITY_X = 0;

const enum BODY_TYPE { CIRCLE, BOX, POLYGON, COUNT };

class RigidBody2D {

private:
	vector<Vector2> points;
	float rotation;
	Vector2 force;
	Vector2 renderPoint;
	pair<Vector2, Vector2> boundaries;
	BODY_TYPE type;
	Vector2 center;

public:
	bool isStatic;

	RigidBody2D(Vector2 center_, float radius_, bool isStatic_ = false);						//Circle
	RigidBody2D(Vector2 center_, Vector2 size_, bool isStatic_ = false);						//Box
	RigidBody2D(Vector2 center_, const vector<Vector2> & points_, bool isStatic_ = false);	//Polygon

	const float getRadius();
	const Vector2 getSize();
	const pair<Vector2, Vector2> getBoundaries();
	const vector<Vector2> getPoints();
	const Vector2 getCenter();
	const Vector2 getRenderPoint();
	const Vector2 getCurrentForce();
	const Vector2 getDirection();
	const float getRotation();
	const BODY_TYPE getType();

	const bool isColliding(RigidBody2D rb_);
	const bool isInBoundaries(Vector2 point_);

	void calculateBoundaries();
	void calculateRenderPoint();
	void rotate(float eulerAngle_);
	void move(Vector2 force_);
	void teleport(Vector2 position_);
};