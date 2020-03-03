#pragma once

#include "Arduino.h"

enum Direction{
    Idle = 0,
    Clockwise = 1,
    AntiClockwise = 2
};

class Motor
{
    const int MAX_SPEED = 255;
    const int SPEED_STEPS = 30;
    const int TIME_BETWEEN_STEPS = 30; 
    public:
        Motor(int pinIn1, int pinIn2, int pinPWM);
        Motor();
        void SetDirection(Direction direction);
        Direction GetDirection();
        void Enable();
        void Update();
        void Disable();
    private:
        void _SetupMotorsMovement();
        void _NextSpeedValue(int direction);
        Direction _currentDirection;
        Direction _targetDirection;
        unsigned long _currentStepTime;
        int _currentSpeed;
        int _pinPWM;
        int _pinIn1;
        int _pinIn2;
};  
