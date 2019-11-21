#include "Vector2.h"


//CONSTRUCT

Vector2::Vector2() {
	x = 0; y = 0;
}
Vector2::Vector2(const Vector2& copy_) {
	x = copy_.x; y = copy_.y;
}
Vector2::Vector2(const Vector2 origin_, const Vector2 end_) {
	x = end_.x - origin_.x;
	y = end_.y - origin_.y;
}
Vector2::Vector2(float x_, float y_) {
	x = x_; y = y_;
}

Vector2 Vector2::zero()
{
	return Vector2();
}

Vector2 Vector2::right()
{
	return Vector2(0, 1);
}

Vector2 Vector2::left()
{
	return Vector2(0, -1);
}

Vector2 Vector2::up()
{
	return Vector2(1, 0);
}

Vector2 Vector2::down()
{
	return Vector2(-1, 0);
}

//READ

const float Vector2::Magnitude() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

const float Vector2::Distance(Vector2 to_) {
	return sqrt(pow(to_.x - x, 2) + pow(to_.y - y, 2));
}

const float Vector2::Distance(Vector2 lineStart_, Vector2 lineEnd_)
{
	return 0.0f;
}

const float Vector2::GetEulerAngle()
{
	if (x == 0 && y == 0)
		return 0.0f;
	else {
		Vector2 vector(*this);
		vector.Normalize();
		float value = vector.xProduct(Vector2(1, 0));
		return acos(value) * 180.0 / PI;
	}
}

const float Vector2::xProduct(const Vector2& scalar_) {
	return x * scalar_.x + y * scalar_.y;
}

const bool Vector2::onSegment(Vector2 segment1_, Vector2 segment2_)
{
	if (x <= max(segment1_.x, segment2_.x) && x >= min(segment1_.x, segment2_.x) &&
		y <= max(segment1_.y, segment2_.y) && y >= min(segment1_.y, segment2_.y))
		return true;
	return false;
}

//MODIFY

void Vector2::Add(const Vector2 add_) {
	x += add_.x; y += add_.y;
}

void Vector2::Scale(const float scalar_) {
	x *= scalar_; y *= scalar_;
}

void Vector2::LookAt(const Vector2 look_) {
	x = look_.x - x;
	y = look_.y - y;
	this->Normalize();
}

void Vector2::Normalize() {
	float magnitude = this->Magnitude();
	x = x / magnitude;
	y = y / magnitude;
}

void Vector2::Project(const Vector2 vectorToProject_) {
	this->Scale(this->xProduct(vectorToProject_) / pow(this->Magnitude(), 2));
}

void Vector2::Clamp(const float magnitude_) {
	if (this->Magnitude() > magnitude_) {
		this->Normalize();
		this->Scale(magnitude_);
	}
}

void Vector2::FromEulerAngle(const float eulerAngle_) {
	x = cos(eulerAngle_ * PI / 180.0);
	y = sin(eulerAngle_ * PI / 180.0);
}

void Vector2::RotateOnAxis(const float eulerAngle_)
{
	Vector2 tempV(x, y);
	float deg = eulerAngle_ * PI / 180.0;
	x = tempV.x * cos(deg) + tempV.y * sin(deg);
	y = tempV.x * -sin(deg) + tempV.y * cos(deg);
}

//OPERATORS

Vector2 Vector2::operator+(const Vector2 vector_)
{
	return Vector2();
}

Vector2 Vector2::operator-(const Vector2 vector_)
{
	return Vector2();
}

Vector2 Vector2::operator*(const Vector2 vector_)
{
	return Vector2();
}

bool operator==(const Vector2 vector0_, const Vector2 vector1_)
{
	return vector0_.x == vector1_.x && vector0_.y == vector1_.y;
}

bool operator!=(const Vector2 vector0_, const Vector2 vector1_)
{
	return vector0_.x != vector1_.x || vector0_.y != vector1_.y;
}

//UTILS

// 0 --> Colinear
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int pointsOrientation(Vector2 p, Vector2 q, Vector2 r)
{
	float val =	(q.y - p.y) * (r.x - q.x) -
				(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;
	return (val > 0) ? 1 : 2;
}

bool segmentsIntersect(Vector2 segmentA_1_, Vector2 segmentA_2_, Vector2 segmentB_1_, Vector2 segmentB_2_)
{
	int o1 = pointsOrientation(segmentA_1_, segmentA_2_, segmentB_1_);
	int o2 = pointsOrientation(segmentA_1_, segmentA_2_, segmentB_2_);
	int o3 = pointsOrientation(segmentB_1_, segmentB_2_, segmentA_1_);
	int o4 = pointsOrientation(segmentB_1_, segmentB_2_, segmentA_2_);

	if (o1 != o2 && o3 != o4)
		return true;

	if (o1 == 0 && segmentB_1_.onSegment(segmentA_1_, segmentA_2_)) return true;

	if (o2 == 0 && segmentB_2_.onSegment(segmentA_1_, segmentA_2_)) return true;

	if (o3 == 0 && segmentA_1_.onSegment(segmentB_1_, segmentB_2_)) return true;

	if (o4 == 0 && segmentA_2_.onSegment(segmentB_1_, segmentB_2_)) return true;

	return false;
}
