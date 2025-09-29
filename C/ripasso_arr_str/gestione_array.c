#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 5

int main(int argc, char *argv[])
{
    // Dichiarazione delle variabili
    int array[DIM], i, scelta;

    // Genero elementi dell'array (random da 1 a 100)
    srand(time(NULL));
    for (i = 0; i < DIM; i++)
    {
        array[i] = rand() % 100;
    }

    /* Stampo array
    for (i = 0; i < 5; i++)
    {
        printf("%d ",array[i]);
    }*/

    do
    {
        printf("1. Visualizza elementi dell'array\n");
        printf("2. Visualizza array invertito\n");
        printf("3. Visualizza la somma e la media degli elementi\n");
        printf("4. Visualizza tutti i numeri pari\n");
        printf("5. Visualizza tutti i numeri dispari\n");
        printf("6. Ricerca un numero (da input)\n");
        printf("7. Elimina un numero (da input)\n");
        printf("8. Scambia le posizioni a due a due\n");
        printf("9. Ordina l'array (in ordine a scelta)\n");
        printf("10. Esci\n");
        printf("Inserisci la scelta: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
        case 1:
            printf("Visualizza elementi dell'array\n");
            for (i = 0; i < DIM; i++)
            {
                printf("%d ", array[i]);
            }
            break;
        case 2:
            printf("Visualizza array invertito\n");
            for (i = DIM - 1; i >= 0; i--)
            {
                printf("%d ", array[i]);
            }
            break;
        case 3:
            printf("Visualizza la somma e la media degli elementi\n");
            int somma = 0;
            for (i = 0; i < DIM; i++)
            {
                somma += array[i];
            }
            printf("Somma: %d, Media: %.2f", somma, somma / 5.0);
            break;
        case 4:
            printf("Visualizza tutti i numeri pari\n");
            for (i = 0; i < DIM; i++)
            {
                if (array[i] % 2 == 0)
                {
                    printf("%d ", array[i]);
                }
            }
            break;
        case 5:
            printf("Visualizza tutti i numeri dispari\n");
            for (i = 0; i < DIM; i++)
            {
                if (array[i] % 2 != 0)
                {
                    printf("%d ", array[i]);
                }
            }
            break;
        case 6:
            printf("Ricerca un numero (da input)\n");
            int num, trovato = 0;
            printf("Inserisci il numero da cercare: ");
            scanf("%d", &num);
            for (i = 0; i < DIM; i++)
            {
                if (num == array[i])
                {
                    trovato = 1;
                    printf("Numero trovato!");
                }
            }
            if (!trovato)
            {
                printf("Numero NON trovato!");
            }
            break;
        case 7:
            printf("Elimina un numero (da input)\n");
            int num_el, trovato_ = 0;
            printf("Inserisci il numero da eliminare: ");
            scanf("%d", &num_el);
            for (i = 0; i < DIM; i++)
            {
                if (num_el == array[i])
                {
                    trovato_ = 1;
                    array[i] = -1; // Numero eliminato
                    printf("Numero eliminato! (Segnato con -1)");
                    break;
                }
            }
            if(!trovato_)
            {
                printf("Numero NON trovato!");
            }
            break;
        case 8:
            printf("Scambia le posizioni a due a due\n");
            int temp;
            for (i = 0; i < DIM - 1; i += 2)
            {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
            break;
        case 9:
            printf("Ordina l'array (in ordine a scelta)\n");
            int ordine, j;
            printf("1. Ordine crescente\n");
            printf("2. Ordine decrescente\n");
            printf("Inserisci la scelta: ");
            scanf("%d", &ordine);
            if (ordine == 1) // CRESCENTE
            {
                for (i = 0; i < DIM - 1; i++)
                {
                    for (j = i + 1; j < DIM; j++)
                    {
                        if (array[i] > array[j])
                        {
                            temp = array[i];
                            array[i] = array[j];
                            array[j] = temp;
                        }
                    }
                }
            }
            else if (ordine == 2) // DECRESCENTE
            {
                for (i = 0; i < DIM - 1; i++)
                {
                    for (j = i + 1; j < DIM; j++)
                    {
                        if (array[i] < array[j])
                        {
                            temp = array[i];
                            array[i] = array[j];
                            array[j] = temp;
                        }
                    }
                }
            }
            else
            {
                printf("Scelta non valida!\n");
            }

            break;
        case 10:
            printf("Uscita dal programma\n");
            break;
        default:
            printf("Scelta non valida\n");
        }

        printf("\n\n\n");
    } while (scelta != 10 && scelta > 0 && scelta < 11);

    return 0;
}