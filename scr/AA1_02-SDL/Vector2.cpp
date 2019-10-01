#include "Vector2.h"


//CONSTRUCT

Vector2::Vector2() {
	x = 0; y = 0;
}
Vector2::Vector2(const Vector2& copy_) {
	x = copy_.x; y = copy_.y;
}
Vector2::Vector2(const Vector2& origin_, const Vector2& end_) {
	x = end_.x - origin_.x;
	y = end_.y - origin_.y;
}
Vector2::Vector2(float x_, float y_) {
	x = x_; y = y_;
}

//READ

const float Vector2::Magnitude(){
	return sqrt(pow(x, 2) + pow(y, 2));
}

const float Vector2::Distance(Vector2 to_){
	return sqrt(pow(to_.x - x, 2) + pow(to_.y - y, 2));
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

//MODIFY

void Vector2::Add(const Vector2 & add_){
	x += add_.x; y += add_.y;
}

void Vector2::Scale(const float scalar_){
	x *= scalar_; y *= scalar_;
}

void Vector2::LookAt(const Vector2 & look_){
	x = look_.x - x;
	y = look_.y - y;
	this->Normalize();
}

void Vector2::Normalize(){
	float magnitude = this->Magnitude();
	x = x / magnitude;
	y = y / magnitude;
}

void Vector2::Project(const Vector2& vectorToProject_){
	this->Scale(this->xProduct(vectorToProject_) / pow(this->Magnitude(), 2));
}

void Vector2::Clamp(const float magnitude_){
	if (this->Magnitude() > magnitude_) {
		this->Normalize();
		this->Scale(magnitude_);
	}
}

void Vector2::FromEulerAngle(const float eulerAngle_){
	x = cos(eulerAngle_ * PI / 180.0);
	y = sin(eulerAngle_ * PI / 180.0);
}

void Vector2::Lerp(const Vector2& end_, float position_, bool clamp_ = false)
{
	if (clamp_) {
		if (position_ > 1) position_ = 1;
		else if (position_ < 0) position_ = 0;
	}
	if (* this != end_) {

	}
}

//OPERATORS

Vector2 Vector2::operator+(const Vector2& vector_)
{
	return Vector2();
}

Vector2 Vector2::operator-(const Vector2& vector_)
{
	return Vector2();
}

Vector2 Vector2::operator*(const Vector2& vector_)
{
	return Vector2();
}

bool operator==(const Vector2& vector0_, const Vector2& vector1_)
{
	return vector0_.x != vector1_.x || vector0_.y != vector1_.y;
}

bool operator!=(const Vector2& vector0_, const Vector2& vector1_)
{
	return vector0_.x == vector1_.x && vector0_.y == vector1_.y;
}
