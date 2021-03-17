#include <cstdio>

int main()
{

    int compteur, Nombre, a, i, j;
    int facteur[256];
    int puissance[256];

    i = 255;
    do
    {
         puissance[i] = facteur[i] = 0;
    }
    while(--i >= 0);


    printf("Entrez le nombre que vous voulez decomposer: ");
    scanf("%d",&Nombre);

    j=0;
    a=Nombre;

    for(i=2; i<=Nombre; i++)
    {
        // Si le nombre est divisible par i alors
       if((a % i) == 0)
       {
          // J'augmente j l'indice des puissances et facteurs
          compteur = j; // Ce compteur retient la dernière valeur de j
          facteur[j] = i;    // Le facteur est donc i

          while((a % i) == 0)
          {
              a= a / i;
            puissance[j]++;
          }

          j++;
       }

    }

    printf("\n");
    printf("L'Écriture en facteurs premiers est :\n");

    for(j=0; j<=compteur; j++)
    {
        printf("Il y a %d facteurs %d.\n",puissance[j],facteur[j]);
    }

    printf("\n");

    return 0;
}