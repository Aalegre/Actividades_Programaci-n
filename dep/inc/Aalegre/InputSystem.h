#pragma once

#include "Vector2.h"

#include <unordered_map>
#include <chrono>

const enum INPUT_TYPE {BUTTON, TRIGGER, AXIS};

class Input {
	const INPUT_TYPE type;
	const bool turnDown;
	const float stiffness;
	std::chrono::steady_clock::time_point lastInput;
	bool pressedOld = false;
	bool pressed = false;
	bool buttonState = false;
	Vector2 axis;

public:

	Input(INPUT_TYPE type_ = BUTTON, bool turnDown_ = true, float stiffness_ = 1) : type(type_), turnDown(turnDown_), stiffness(stiffness_), lastInput(std::chrono::steady_clock::now()) { resetInput(); };

	void setInput(bool pressed_);
	void setInput(bool axisX_, bool axisY_);
	void setInput(float value_);
	void setInput(Vector2 axis_);
	void setButtonDown();
	void setButtonUp();
	void updateButton();
	void updateInput();
	void resetInput();
	const bool inputDown();
	const bool input();
	const bool inputUp();
	const float getValue();
	const Vector2 getAxis();

	Input& operator=(bool pressed_);
};

class InputSystem
{
	std::unordered_map<std::string, Input> inputs;

	public:

	InputSystem();

	Input& operator[] (std::string);
	void resetAll();
};

