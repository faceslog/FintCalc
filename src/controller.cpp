//
// Created by faceslog and Derugon on 17/03/2021.
//

#include "../includes/controller.h"

Controller::Controller()
{
    this->toggled = Buttons_None;
    this->b = 1;
}

void Controller::DrawButtons()
{
    ImGui::Spacing();
    if(ImGui::Button("A * B")) toggled = Buttons_Mult;
    ImGui::SameLine();
    if(ImGui::Button("A DIV B")) toggled = Buttons_Div;
    ImGui::SameLine();
    if(ImGui::Button("A^b")) toggled = Buttons_Pow;
    ImGui::SameLine();
    if(ImGui::Button("isPrime(A)")) toggled = Buttons_Prime;
    ImGui::SameLine();
    if(ImGui::Button("GCD(A,B)")) toggled = Buttons_Gcd;

    ImGui::Spacing();
    if(ImGui::Button("LCM(A,B)")) toggled = Buttons_Lcm;
    ImGui::SameLine();
    if(ImGui::Button("CopyAsFint(A)")) toggled = Buttons_CopyAsFint;
}

void Controller::ParseResult(fint& fint_a)
{
    if(toggled != Buttons_None)
    {
        switch (toggled)
        {
            case Buttons_Prime:
                DrawResultIsPrime(fint_a);
                break;
            case Buttons_Gcd:
                DrawResultGcd(fint_a);
                break;
            case Buttons_Lcm:
                DrawResultLcm(fint_a);
                break;
            case Buttons_Mult:
                DrawResultMult(fint_a);
                break;
            case Buttons_Div:
                DrawResultDiv(fint_a);
                break;
            case Buttons_Pow:
                DrawResultPow(fint_a);
                break;
            case Buttons_CopyAsFint:
            {
                ImGui::LogToClipboard();
                ImGui::LogText("%s", fint_a.to_string().c_str());
                ImGui::LogFinish();
                toggled = Buttons_None;
                break;
            }
            default:
                toggled = Buttons_None;
        }
    }
}

void Controller::DrawGui()
{
    static unsigned long a = 1;
    ImGui::Begin("Fint Calculator", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
    ImGui::SetWindowFontScale(1.5);

    try
    {
        fint fint_a(a);
        ImGui::Text("A: %s", fint_a.to_string().c_str());
        ImGui::InputScalar("A", ImGuiDataType_U32, &a);
        ParseResult(fint_a);

    } catch (const std::exception& error)
    {
        a = 1;
    }

    DrawButtons();
    ImGui::End();
}

void Controller::DrawResultIsPrime(fint &fint_a)
{
    ImGui::BulletText("%s", fint_a.is_prime() ? "A is a prime number" : "A not a prime Number");
}

void Controller::DrawResultGcd(fint &fint_a)
{
    try
    {
        fint fint_b(b);
        ImGui::Text("B: %s", fint_b.to_string().c_str());
        ImGui::InputScalar("B", ImGuiDataType_U32, &b);
        ImGui::BulletText("GCD(A,B) = %s", gcd(fint_a, fint_b).to_string().c_str());
    }
    catch (const std::exception& error)
    {
        b = 1;
    }
}

void Controller::DrawResultLcm(fint &fint_a)
{
    try
    {
        fint fint_b(b);
        ImGui::Text("B: %s", fint_b.to_string().c_str());
        ImGui::InputScalar("B", ImGuiDataType_U32, &b);
        ImGui::BulletText("LCM(A,B) = %s", lcm(fint_a, fint_b).to_string().c_str());
    }
    catch (const std::exception& error)
    {
        b = 1;
    }

}

void Controller::DrawResultMult(fint &fint_a)
{
    try
    {
        fint fint_b(b);
        ImGui::Text("B: %s", fint_b.to_string().c_str());
        ImGui::InputScalar("B", ImGuiDataType_U32, &b);
        ImGui::BulletText("A * B = %s", (fint_a * fint_b).to_string().c_str());
    }
    catch (const std::exception& error)
    {
        b = 1;
    }
}

void Controller::DrawResultDiv(fint &fint_a)
{
    try
    {
        fint fint_b(b);
        ImGui::Text("B: %s", fint_b.to_string().c_str());
        ImGui::InputScalar("B", ImGuiDataType_U32, &b);

        if(fint_b.divides(fint_a))
        {
            ImGui::BulletText("A / B = %s", (fint_a / fint_b).to_string().c_str());
        }
        else
        {
            fint fint_c, fint_d;
            std::tie(fint_c, fint_d) = frac(std::make_pair(fint_a, fint_b));
            ImGui::BulletText("A / B = (%s) / (%s)", fint_c.to_string().c_str(), fint_d.to_string().c_str());
        }

    }
    catch(const std::exception& error)
    {
        b = 1;
    }

}

void Controller::DrawResultPow(fint &fint_a)
{
    try
    {
        ImGui::InputScalar("B", ImGuiDataType_U32, &b);
        ImGui::BulletText("A^b = %s", fint_a.pow(b).to_string().c_str());
    }
    catch (const std::exception& error)
    {
        b = 1;
    }
}

Controller::~Controller() = default;
