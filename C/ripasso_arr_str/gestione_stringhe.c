#include <stdio.h>
#include <string.h>

#define MAX 100
#define DIM_LETTERE_COMUNI 100

int main(int argc, char *argv[])
{
    // Dichiarazione delle variabili
    char stringa[MAX], stringa2[MAX];
    int scelta, i;

    printf("Inserisci una stringa (max 100 caratteri): ");
    fgets(stringa, MAX, stdin);

    do
    {
        printf("1. Controlla che contenga solo lettere\n");
        printf("2. Conta l'occorrenza di una lettera nella stringa\n");
        printf("3. Crea due ulteriori stringhe che contengano 1 le lettere di posizione pari e 2 le lettere di posizione dispari\n");
        printf("4. Verifica se la stringa contiene doppie\n");
        printf("5. Esci\n");
        printf("Inserisci la scelta: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
        case 1:

            printf("Controlla che contenga solo lettere\n"); // gli spazi sono considerati caratteri validi
            {
                int solo_lettere = 1;
                for (i = 0; stringa[i] != '\0' && stringa[i] != '\n'; i++)
                {
                    if (!((stringa[i] >= 'A' && stringa[i] <= 'Z') || (stringa[i] >= 'a' && stringa[i] <= 'z') || stringa[i] == ' '))
                    {
                        solo_lettere = 0;
                        break;
                    }
                }
                if (solo_lettere)
                    printf("La stringa contiene solo lettere e spazi\n");
                else
                    printf("La stringa contiene caratteri NON alfabetici\n");
            }
            break;

        case 2:
            printf("Conta l'occorrenza di una lettera nella stringa\n");
            char lettera;
            int cont = 0;
            printf("Inserisci la lettera da cercare: ");
            scanf(" %c", &lettera);
            for (i = 0; stringa[i] != '\0' && stringa[i] != '\n'; i++)
            {
                if (stringa[i] == lettera)
                    cont++;
            }
            if (cont > 0)
                printf("La lettera '%c' compare %d volte nella stringa\n", lettera, cont);
            else
                printf("La lettera '%c' non compare nella stringa\n", lettera);
            break;

        case 3:
            printf("Crea due ulteriori stringhe che contengano 1 le lettere di posizione pari e 2 le lettere di posizione dispari\n");
            char pari[MAX], dispari[MAX];
            int j = 0, k = 0;
            for (i = 0; stringa[i] != '\0' && stringa[i] != '\n'; i++)
            {
                if (i % 2 == 0)
                {
                    pari[j++] = stringa[i];
                }
                else
                {
                    dispari[k++] = stringa[i];
                }
            }
            pari[j] = '\0';
            dispari[k] = '\0';
            printf("Stringa con lettere in posizione pari: %s\n", pari);
            printf("Stringa con lettere in posizione dispari: %s\n", dispari);
            break;

        case 4:
            printf("Verifica se la stringa contiene doppie\n");
            {
                int doppie = 0;
                for (i = 0; stringa[i] != '\0' && stringa[i] != '\n'; i++)
                {
                    if (stringa[i] == stringa[i + 1])
                    {
                        doppie = 1;
                        break;
                    }
                }
                if (doppie)
                    printf("La stringa contiene doppie\n");
                else
                    printf("La stringa NON contiene doppie\n");
            }
            break;

        case 5:
            printf("Uscita dal programma\n");
            break;

        default:
            break;
        }

        printf("\n");
    } while (scelta != 5 && scelta > 0 && scelta < 6);

    printf("----- SECONDA STRINGA -----\n");

    printf("Inserisci una seconda stringa (max 100 caratteri): ");
    scanf(" "); // pulizia del buffer
    fgets(stringa2, MAX, stdin);

    do
    {
        printf("1. Quale delle due stringhe e' piu' lunga\n");
        printf("2. Quali sono le lettere contenute in ambedue le stringhe\n");
        printf("3. Quale delle due stringhe contiene piu' vocali\n");
        printf("4. Quale delle due stringhe contiene piu' consonanti\n");
        printf("5. Esci\n");

        printf("Inserisci la scelta: ");
        scanf("%d", &scelta);

        switch (scelta)
        {
        case 1:
            printf("Quale delle due stringhe e' piu' lunga\n");
            {
                int len1 = strlen(stringa);
                int len2 = strlen(stringa2);
                if (len1 > len2)
                    printf("La prima stringa e' piu' lunga (%d caratteri contro %d)\n", len1, len2);
                else if (len2 > len1)
                    printf("La seconda stringa e' piu' lunga (%d caratteri contro %d)\n", len2, len1);
                else
                    printf("Le due stringhe sono della stessa lunghezza (%d caratteri)\n", len1);
            }
            break;

        case 2:
            printf("Quali sono le lettere contenute in ambedue le stringhe\n");
            int lettere_comuni[DIM_LETTERE_COMUNI];
            int cont_comuni = 0;
            for (i = 0; stringa[i] != '\0' && stringa[i] != '\n'; i++)
            {
                for (int j = 0; stringa2[j] != '\0' && stringa2[j] != '\n'; j++)
                {
                    if (stringa[i] == stringa2[j])
                    {
                        lettere_comuni[cont_comuni++] = stringa[i];
                        stringa2[j] = ' '; // non conta la stessa lettera piu' volte
                        break;
                    }
                }
            }
            printf("Lettere comuni: ");
            for (i = 0; i < cont_comuni; i++)
            {
                printf("%c ", lettere_comuni[i]);
            }
            break;

        case 3:
            printf("Quale delle due stringhe contiene piu' vocali\n");
            int cont_vocali1 = 0, cont_vocali2 = 0;
            for (i = 0; stringa[i] != '\0' && stringa[i] != '\n'; i++)
            {
                if (stringa[i] == 'a' || stringa[i] == 'e' || stringa[i] == 'i' || stringa[i] == 'o' || stringa[i] == 'u' ||
                    stringa[i] == 'A' || stringa[i] == 'E' || stringa[i] == 'I' || stringa[i] == 'O' || stringa[i] == 'U')
                {
                    cont_vocali1++;
                }
            }
            for (i = 0; stringa2[i] != '\0' && stringa2[i] != '\n'; i++)
            {
                if (stringa2[i] == 'a' || stringa2[i] == 'e' || stringa2[i] == 'i' || stringa2[i] == 'o' || stringa2[i] == 'u' ||
                    stringa2[i] == 'A' || stringa2[i] == 'E' || stringa2[i] == 'I' || stringa2[i] == 'O' || stringa2[i] == 'U')
                {
                    cont_vocali2++;
                }
            }
            if (cont_vocali1 > cont_vocali2)
            {
                printf("La prima stringa contiene piu' vocali (%d contro %d)\n", cont_vocali1, cont_vocali2);
            }
            else if (cont_vocali2 > cont_vocali1)
            {
                printf("La seconda stringa contiene piu' vocali (%d contro %d)\n", cont_vocali2, cont_vocali1);
            }
            else
            {
                printf("Entrambe le stringhe contengono lo stesso numero di vocali (%d)\n", cont_vocali1);
            }
            break;

        case 4:
            printf("Quale delle due stringhe contiene piu' consonanti\n");
            int cont_consonanti1 = 0, cont_consonanti2 = 0;
            for (i = 0; stringa[i] != '\0' && stringa[i] != '\n'; i++)
            {
                if (stringa[i] != 'a' && stringa[i] != 'e' && stringa[i] != 'i' && stringa[i] != 'o' && stringa[i] != 'u' &&
                    stringa[i] != 'A' && stringa[i] != 'E' && stringa[i] != 'I' && stringa[i] != 'O' && stringa[i] != 'U')
                {
                    cont_consonanti1++;
                }
            }
            for (i = 0; stringa2[i] != '\0' && stringa2[i] != '\n'; i++)
            {
                if (stringa2[i] != 'a' && stringa2[i] != 'e' && stringa2[i] != 'i' && stringa2[i] != 'o' && stringa2[i] != 'u' &&
                    stringa2[i] != 'A' && stringa2[i] != 'E' && stringa2[i] != 'I' && stringa2[i] != 'O' && stringa2[i] != 'U')
                {
                    cont_consonanti2++;
                }
            }
            if (cont_consonanti1 > cont_consonanti2)
            {
                printf("La prima stringa contiene piu' vocali (%d contro %d)\n", cont_consonanti1, cont_consonanti2);
            }
            else if (cont_consonanti2 > cont_consonanti1)
            {
                printf("La seconda stringa contiene piu' vocali (%d contro %d)\n", cont_consonanti2, cont_consonanti1);
            }
            else
            {
                printf("Entrambe le stringhe contengono lo stesso numero di vocali (%d)\n", cont_consonanti1);
            }
            break;

        case 5:
            printf("Uscita dal programma\n");
            break;

        default:
            break;
        }

        printf("\n");
    } while (scelta != 5 && scelta > 0 && scelta < 6);

    return 0;
}