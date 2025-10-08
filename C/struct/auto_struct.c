#include <stdio.h>
#include <string.h>

/* Scrivere un programma in C che dopo aver dichiarato una struttura denominata Auto con i seguenti
campi: ModelloAuto, marca, cilindrata, prezzo, anno_immatricolazione, targa; determini:
1) Il prezzo + alto e quello + basso visualizzando anche il modello dell'auto;
2) Ordinare la lista delle auto in base all'anno d'immatricolazione;
3) Visualizzare il nome delle auto a partire da un prezzo scelto dall'utente.
4) Ricerchi un Auto scelta dall’utente (utilizzare il campo targa): visualizzando tutti i campi;
5) La media dei prezzi delle auto inserite;
6) Visualizzare le Auto con anno di immatricolazione scelto dall’utente; */

#define MAX_AUTO 10 // definito per la dimensione dell'array nel main()

typedef struct
{
    char modello_auto[50];
    char marca[50];
    int cilindrata;
    int prezzo;
    int anno_immatricolazione;
    char targa[10];
} Auto;

void stampa_auto(Auto a, int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }
    printf("Modello: %s, Marca: %s, Cilindrata: %d, Prezzo: %d, Anno: %d, Targa: %s\n",
           a.modello_auto, a.marca, a.cilindrata, a.prezzo, a.anno_immatricolazione, a.targa);
}

void stampa_lista(Auto lista_auto[], int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }
    for (int i = 0; i < n_auto; i++)
    {
        stampa_auto(lista_auto[i], n_auto);
    }
}

void mostra_menu()
{
    printf("1. Inserisci auto\n");
    printf("2. Trova prezzi estremi\n");
    printf("3. Ordina per anno di immatricolazione\n");
    printf("4. Cerca auto per prezzo minimo\n");
    printf("5. Cerca auto per targa\n");
    printf("6. Calcola media prezzi\n");
    printf("7. Cerca auto per anno\n");
    printf("0. Esci\n");
    printf("Inserisci la scelta: ");
}

void inserisci_auto(Auto lista_auto[], int *n_auto)
{
    if (*n_auto >= MAX_AUTO)
    {
        printf("Numero massimo di auto gia' inserito!\n");
        return;
    }
    printf("\nINSERIMENTO DATI AUTO %d\n", *n_auto + 1);
    printf("Modello: ");
    scanf("%s", lista_auto[*n_auto].modello_auto);
    printf("Marca: ");
    scanf("%s", lista_auto[*n_auto].marca);
    printf("Cilindrata: ");
    scanf("%d", &lista_auto[*n_auto].cilindrata);
    printf("Prezzo: ");
    scanf("%d", &lista_auto[*n_auto].prezzo);
    printf("Anno immatricolazione: ");
    scanf("%d", &lista_auto[*n_auto].anno_immatricolazione);
    printf("Targa: ");
    scanf("%s", lista_auto[*n_auto].targa);
    printf("\n");

    (*n_auto)++;
    printf("Auto aggiunta alla lista\n\n");
}

void trova_prezzi_estremi(Auto lista_auto[], int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }
    int prezzo_max, prezzo_min;
    char modello_max[50], modello_min[50];

    prezzo_max = lista_auto[0].prezzo;
    prezzo_min = lista_auto[0].prezzo;
    strcpy(modello_max, lista_auto[0].modello_auto); // metto 'in storage' modello_auto su modello_max
    strcpy(modello_min, lista_auto[0].modello_auto);

    for (int i = 1; i < n_auto; i++)
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
    // output
    printf("Auto con prezzo piu' alto: %s con %d\n", modello_max, prezzo_max);
    printf("Auto con prezzo piu' basso: %s con %d\n", modello_min, prezzo_min);
    printf("\n\n");
}

void ordina_per_anno(Auto lista_auto[], int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }
    for (int i = 0; i < n_auto - 1; i++)
    {
        for (int j = i + 1; j < n_auto; j++)
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
    for (int i = 0; i < n_auto; i++)
    {
        stampa_auto(lista_auto[i], n_auto);
    }
    printf("\n\n");
}

void visualizza_per_prezzo(Auto lista_auto[], int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }
    int prezzo_scelto, trovato = 0;

    printf("Inserisci un prezzo per visualizzare le auto con prezzo maggiore o uguale: ");
    scanf("%d", &prezzo_scelto);
    printf("Auto con prezzo >= %d\n", prezzo_scelto);
    for (int i = 0; i < n_auto; i++)
    {
        if (lista_auto[i].prezzo >= prezzo_scelto)
        {
            stampa_auto(lista_auto[i], n_auto);
            trovato = 1;
        }
    }
    if (!trovato)
        printf("Nessun'auto trovata con prezzo >= %d\n", prezzo_scelto);
    printf("\n\n");
}

void cerca_per_targa(Auto lista_auto[], int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }

    char targa_ricerca[50];
    int targa_trovata = 0;

    printf("Inserisci la targa dell'auto da cercare: ");
    scanf("%s", targa_ricerca);
    for (int i = 0; i < n_auto; i++)
    {
        if (strcmp(lista_auto[i].targa, targa_ricerca) == 0)
        {
            stampa_auto(lista_auto[i], n_auto);
            targa_trovata = 1;
            break;
        }
    }
    if (!targa_trovata)
    {
        printf("Auto con targa %s non trovata\n", targa_ricerca);
    }
    printf("\n\n");
}

void calcola_media(Auto lista_auto[], int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }

    int somma_prezzi = 0;

    for (int i = 0; i < n_auto; i++)
    {
        somma_prezzi += lista_auto[i].prezzo;
    }
    printf("Media dei prezzi: %.2f", (float)somma_prezzi / n_auto);
    printf("\n\n");
}

void cerca_per_anno(Auto lista_auto[], int n_auto)
{
    if (n_auto == 0)
    {
        printf("Nessun'auto presente\n");
        return;
    }

    int anno_scelto, anno_trovato = 0;

    printf("Inserisci un anno di immatricolazione per visualizzarne le auto: ");
    scanf("%d", &anno_scelto);
    for (int i = 0; i < n_auto; i++)
    {
        if (lista_auto[i].anno_immatricolazione == anno_scelto)
        {
            stampa_auto(lista_auto[i], n_auto);
            anno_trovato = 1;
        }
    }
    if (!anno_trovato)
    {
        printf("Nessuna auto trovata con anno di immatricolazione %d", anno_scelto);
    }
    printf("\n\n");
}

int main()
{
    Auto lista_auto[MAX_AUTO];
    int n_auto = 0, scelta;

    do
    {
        mostra_menu();
        scanf("%d", &scelta);

        switch (scelta)
        {

        case 1:
            inserisci_auto(lista_auto, &n_auto);
            break;

        case 2:
            trova_prezzi_estremi(lista_auto, n_auto);
            break;

        case 3:
            ordina_per_anno(lista_auto, n_auto);
            break;

        case 4:
            visualizza_per_prezzo(lista_auto, n_auto);
            break;

        case 5:
            cerca_per_targa(lista_auto, n_auto);
            break;

        case 6:
            calcola_media(lista_auto, n_auto);
            break;

        case 7:
            cerca_per_anno(lista_auto, n_auto);
            break;

        case 0:
            printf("Uscita dal programma\n");
            break;

        default:
            printf("Scelta non valida\n");
        }
    } while (scelta != 0);

    return 0;
}