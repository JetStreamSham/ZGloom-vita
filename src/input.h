#pragma once
#include <psp2/ctrl.h>

namespace Input
{
    struct Stick
    {
        unsigned char x;
        unsigned char y;
    };
    static SceCtrlData oldInput;
    static SceCtrlData newInput;

    enum ButtonState
    {
        BUTTONSTATE_PRESSED = 1,
        BUTTONSTATE_RELEASED = 0,
        BUTTONSTATE_UP = 2,
        BUTTONSTATE_DOWN = 3,
    };

    static ButtonState TRIANGLE;
    static ButtonState SQUARE;
    static ButtonState CROSS;
    static ButtonState CIRCLE;

    static ButtonState UP;
    static ButtonState DOWN;
    static ButtonState LEFT;
    static ButtonState RIGHT;

    static ButtonState RTRIGGER;
    static ButtonState LTRIGGER;

    static ButtonState START;
    static ButtonState SELECT;

    bool GetButton(SceCtrlButtons button);
    bool GetButtonUp(SceCtrlButtons button);
    bool GetButtonDown(SceCtrlButtons button);
    Stick GetLeftStick();
    Stick GetRightStick();

    void Init();
    void Update();
}
