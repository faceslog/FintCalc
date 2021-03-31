//
// Created by CHABANE Hugo et Adrien Lesénéchal on 17/03/2021.
//

#include "../includes/fint.h"

fint::fint(int_t n)
{
    int a = n;
    int_t temp_factor {0};

    for(int i{2}; i <= n; i++)
    {
        // Si le nombre est divisible par i alors
        if((a % i) == 0)
        {
            temp_factor = i;    // Le facteur est donc i

            mult_t temp_power {0};
            while((a % i) == 0)
            {
                a = a / i;
                temp_power++;
            }

            this->dico.insert(std::make_pair(temp_factor, temp_power));
        }
    }
}

std::map<int_t, mult_t> fint::get_dico()
{
    return this->dico;
}
