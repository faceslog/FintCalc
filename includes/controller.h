//
// Created by CHABANE Hugo on 27/04/2021.
//

#ifndef FINTCALC_CONTROLLER_H
#define FINTCALC_CONTROLLER_H

#include "../imgui/imgui.h"
#include "fint.h"

enum Buttons
{
    Buttons_None,
    Buttons_Prime,
    Buttons_Gcd,
    Buttons_Lcm,
    Buttons_Mult,
    Buttons_Div,
    Buttons_Pow,
    Buttons_CopyAsFint
};

class Controller {

public:
    Controller();
    void DrawResult(fint& fint_a);
    void DrawButtons();
    void DrawGui();
    ~Controller();

private:
    Buttons toggled;
};

#endif
