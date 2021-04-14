#include <iostream>
#include "../includes/fint.h"

int main()
{
    int_t Nombre;
    std::cout << "Entrez le nombre que vous voulez décomposer : ";
    std::cin >> Nombre;

    fint a(Nombre);

    std::cout << std::endl;
    std::cout << "L'écriture en facteurs premiers est :" << std::endl;

    for(auto const& elem : a.get_dico())
    {
        std::cout << elem.first << "^" << elem.second << std::endl;
    }
    // std::cout << a;

    std::cout << "a.to_int() : " <<  a.to_int() << std::endl;
    std::cout << std::boolalpha;
    std::cout << "a.is_prime() : " << a.is_prime() << std::endl;

    std::cout << "Entrez le second nombre avec lequel réaliser les calculs : ";
    std::cin >> Nombre;
    fint b(Nombre);
    std::cout << "L'écriture en facteurs premiers est :" << std::endl;
    for(auto const& elem : b.get_dico())
    {
        std::cout << elem.first << "^" << elem.second << std::endl;
    }

    std::cout << "a == b : " << (a == b) << std::endl;
    std::cout << "a != b : " << (a != b) << std::endl;

    fint l = lcm(a, b);
    std::cout << "lcm(a, b) :" << std::endl;
    for(auto const& elem : l.get_dico())
    {
        std::cout << elem.first << "^" << elem.second << std::endl;
    }

    return 0;
}