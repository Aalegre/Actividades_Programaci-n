#include "InputSystem.h"

void Input::setInput(bool pressed_)
{
	std::chrono::steady_clock::time_point newInput = std::chrono::steady_clock::now();
	pressedOld = pressed;
	pressed = pressed_;
	double currentStiffness;
	switch (type)
	{
	case TRIGGER:
		currentStiffness = stiffness * (std::chrono::duration_cast<std::chrono::microseconds>(newInput - lastInput).count());
		if(pressed_)
			axis.x += currentStiffness;
		else
			axis.x -= currentStiffness;
		if (axis.x > 1) axis.x = 1;
		if (axis.x < 0) axis.x = 0;
		break;
	case AXIS:
		currentStiffness = stiffness * (std::chrono::duration_cast<std::chrono::microseconds>(newInput - lastInput).count());
		if (pressed_)
			axis.x += currentStiffness;
		else
			axis.x -= currentStiffness;
		if (axis.x > 1) axis.x = 1;
		if (axis.x < -1) axis.x = -1;
		break;
	default:
		break;
	}
	lastInput = std::chrono::steady_clock::now();
}

void Input::setInput(bool axisX_, bool axisY_)
{
	lastInput = std::chrono::steady_clock::now();
}

void Input::setInput(float value_)
{
	lastInput = std::chrono::steady_clock::now();
}

void Input::setInput(Vector2 axis_)
{
	std::chrono::steady_clock::time_point newInput = std::chrono::steady_clock::now();
	pressedOld = pressed;
	pressed = true;
	axis = axis_;
	lastInput = std::chrono::steady_clock::now();
}

void Input::setButtonDown()
{
	buttonState = true;
}

void Input::setButtonUp()
{
	buttonState = false;
}

void Input::updateButton()
{
	this->setInput(buttonState);
}

void Input::updateInput()
{
	if (turnDown) {
		std::chrono::steady_clock::time_point newInput = std::chrono::steady_clock::now();
		double currentStiffness;
		switch (type)
		{
		case TRIGGER:
			currentStiffness = stiffness * (std::chrono::duration_cast<std::chrono::microseconds>(newInput - lastInput).count());
			if (axis.x < 0)
				axis.x += currentStiffness;
			else if (axis.x > 0)
				axis.x -= currentStiffness;
			if (axis.x > 1) axis.x = 1;
			if (axis.x < 0) axis.x = 0;
			break;
		case AXIS:
			currentStiffness = stiffness * (std::chrono::duration_cast<std::chrono::microseconds>(newInput - lastInput).count());
			if (axis.x < 0)
				axis.x += currentStiffness;
			else if (axis.x > 0)
				axis.x -= currentStiffness;
			if (axis.x > 1) axis.x = 1;
			if (axis.x < -1) axis.x = -1;
			if (axis.y < 0)
				axis.y += currentStiffness;
			else if (axis.y > 0)
				axis.y -= currentStiffness;
			if (axis.y > 1) axis.y = 1;
			if (axis.y < -1) axis.y = -1;
			break;
		default:
			break;
		}
		lastInput = std::chrono::steady_clock::now();
	}
}

void Input::resetInput()
{
	axis = { 0,0 };
	pressed = false;
	pressedOld = false;
}

const bool Input::inputDown()
{
	updateInput();
	switch (type)
	{
	case BUTTON:
		return !pressedOld && pressed;
	default:
		return axis.x != 0;
	}
}

const bool Input::input()
{
	updateInput();
	switch (type)
	{
	case BUTTON:
		return pressed;
	default:
		return axis.x != 0;
	}
}

const bool Input::inputUp()
{
	updateInput();
	switch (type)
	{
	case BUTTON:
		return pressedOld && !pressed;
	default:
		return axis.x != 0;
	}
}

const float Input::getValue()
{
	updateInput();
	return axis.x;
}

const Vector2 Input::getAxis()
{
	updateInput();
	return Vector2(axis);
}

Input& Input::operator=(bool pressed_)
{
	setInput(pressed_);
	return *this;
}


InputSystem::InputSystem()
{
}

Input& InputSystem::operator[](std::string key_)
{
	return inputs[key_];
}

void InputSystem::resetAll()
{
	for (auto& it : inputs) {
		it.second.resetInput();
	}
}
