#pragma once

#include "Arduino.h"
#include "Motor.h"

enum MovementDirection{
    Forward,
    Backward,
    Left,
    Right,
    Stop
};

class Controller
{
    public:
        Controller(const Motor& motorA, const Motor& motorB, int pinEnable);
        void Update();
        void Move(MovementDirection direction);
    private:
        MovementDirection _currentMovementDirection;
        int _pinEnable;
        Motor _motorA;
        Motor _motorB;
};

