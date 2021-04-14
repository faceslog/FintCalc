#include <iostream>
#include "../includes/fint.h"

int main()
{
    int_t Nombre;
    std::cout << "Entrez le nombre que vous voulez decomposer: ";
    std::cin >> Nombre;

    fint f(Nombre);

    std::cout << std::endl;
    std::cout << "L'Écriture en facteurs premiers est :" << std::endl;

    for(auto const& elem : f.get_dico())
    {
       std::cout << elem.first << "^" << elem.second << std::endl;
    }

    std::cout << "fint to int_t : " <<  f.to_int() << std::endl;
    std::cout << std::boolalpha;
    std::cout << "fint is a prime number: " << f.is_prime() << std::endl;

    fint a(25000);
    fint b(25000);

    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;


    return 0;
}