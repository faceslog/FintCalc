#include <cstdio>
#include <map>

int main()
{

    int Nombre, a;
    std::map<int, int> dico;

    printf("Entrez le nombre que vous voulez decomposer: ");
    scanf("%d",&Nombre);

    a = Nombre;

    int temp_factor {0};

    for(int i{2}; i <= Nombre; i++)
    {
        // Si le nombre est divisible par i alors
       if((a % i) == 0)
       {
           temp_factor = i;    // Le facteur est donc i

          int temp_power {0};
          while((a % i) == 0)
          {
              a = a / i;
              temp_power++;
          }

          dico.insert(std::make_pair(temp_factor, temp_power));
       }
    }

    printf("\n");
    printf("L'Écriture en facteurs premiers est :\n");

    for(auto const& elem : dico)
    {
        printf("Il y a %d puissance %d.\n", elem.first, elem.second);
    }


    printf("\n");

    return 0;
}