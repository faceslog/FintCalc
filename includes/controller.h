//
//
// Created by faceslog and Derugon on 17/03/2021.
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
    void DrawGui();
    ~Controller();

private:
    static void DrawResultIsPrime(fint& fint_a);
    void DrawResultGcd(fint& fint_a);
    void DrawResultLcm(fint& fint_a);
    void DrawResultMult(fint& fint_a);
    void DrawResultDiv(fint& fint_a);
    void DrawResultPow(fint& fint_a);

    void ParseResult(fint& fint_a);
    void DrawButtons();

    Buttons toggled;
    unsigned long b {1};

};

#endif
