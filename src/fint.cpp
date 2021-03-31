//
// Created by CHABANE Hugo et Adrien Lesénéchal on 17/03/2021.
//

#include "../includes/fint.h"

fint::fint(int_t n)
{
   
    this->add_to_dico(n, 2);

    for(int_t i{3}; i*i <= n; i+=2)
    {
        this->add_to_dico(n, i);
    }

    if(n >= 2)
    {
        this->dico.insert(std::make_pair(n, 1));
    }
}

std::map<int_t, mult_t> fint::get_dico()
{
    return this->dico;
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

        this->dico.insert(std::make_pair(i, temp_power));
    }
}