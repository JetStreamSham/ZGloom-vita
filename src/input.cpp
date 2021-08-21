#include "input.h"
#include <psp2/ctrl.h>
#include <stdio.h>

namespace Input
{

    void Init()
    {
        sceCtrlPeekBufferPositive(0, &oldInput, 1);
        TRIANGLE = BUTTONSTATE_RELEASED;
        CIRCLE = BUTTONSTATE_RELEASED;
        SQUARE = BUTTONSTATE_RELEASED;
        CROSS = BUTTONSTATE_RELEASED;

        UP = BUTTONSTATE_RELEASED;
        DOWN = BUTTONSTATE_RELEASED;
        LEFT = BUTTONSTATE_RELEASED;
        RIGHT = BUTTONSTATE_RELEASED;

        LTRIGGER  = BUTTONSTATE_RELEASED;
        RTRIGGER = BUTTONSTATE_RELEASED;

        START  = BUTTONSTATE_RELEASED;
        SELECT  = BUTTONSTATE_RELEASED;
    }

    void Update()
    {
        sceCtrlPeekBufferPositive(0, &newInput, 1);
        if (newInput.buttons & SCE_CTRL_TRIANGLE)
        {
            if (oldInput.buttons & SCE_CTRL_TRIANGLE)
            {
                TRIANGLE = BUTTONSTATE_PRESSED;
            }
            else
            {
                TRIANGLE = BUTTONSTATE_UP;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_TRIANGLE)
            {
                TRIANGLE = BUTTONSTATE_DOWN;
            }
            else
            {
                TRIANGLE = BUTTONSTATE_RELEASED;
            }
        }

        if (newInput.buttons & SCE_CTRL_SQUARE)
        {
            if (oldInput.buttons & SCE_CTRL_SQUARE)
            {
                SQUARE = BUTTONSTATE_PRESSED;
            }
            else
            {
                SQUARE = BUTTONSTATE_DOWN;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_SQUARE)
            {
                SQUARE = BUTTONSTATE_UP;
            }
            else
            {
                SQUARE = BUTTONSTATE_RELEASED;
            }
        }

        if (newInput.buttons & SCE_CTRL_CIRCLE)
        {
            if (oldInput.buttons & SCE_CTRL_CIRCLE)
            {
                CIRCLE = BUTTONSTATE_PRESSED;
            }
            else
            {
                CIRCLE = BUTTONSTATE_DOWN;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_CIRCLE)
            {
                CIRCLE = BUTTONSTATE_UP;
            }
            else
            {
                CIRCLE = BUTTONSTATE_RELEASED;
            }
        }

        if (newInput.buttons & SCE_CTRL_CROSS)
        {
            if (oldInput.buttons & SCE_CTRL_CROSS)
            {
                CROSS = BUTTONSTATE_PRESSED;
            }
            else
            {
                CROSS = BUTTONSTATE_DOWN;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_CROSS)
            {
                CROSS = BUTTONSTATE_UP;
            }
            else
            {
                CROSS = BUTTONSTATE_RELEASED;
            }
        }

        if (newInput.buttons & SCE_CTRL_UP)
        {
            if (oldInput.buttons & SCE_CTRL_UP)
            {
                UP = BUTTONSTATE_PRESSED;
            }
            else
            {
                UP = BUTTONSTATE_UP;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_UP)
            {
                UP = BUTTONSTATE_DOWN;
            }
            else
            {
                UP = BUTTONSTATE_RELEASED;
            }
        }

        if (newInput.buttons & SCE_CTRL_DOWN)
        {
            if (oldInput.buttons & SCE_CTRL_DOWN)
            {
                DOWN = BUTTONSTATE_PRESSED;
            }
            else
            {
                DOWN = BUTTONSTATE_DOWN;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_DOWN)
            {
                DOWN = BUTTONSTATE_UP;
            }
            else
            {
                DOWN = BUTTONSTATE_RELEASED;
            }
        }

        if (newInput.buttons & SCE_CTRL_LEFT)
        {
            if (oldInput.buttons & SCE_CTRL_LEFT)
            {
                LEFT = BUTTONSTATE_PRESSED;
            }
            else
            {
                LEFT = BUTTONSTATE_DOWN;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_LEFT)
            {
                LEFT = BUTTONSTATE_UP;
            }
            else
            {
                LEFT = BUTTONSTATE_RELEASED;
            }
        }

        if (newInput.buttons & SCE_CTRL_RIGHT)
        {
            if (oldInput.buttons & SCE_CTRL_RIGHT)
            {
                RIGHT = BUTTONSTATE_PRESSED;
            }
            else
            {
                RIGHT = BUTTONSTATE_DOWN;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_RIGHT)
            {
                RIGHT = BUTTONSTATE_UP;
            }
            else
            {
                RIGHT = BUTTONSTATE_RELEASED;
            }
        }


        if (newInput.buttons & SCE_CTRL_START)
        {
            if (oldInput.buttons & SCE_CTRL_START)
            {
                START = BUTTONSTATE_PRESSED;
            }
            else
            {
                START = BUTTONSTATE_UP;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_START)
            {
                START = BUTTONSTATE_DOWN;
            }
            else
            {
                START = BUTTONSTATE_RELEASED;
            }
        }




        if (newInput.buttons & SCE_CTRL_SELECT)
        {
            if (oldInput.buttons & SCE_CTRL_SELECT)
            {
                SELECT = BUTTONSTATE_PRESSED;
            }
            else
            {
                SELECT = BUTTONSTATE_UP;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_SELECT)
            {
                SELECT = BUTTONSTATE_DOWN;
            }
            else
            {
                SELECT = BUTTONSTATE_RELEASED;
            }
        }



        if (newInput.buttons & SCE_CTRL_RTRIGGER)
        {
            if (oldInput.buttons & SCE_CTRL_RTRIGGER)
            {
                RTRIGGER = BUTTONSTATE_PRESSED;
            }
            else
            {
                RTRIGGER = BUTTONSTATE_UP;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_RTRIGGER)
            {
                RTRIGGER = BUTTONSTATE_DOWN;
            }
            else
            {
                RTRIGGER = BUTTONSTATE_RELEASED;
            }
        }




        if (newInput.buttons & SCE_CTRL_LTRIGGER)
        {
            if (oldInput.buttons & SCE_CTRL_LTRIGGER)
            {
                LTRIGGER = BUTTONSTATE_PRESSED;
            }
            else
            {
                LTRIGGER = BUTTONSTATE_UP;
            }
        }
        else
        {
            if (oldInput.buttons & SCE_CTRL_LTRIGGER)
            {
                LTRIGGER = BUTTONSTATE_DOWN;
            }
            else
            {
                LTRIGGER = BUTTONSTATE_RELEASED;
            }
        }

        oldInput = newInput;
    }

    bool GetButton(SceCtrlButtons button)
    {
        switch (button)
        {
        case SCE_CTRL_UP:
            return UP == BUTTONSTATE_PRESSED || UP == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_DOWN:
            return DOWN == BUTTONSTATE_PRESSED || DOWN == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_LEFT:
            return LEFT == BUTTONSTATE_PRESSED || LEFT == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_RIGHT:
            return RIGHT == BUTTONSTATE_PRESSED || RIGHT == BUTTONSTATE_DOWN;
            break;

        case SCE_CTRL_TRIANGLE:
            return TRIANGLE == BUTTONSTATE_PRESSED || TRIANGLE == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_SQUARE:
            return SQUARE == BUTTONSTATE_PRESSED || SQUARE == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_CROSS:
            return CROSS == BUTTONSTATE_PRESSED || CROSS == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_CIRCLE:
            return CIRCLE == BUTTONSTATE_PRESSED || CIRCLE == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_START:
            return START == BUTTONSTATE_PRESSED || START == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_SELECT:
            return SELECT == BUTTONSTATE_PRESSED || SELECT == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_LTRIGGER:
            return LTRIGGER == BUTTONSTATE_PRESSED || LTRIGGER == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_RTRIGGER:
            return RTRIGGER == BUTTONSTATE_PRESSED || RTRIGGER == BUTTONSTATE_DOWN;
            break;
        }

        return false;
    }

    bool GetButtonUp(SceCtrlButtons button)
    {
        switch (button)
        {
        case SCE_CTRL_UP:
            return UP == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_DOWN:
            return DOWN == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_LEFT:
            return LEFT == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_RIGHT:
            return RIGHT == BUTTONSTATE_UP;
            break;

        case SCE_CTRL_TRIANGLE:
            return TRIANGLE == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_SQUARE:
            return SQUARE == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_CROSS:
            return CROSS == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_CIRCLE:
            return CIRCLE == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_START:
            return START == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_SELECT:
            return SELECT == BUTTONSTATE_UP;
            break;
        case SCE_CTRL_RTRIGGER:
            return RTRIGGER== BUTTONSTATE_UP;
            break;
        case SCE_CTRL_LTRIGGER:
            return LTRIGGER== BUTTONSTATE_UP;
            break;
        }

        return false;
    }

    bool GetButtonDown(SceCtrlButtons button)
    {
        switch (button)
        {
        case SCE_CTRL_UP:
            return UP == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_DOWN:
            return DOWN == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_LEFT:
            return LEFT == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_RIGHT:
            return RIGHT == BUTTONSTATE_DOWN;
            break;

        case SCE_CTRL_TRIANGLE:
            return TRIANGLE == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_SQUARE:
            return SQUARE == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_CROSS:
            return CROSS == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_CIRCLE:
            return CIRCLE == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_START:
            return START == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_SELECT:
            return SELECT == BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_RTRIGGER:
            return RTRIGGER== BUTTONSTATE_DOWN;
            break;
        case SCE_CTRL_LTRIGGER:
            return LTRIGGER== BUTTONSTATE_DOWN;
            break;
        }

        return false;
    }

    Stick GetLeftStick()
    {
        return {newInput.lx, newInput.ly};
    }


    Stick GetRightStick()
    {
        return {newInput.rx, newInput.ry};
    }
}