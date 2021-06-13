//
// Created by faceslog and Derugon on 17/03/2021.
//

#include "../includes/fint.h"

fint::fint() = default;

fint::fint(int_t n)
{
    if(n == 0)
    {
        throw std::invalid_argument("trying to create a fint from 0");
    }
    add_to_dico(n, 2);
    for(int_t i{3}; i*i <= n; i += 2)
    {
        add_to_dico(n, i);
    }
    if(n >= 2)
    {
        dico.insert(dico.cend(), std::make_pair(n, 1));
    }
}

fint::fint(const std::initializer_list<int_t>& lf, const std::initializer_list<mult_t>& lm)
{
    if(lf.size() != lm.size())
    {
        throw std::invalid_argument("trying to create a fint from two lists of different size");
    }
    for(auto ilf = lf.begin(), ilm = lm.begin(); ilf != lf.end(); ilf++, ilm++)
    {
        if (*ilm > 0)
        {
            dico.insert(std::make_pair(*ilf, *ilm));
        }
    }
}

int_t fint::to_int() const {
    int_t a{1}, b;
    for(auto const& elem : dico)
    {
        b = static_cast<int_t>(std::pow(elem.first, elem.second));
        if(a > MAX_INT_T/b)
        {
            throw std::overflow_error("trying to convert a fint to an int_t computation is too "
                                      "large for the destination type");
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
    fint r;
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
    fint r;
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
    fint r;

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
        throw std::domain_error("trying to solve a non-integer fint division");
    }
    fint r;
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
        throw std::domain_error("trying to solve a non-integer fint division");
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

std::pair<fint, fint> frac(const std::pair<fint, fint>& f)
{
    fint a, b;
    std::tie(a, b) = f;
    fint c, d;
    auto ia = a.dico.cbegin(), ib = b.dico.cbegin();
    while(ia != a.dico.cend() && ib != b.dico.cend())
    {
        if(ia->first < ib->first)
        {
            c.dico.insert(c.dico.cend(), *ia);
            ia++;
        }
        else if(ia->first > ib->first)
        {
            d.dico.insert(d.dico.cend(), *ib);
            ib++;
        }
        else
        {
            if(ia->second < ib->second)
            {
                d.dico.insert(d.dico.cend(), std::make_pair(ib->first, ib->second - ia->second));
            }
            else if(ia->second > ib->second)
            {
                c.dico.insert(c.dico.cend(), std::make_pair(ia->first, ia->second - ib->second));
            }
            ia++;
            ib++;
        }
    }
    for(; ia != a.dico.cend(); ia++)
    {
        c.dico.insert(c.dico.cend(), *ia);
    }
    for(; ib != b.dico.cend(); ib++)
    {
        d.dico.insert(d.dico.cend(), *ib);
    }
    return std::make_pair(c, d);
}

fint& fint::frac(fint& b)
{
    for(auto i = dico.begin(), ib = b.dico.begin(); i != dico.end() && ib != b.dico.end();)
    {
        if(i->first < ib->first)
        {
            i++;
        }
        else if(i->first > ib->first)
        {
            ib++;
        }
        else if(i->second < ib->second)
        {
            ib->second -= i->second;
            i = dico.erase(i);
            ib++;
        }
        else if(i->second > ib->second)
        {
            i->second -= ib->second;
            ib = b.dico.erase(ib);
            i++;
        }
        else
        {
            i = dico.erase(i);
            ib = b.dico.erase(ib);
        }
    }
    return *this;
}

fint pow(const fint& a, unsigned int n)
{
    if(n == 0)
    {
        return fint(1);
    }

    fint r;
    for(auto const& ia : a.dico)
    {
        r.dico.insert(r.dico.cend(), std::make_pair(ia.first, ia.second * n));
    }
    return r;
}

fint& fint::pow(unsigned int n)
{
    if(n == 0)
    {
        *this = fint(1);
    }
    else
    {
        for(auto& i : dico)
        {
            i.second *= n;
        }
    }

    return *this;
}

std::string fint::to_string() const
{
    if(dico.empty())
    {
        return "1";
    }

    std::string str;
    auto ia = dico.cbegin();
    auto second_last = std::prev(dico.cend(), 1);

    for(; ia != second_last; ia++)
    {
        str += std::to_string(ia->first) + '^' + std::to_string(ia->second) + '*';
    }
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