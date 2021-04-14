//
// Created by CHABANE Hugo et Adrien Lesénéchal on 17/03/2021.
//

#include "../includes/fint.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

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

fint::fint(const fint& f): dico(f.dico) {}

fint::~fint() = default;

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

bool fint::divides(const fint& a) const
{
    auto i = dico.cbegin();
    for (auto ia = a.dico.cbegin(); ia != a.dico.cend() && i != dico.cend(); ia++)
    {
        if (ia->first < i->first)
        {
            continue;
        }
        if (ia->first > i->first || ia->second < i->second)
        {
            return false;
        }
        if (ia->first == i->first)
        {
            i++;
        }
    }
    return i == dico.cend();
}

bool fint::is_prime() const
{
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

fint lcm(const fint& a, const fint& b)
{
    fint r(1);
    auto ia = a.dico.cbegin(), ib = b.dico.cbegin();
    while (ia != a.dico.cend() && ib != b.dico.cend())
    {
        if (ia->first < ib->first || (ia->first == ib->first && ia->second > ib->second))
        {
            r.dico.insert(r.dico.cend(), *ia);
            ia++;
        }
        else
        {
            r.dico.insert(r.dico.cend(), *ib);
            ib++;
        }
    }
    for (; ia != a.dico.cend(); ia++)
    {
        r.dico.insert(r.dico.cend(), *ia);
    }
    for (; ib != b.dico.cend(); ib++)
    {
        r.dico.insert(r.dico.cend(), *ib);
    }
    return r;
}

fint gcd(const fint& a, const fint& b)
{
    fint r(1);
    auto ia = a.dico.cbegin(), ib = b.dico.cbegin();
    while (ia != a.dico.cend() && ib != b.dico.cend())
    {
        if (ia->first < ib->first)
        {
            ia++;
        }
        else if (ia->first > ib->first)
        {
            ib++;
        }
        else
        {
            r.dico.insert(r.dico.cend(), ia->second < ib->second ? *ia : *ib);
            ia++;
            ib++;
        }
    }
    return r;
}

fint operator*(const fint &a, const fint &b)
{
    fint sum(1);

    auto ia = a.dico.cbegin(), ib = b.dico.cbegin();
    while (ia != a.dico.cend() && ib != b.dico.cend())
    {
        if (ia->first == ib->first)
        {
            // x^a * x^b = x^(a+b)
            sum.dico.insert(sum.dico.end(), std::make_pair(ia->first, ia->second + ib->second));
            ia++;
            ib++;
        }
        else if(ia->first < ib->first)
        {
            sum.dico.insert(sum.dico.end(), std::make_pair(ia->first,  ia->second));
            ia++;
        }
        else if(ia->first > ib->first)
        {
            sum.dico.insert(sum.dico.end(), std::make_pair(ib->first,  ib->second));
            ib++;
        }
    }

    return sum;
}

fint operator/(const fint& a, const fint& b)
{
    if (!b.divides(a))
    {
        throw std::domain_error("AAAAAAAAAAAAAAAAH");
    }
    fint r(1);
    auto ia = a.dico.cbegin();
    for (auto ib = b.dico.cbegin(); ib != b.dico.cend(); ia++)
    {
        if (ia->first < ib->first)
        {
            r.dico.insert(r.dico.cend(), *ia);
        }
        else
        {
            r.dico.insert(r.dico.cend(), std::make_pair(ia->first, ia->second - ib->second));
            ib++;
        }
    }
    for (; ia != a.dico.cend(); ia++)
    {
        r.dico.insert(r.dico.cend(), *ia);
    }
    return r;
}

fint pow(const fint& a, unsigned int n)
{
    fint r(1);
    for (auto ia = a.dico.begin(); ia != a.dico.end(); ia++)
    {
        r.dico.insert(r.dico.cend(), std::make_pair(ia->first, ia->second * n));
    }
    return r;
}

std::ostream& operator<<(std::ostream& os, const fint& a)
{
    for(auto const& elem : a.dico)
    {
        // We need to flush the ostream, the std::endl is doing the flush
        os << elem.first << '^' << elem.second <<  std::endl;
    }

    return os;
}
