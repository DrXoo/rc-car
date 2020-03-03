#include "Arduino.h"
#include "Controller.h"

Controller::Controller(const Motor &motorA, const Motor &motorB, int pinEnable) : _motorA(motorA), _motorB(motorB)
{
    _pinEnable = pinEnable;

    pinMode(_pinEnable, OUTPUT);
}

void Controller::Update()
{
    _motorA.Update();
    _motorB.Update();
}

void Controller::Move(MovementDirection direction)
{
    switch (direction)
    {
    case MovementDirection::Forward:
        _motorA.SetDirection(Direction::Clockwise);
        _motorB.SetDirection(Direction::Clockwise);
        break;
    case MovementDirection::Backward:
        _motorA.SetDirection(Direction::AntiClockwise);
        _motorB.SetDirection(Direction::AntiClockwise);
        break;
    case MovementDirection::Left:
        _motorA.SetDirection(Direction::Clockwise);
        _motorB.SetDirection(Direction::AntiClockwise);
        break;
    case MovementDirection::Right:
        _motorA.SetDirection(Direction::AntiClockwise);
        _motorB.SetDirection(Direction::Clockwise);
        break;
    case MovementDirection::Stop:
        _motorA.SetDirection(Direction::Idle);
        _motorB.SetDirection(Direction::Idle);
        break;
    default:
        break;
    }

    if (_motorA.GetDirection() == Direction::Idle &&
        _motorB.GetDirection() == Direction::Idle)
    {
        digitalWrite(_pinEnable, LOW);
    }
    else
    {
        digitalWrite(_pinEnable, HIGH);
    }
}