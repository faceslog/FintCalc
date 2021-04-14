//
// Created by CHABANE Hugo et Adrien Lesénéchal on 17/03/2021.
//

#include "../includes/fint.h"
#include <cmath>
#include <stdexcept>

fint::fint(int_t n)
{
    add_to_dico(n, 2);

    for(int_t i{3}; i*i <= n; i+=2)
    {
        add_to_dico(n, i);
    }

    if(n >= 2)
    {
        dico.insert(dico.end(), std::make_pair(n, 1));
    }
}

fint::fint(const std::initializer_list<int_t>& lf, const std::initializer_list<mult_t>& lm)
{
    if (lf.size() != lm.size())
    {
        throw std::runtime_error("il manque des facteurs ou multiplicateurs.");
    }
    for (auto ilf = lf.begin(), ilm = lm.begin(); ilf != lf.end(); ilf++, ilm++)
    {
        dico.insert(dico.end(), std::make_pair(*ilf, *ilm));
    }
}

std::map<int_t, mult_t> fint::get_dico() const
{
    return dico;
}

void fint::add_to_dico(int_t& a, const int_t& i)
{
    if((a % i) == 0)
    {
        mult_t temp_power {0};
        while((a % i) == 0)
        {
            a = a / i;
            temp_power++;
        }

        dico.insert(dico.end(), std::make_pair(i, temp_power));
    }
}

int_t fint::to_int() const {
    int_t a{1};

    for(auto const& elem : dico)
    {
        int_t b = std::pow(elem.first, elem.second);

        if( a > MAX_INT_T/b)
        {
            throw std::overflow_error("[ERROR] trying to convert a fint to an int_t computation is too large for the destination type");
        }

        a *= b;
    }

    return a;
}

bool fint::is_prime() const {
    // Si il n'y a que un élément dans notre map et que la puissance de cet élément est 1 alors ce nombre est un nombre premier.
    return dico.size() == 1 && dico.begin()->second == 1;
}

bool operator==(const fint& a, const fint &b)
{
    return a.dico == b.dico ;
}

bool operator!=(const fint &a, const fint &b)
{
    return a.dico != b.dico;
}

std::ostream& operator<<(std::ostream& os, const fint& a)
{
    /*for(auto const& elem : a.dico)
    {
        os << elem.first << '^' << elem.second << '\n';
    }*/

    os << a.to_int();

    return os;
}

fint::~fint() = default;
