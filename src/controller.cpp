//
// Created by faces on 27/04/2021.
//
#include "../includes/controller.h"

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

    ImGui::Spacing();
    if(ImGui::Button("GCD(A,B)")) toggled = Buttons_Gcd;
    ImGui::SameLine();
    if(ImGui::Button("LCM(A,B)")) toggled = Buttons_Lcm;
    ImGui::SameLine();
    if(ImGui::Button("CopyAsFint(A)")) toggled = Buttons_CopyAsFint;
}

void Controller::DrawResult(fint& fint_a)
{
    static unsigned long b = 1;

    if(toggled != Buttons_None)
    {
        switch (toggled)
        {
            case Buttons_Prime:
            {
                ImGui::BulletText("%s", fint_a.is_prime() ? "true" : "false");
                break;
            }
            case Buttons_Gcd:
            {
                fint fint_b(b);
                ImGui::Text("B: %s", fint_b.to_string().c_str());
                ImGui::InputScalar("B", ImGuiDataType_U32, &b);
                ImGui::BulletText("GCD(A,B) = %s", gcd(fint_a, fint_b).to_string().c_str());
                break;
            }
            case Buttons_Lcm:
            {
                fint fint_b(b);
                ImGui::Text("b: %s", fint_b.to_string().c_str());
                ImGui::InputScalar("B", ImGuiDataType_U32, &b);
                ImGui::BulletText("LCM(A,B) = %s", lcm(fint_a, fint_b).to_string().c_str());
                break;
            }
            case Buttons_Mult:
            {
                fint fint_b(b);
                ImGui::Text("B: %s", fint_b.to_string().c_str());
                ImGui::InputScalar("B", ImGuiDataType_U32, &b);
                ImGui::BulletText("A * B = %s", (fint_a * fint_b).to_string().c_str());
                break;
            }
            case Buttons_Div:
            {
                fint fint_b(b);
                ImGui::Text("B: %s", fint_b.to_string().c_str());
                ImGui::InputScalar("B", ImGuiDataType_U32, &b);

                if(fint_b.divides(fint_a))
                    ImGui::BulletText("A / B = %s", (fint_a / fint_b).to_string().c_str());
                else
                    ImGui::BulletText("Cannot divide a per b");
                break;
            }
            case Buttons_Pow:
            {
                fint fint_b(b);
                ImGui::Text("b: %s", fint_b.to_string().c_str());
                ImGui::InputScalar("b", ImGuiDataType_U32, &b);
                ImGui::BulletText("A^b = %s", fint_a.pow(b).to_string().c_str());
                break;
            }
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
    fint fint_a(a);
    ImGui::Text("A: %s", fint_a.to_string().c_str());
    ImGui::InputScalar("A", ImGuiDataType_U32, &a);

    DrawResult(fint_a);
    DrawButtons();

    ImGui::End();
}

Controller::Controller()
{
    this->toggled = Buttons_None;
}
