#include <iostream>
#include "../includes/fint.h"

int main()
{
    int_t Nombre;
    std::cout << "Entrez le nombre que vous voulez décomposer : ";
    std::cin >> Nombre;

    fint a(Nombre);

    std::cout << std::endl;
    std::cout << "L'écriture en facteurs premiers de a est :" << std::endl;
    std::cout << a;
    std::cout << "a.to_int() : " <<  a.to_int() << std::endl;
    std::cout << std::boolalpha;
    std::cout << "a.is_prime() : " << a.is_prime() << std::endl;

    std::cout << "Entrez le second nombre avec lequel réaliser les calculs : ";
    std::cin >> Nombre;
    fint b(Nombre);
    std::cout << "L'écriture en facteurs premiers de b est :" << std::endl;
    std::cout << b;

    std::cout << "\nOpérations de comparaison: " << std::endl;
    std::cout << "a == b : " << (a == b) << std::endl;
    std::cout << "a != b : " << (a != b) << std::endl;

    std::cout << "lcm(a, b) : " << lcm(a, b).to_int() << std::endl;
    std::cout << lcm(a, b);
    std::cout << "gcd(a, b) : " << gcd(a, b).to_int() << std::endl;
    std::cout << gcd(a, b);

    unsigned int n;
    std::cout << "Entrez la puissance à utiliser : ";
    std::cin >> n;
    std::cout << "pow(a, n) : " << pow(a, n).to_int() << std::endl;
    std::cout << pow(a, n);

    return 0;
}