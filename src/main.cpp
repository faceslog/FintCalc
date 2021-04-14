#include <iostream>
#include "../includes/fint.h"

int main()
{
    int_t Nombre;
    std::cout << "Entrez le nombre que vous voulez décomposer: ";
    std::cin >> Nombre;
    std::cout << std::endl;

    fint a(Nombre);
    std::cout << "Écriture en facteurs premiers de a est: " << a << std::endl;
    std::cout << std::boolalpha;
    std::cout << "a.to_int() : " <<  a.to_int() << std::endl;
    std::cout << "a.is_prime() : " << a.is_prime() << std::endl;
    std::cout << std::endl;

    std::cout << "Entrez le second nombre avec lequel réaliser les calculs: ";
    std::cin >> Nombre;
    fint b(Nombre);
    std::cout << "Écriture en facteurs premiers de b est: " << b << std::endl;
    std::cout << "b.divides(a) : " << b.divides(a) << std::endl;
    std::cout << std::endl;
    
    std::cout << "============= Operator overloading =============" << std::endl;
    std::cout << "a == b : " << (a == b) << " & a != b : " << (a != b) << std::endl;
    std::cout << "a * b = " << (a*b) << std::endl;
    std::cout << "a / b = " << (a/b) << std::endl;
    
    uint32_t n;
    std::cout << "Entrez la puissance à utiliser : ";
    std::cin >> n;
    std::cout << "pow(a, n) = " << pow(a, n) << std::endl;
    std::cout << std::endl;

    std::cout << "============= LCM & GCD =============" << std::endl;
    std::cout << "lcm(a, b) = " << lcm(a, b) << std::endl;
    std::cout << "gcd(a, b) = " << gcd(a,b) << std::endl;
    std::cout << std::endl;

    return 0;
}