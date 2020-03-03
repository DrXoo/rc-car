#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pinIn1, int pinIn2, int pinPWM)
{
    _currentDirection = Direction::Idle;
    _targetDirection = Direction::Idle;
    _currentSpeed = 0;
    _pinPWM = pinPWM;
    _pinIn1 = pinIn1;
    _pinIn2 = pinIn2;

    pinMode(pinIn1, OUTPUT);
    pinMode(pinIn2, OUTPUT);
    pinMode(pinPWM, OUTPUT);
}

void Motor::Update()
{
    switch (_currentDirection)
    {
    case Direction::Idle:
        _currentDirection = _targetDirection;
        break;
    case Direction::Clockwise:
    case Direction::AntiClockwise:
        if (_targetDirection == _currentDirection)
        {
            _NextSpeedValue(1);
        }
        else
        {
            _NextSpeedValue(-1);
        }

        if (_currentSpeed == 0)
        {
            _currentDirection = Direction::Idle;
        }
        break;
    }

    _SetupMotorsMovement();
    analogWrite(_pinPWM, _currentSpeed);
}

void Motor::SetDirection(Direction direction)
{
    _targetDirection = direction;
}

Direction Motor::GetDirection()
{
    return _currentDirection;
}

void Motor::_NextSpeedValue(int direction)
{
    if (millis() - _currentStepTime >= TIME_BETWEEN_STEPS)
    {
        _currentStepTime = millis();
        _currentSpeed += SPEED_STEPS * direction;
        if (direction == 1)
        {
            _currentSpeed = min(_currentSpeed, MAX_SPEED);
        }
        else
        {
            _currentSpeed = max(_currentSpeed, 0);
        }
    }
}

void Motor::_SetupMotorsMovement()
{
    if (_currentDirection == Direction::Clockwise)
    {
        digitalWrite(_pinIn1, HIGH);
        digitalWrite(_pinIn2, LOW);
    }
    if (_currentDirection == Direction::AntiClockwise)
    {
        digitalWrite(_pinIn1, LOW);
        digitalWrite(_pinIn2, HIGH);
    }
    if (_currentDirection == Direction::Idle)
    {
        digitalWrite(_pinIn1, LOW);
        digitalWrite(_pinIn2, LOW);
    }
}