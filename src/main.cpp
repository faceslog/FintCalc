#include <cstdio>
#include "../includes/fint.h"

int main()
{

    int Nombre;
    printf("Entrez le nombre que vous voulez decomposer: ");
    scanf("%d",&Nombre);

    fint f(Nombre);

    printf("\n");
    printf("L'Écriture en facteurs premiers est :\n");

    for(auto const& elem : f.get_dico())
    {
        printf("Il y a %lu puissance %lu.\n", elem.first, elem.second);
    }
    printf("\n");

    return 0;
}