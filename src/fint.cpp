//
// Created by CHABANE Hugo et Adrien LESENECHAL on 17/03/2021.
//

#include "../includes/fint.h"

fint::fint(int_t n)
{
    if(n <= 0 ) throw std::domain_error("A fint cannot be created with a value less or equal to 0");

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
    if(lf.size() != lm.size())
    {
        throw std::runtime_error("il manque des facteurs ou multiplicateurs.");
    }
    for(auto ilf = lf.begin(), ilm = lm.begin(); ilf != lf.end(); ilf++, ilm++)
    {
        dico.insert(dico.end(), std::make_pair(*ilf, *ilm));
    }
}

int_t fint::to_int() const {
    int_t a{1};

    for(auto const& elem : dico)
    {
        auto b = static_cast<int_t>(std::pow(elem.first, elem.second));

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
    for(auto ia = a.dico.cbegin(); ia != a.dico.cend() && i != dico.cend(); ia++)
    {
        if(ia->first < i->first)
        {
            continue;
        }
        if(ia->first > i->first || ia->second < i->second)
        {
            return false;
        }
        if(ia->first == i->first)
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
    return a.dico == b.dico;
}

bool operator!=(const fint &a, const fint &b)
{
    return a.dico != b.dico;
}

fint lcm(const fint& a, const fint& b)
{
    fint r(1);
    auto ia = a.dico.cbegin(), ib = b.dico.cbegin();
    while(ia != a.dico.cend() && ib != b.dico.cend())
    {
        if(ia->first < ib->first || (ia->first == ib->first && ia->second > ib->second))
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
    for(; ia != a.dico.cend(); ia++)
    {
        r.dico.insert(r.dico.cend(), *ia);
    }
    for(; ib != b.dico.cend(); ib++)
    {
        r.dico.insert(r.dico.cend(), *ib);
    }
    return r;
}

fint& fint::lcm(const fint& b)
{
    auto i = dico.begin();
    auto ib = b.dico.cbegin();
    while(i != dico.end() && ib != b.dico.cend())
    {
        if(i->first < ib->first || (i->first == ib->first && i->second > ib->second))
        {
            i++;
        }
        else
        {
            dico.insert(i, *ib);
            ib++;
        }
    }
    for(; ib != b.dico.cend(); ib++)
    {
        dico.insert(dico.cend(), *ib);
    }
    return *this;
}

fint gcd(const fint& a, const fint& b)
{
    fint r(1);
    auto ia = a.dico.cbegin(), ib = b.dico.cbegin();
    while(ia != a.dico.cend() && ib != b.dico.cend())
    {
        if(ia->first < ib->first)
        {
            ia++;
        }
        else if(ia->first > ib->first)
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

fint& fint::gcd(const fint& b)
{
    auto i = dico.begin();
    auto ib = b.dico.cbegin();
    while(i != dico.end() && ib != b.dico.cend())
    {
        if(i->first < ib->first)
        {
            i = dico.erase(i);
        }
        else if(i->first > ib->first)
        {
            ib++;
        }
        else
        {
            if (i->second > ib->second)
            {
                i->second = ib->second;
            }
            i++;
            ib++;
        }
    }
    return *this;
}

fint operator*(const fint &a, const fint &b)
{
    fint r(1);

    auto ia = a.dico.cbegin(), ib = b.dico.cbegin();

    while(ia != a.dico.cend() && ib != b.dico.cend())
    {
        if(ia->first < ib->first)
        {
            r.dico.insert(r.dico.cend(), *ia);
            ia++;
        }
        else if(ia->first > ib->first)
        {
            r.dico.insert(r.dico.cend(), *ib);
            ib++;
        }
        else
        {
            r.dico.insert(r.dico.cend(), std::make_pair(ia->first, ia->second + ib->second));
            ia++;
            ib++;
        }
    }

    for(; ia != a.dico.cend(); ia++)
    {
        r.dico.insert(r.dico.cend(), *ia);
    }

    for(; ib != b.dico.cend(); ib++)
    {
        r.dico.insert(r.dico.cend(), *ib);
    }

    return r;
}

fint& fint::operator*=(const fint& b)
{
    auto i = dico.begin();
    auto ib = b.dico.cbegin();
    while(i != dico.end() && ib != b.dico.cend())
    {
        if(i->first < ib->first)
        {
            i++;
        }
        else if(i->first > ib->first)
        {
            dico.insert(i, *ib);
            ib++;
        }
        else
        {
            i->second += ib->second;
            i++;
            ib++;
        }
    }
    for(; ib != b.dico.cend(); ib++)
    {
        dico.insert(dico.cend(), *ib);
    }
    return *this;
}

fint operator/(const fint& a, const fint& b)
{
    if(!b.divides(a))
    {
        throw std::domain_error("Error trying to divide the both fint");
    }

    fint r(1);
    auto ia = a.dico.cbegin();

    for(auto ib = b.dico.cbegin(); ib != b.dico.cend(); ia++)
    {
        if(ia->first < ib->first)
        {
            r.dico.insert(r.dico.cend(), *ia);
        }
        else if(ia->second > ib->second)
        {
            r.dico.insert(r.dico.cend(), std::make_pair(ia->first, ia->second - ib->second));
            ib++;
        }
        else
        {
            ib++;
        }
    }

    for(; ia != a.dico.cend(); ia++)
    {
        r.dico.insert(r.dico.cend(), *ia);
    }

    return r;
}

fint& fint::operator/=(const fint& b)
{
    if(!b.divides(*this))
    {
        throw std::domain_error("Error trying to divide the both fint");
    }
    auto i = dico.begin();
    auto ib = b.dico.cbegin();
    while(ib != b.dico.cend())
    {
        if(i->first < ib->first)
        {
            i++;
        }
        else if(i->second > ib->second)
        {
            i->second -= ib->second;
            i++;
            ib++;
        }
        else
        {
            i = dico.erase(i);
            ib++;
        }
    }
    return *this;
}

fint pow(const fint& a, unsigned int n)
{
    fint r(1);
    for(auto const& ia : a.dico)
    {
        r.dico.insert(r.dico.cend(), std::make_pair(ia.first, ia.second * n));
    }
    return r;
}

fint& fint::pow(unsigned int n)
{
    for(auto& i : dico)
    {
        i.second *= n;
    }
    return *this;
}

std::string fint::to_string() const
{
    if(dico.empty()) return "1";

    std::string str;
    auto ia = dico.cbegin();
    auto second_last = std::prev(dico.end(), 1);

    for(; ia != second_last; ia++)
    {
        str += std::to_string(ia->first) + '^' + std::to_string(ia->second) + '*';
    }
    // to avoid the '*' for the last element of the map and only if the map is not empty
    str += std::to_string(ia->first) + '^' + std::to_string(ia->second);

    return str;
}

std::ostream& operator<<(std::ostream& os, const fint& a)
{
    return os << a.to_string();
}

fint::~fint() = default;

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