#include <stdio.h>
#include <string.h>

/*Scrivere un programma in C che dopo aver dichiarato una struttura denominata Auto con i seguenti
campi: ModelloAuto, marca, cilindrata, prezzo, anno_immatricolazione, targa; determini:
1) Il prezzo + alto e quello + basso visualizzando anche il modello dell'auto;
2) Ordinare la lista delle auto in base all'anno d'immatricolazione;
3) Visualizzare il nome delle auto a partire da un prezzo scelto dall'utente.
4) Ricerchi un Auto scelta dall’utente (utilizzare il campo targa): visualizzando tutti i campi;
5) La media dei prezzi delle auto inserite;
6) Visualizzare le Auto con anno di immatricolazione scelto dall’utente;
*/

typedef struct
{
    char modello_auto[50];
    char marca[50];
    int cilindrata;
    int prezzo;
    int anno_immatricolazione;
    char targa[10];
} Auto;

void stampa_auto(Auto a)
{
    printf("Modello: %s, Marca: %s, Cilindrata: %d, Prezzo: %d, Anno: %d, Targa: %s\n",
           a.modello_auto, a.marca, a.cilindrata, a.prezzo, a.anno_immatricolazione, a.targa);
}

int main()
{
    // Dichiarazione delle variabili
    int n_auto, i, j, prezzo_max, prezzo_min, prezzo_scelto, targa_trovata = 0, somma_prezzi = 0, anno_scelto, anno_trovato = 0;
    char modello_max[50], modello_min[50], targa_ricerca[10];

    printf("Inserisci il numero di auto: ");
    scanf("%d", &n_auto);

    Auto lista_auto[n_auto];

    for (i = 0; i < n_auto; i++)
    {
        printf("Inserisci i dati per l'auto %d\n", i + 1);
        printf("Modello: ");
        scanf("%s", &lista_auto[i].modello_auto);
        printf("Marca: ");
        scanf("%s", &lista_auto[i].marca);
        printf("Cilindrata: ");
        scanf("%d", &lista_auto[i].cilindrata);
        printf("Prezzo: ");
        scanf("%d", &lista_auto[i].prezzo);
        printf("Anno immatricolazione: ");
        scanf("%d", &lista_auto[i].anno_immatricolazione);
        printf("Targa: ");
        scanf("%s", &lista_auto[i].targa);
        printf("\n");
    }

    // 1) Il prezzo + alto e quello + basso visualizzando anche il modello dell'auto;

    prezzo_max = lista_auto[0].prezzo;
    prezzo_min = lista_auto[0].prezzo;
    strcpy(modello_max, lista_auto[0].modello_auto);
    strcpy(modello_min, lista_auto[0].modello_auto);

    for (i = 1; i < n_auto; i++)
    {
        if (lista_auto[i].prezzo > prezzo_max)
        {
            prezzo_max = lista_auto[i].prezzo;
            strcpy(modello_max, lista_auto[i].modello_auto);
        }
        if (lista_auto[i].prezzo < prezzo_min)
        {
            prezzo_min = lista_auto[i].prezzo;
            strcpy(modello_min, lista_auto[i].modello_auto);
        }
    }

    printf("Auto con prezzo piu' alto: %s con %d\n", modello_max, prezzo_max);
    printf("Auto con prezzo piu' basso: %s con %d\n", modello_min, prezzo_min);

    printf("\n\n");

    // 2) Ordinare la lista delle auto in base all'anno d'immatricolazione;

    for (i = 0; i < n_auto - 1; i++)
    {
        for (j = i + 1; j < n_auto; j++)
        {
            if (lista_auto[i].anno_immatricolazione > lista_auto[j].anno_immatricolazione)
            {
                Auto temp = lista_auto[i];
                lista_auto[i] = lista_auto[j];
                lista_auto[j] = temp;
            }
        }
    }

    printf("Auto ordinate per anno di immatricolazione:\n");
    for (i = 0; i < n_auto; i++)
    {
        stampa_auto(lista_auto[i]);
    }

    printf("\n\n");

    // 3) Visualizzare il nome delle auto a partire da un prezzo scelto dall'utente.
    printf("Inserisci un prezzo per visualizzare le auto con prezzo maggiore o uguale: ");
    scanf("%d", &prezzo_scelto);
    printf("Auto con prezzo >= %d\n", prezzo_scelto);
    for (i = 0; i < n_auto; i++)
    {
        if (lista_auto[i].prezzo >= prezzo_scelto)
            stampa_auto(lista_auto[i]);
    }

    printf("\n\n");

    // 4) Ricerchi un Auto scelta dall’utente (utilizzare il campo targa): visualizzando tutti i campi;

    printf("Inserisci la targa dell'auto da cercare: ");
    scanf("%s", targa_ricerca);
    for (i = 0; i < n_auto; i++)
    {
        if (strcmp(lista_auto[i].targa, targa_ricerca) == 0)
        {
            stampa_auto(lista_auto[i]);
            targa_trovata = 1;
            break;
        }
    }
    if (!targa_trovata)
    {
        printf("Auto con targa %s non trovata\n", targa_ricerca);
    }

    printf("\n\n");

    // 5) La media dei prezzi delle auto inserite;

    for (i = 0; i < n_auto; i++)
    {
        somma_prezzi += lista_auto[i].prezzo;
    }
    printf("Media dei prezzi: %.2f", (float)somma_prezzi / n_auto);

    printf("\n\n");

    // 6) Visualizzare le Auto con anno di immatricolazione scelto dall’utente;

    printf("Inserisci un anno di immatricolazione per visualizzarne le auto: ");
    scanf("%d", &anno_scelto);
    for (i = 0; i < n_auto; i++)
    {
        if (lista_auto[i].anno_immatricolazione == anno_scelto)
        {
            stampa_auto(lista_auto[i]);
            anno_trovato = 1;
        }
    }
    if (!anno_trovato)
    {
        printf("Nessuna auto trovata con anno di immatricolazione %d", anno_scelto);
    }

    return 0;
}