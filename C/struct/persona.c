#include <stdio.h>
#include <string.h> // per strcmp

#define DIM 50
#define MAX_PERSONE 5

typedef struct
{
    char nome[DIM];
    char cognome[DIM];
    int eta;
    char codice_fiscale[DIM];
    int reddito_annuo;
    int anno_nascita;
    char residenza[DIM];
} Persona;

void stampa_persona(Persona p) // funzione to_string
{
    printf("Nome: %s, Cognome: %s, Eta': %d, Codice fiscale: %s, Reddito annuo: %d, Anno di nascita: %d, Residenza: %s\n",
           p.nome, p.cognome, p.eta, p.codice_fiscale, p.reddito_annuo, p.anno_nascita, p.residenza);
}

void inserisci_persone(Persona persone[], int n_persone)
{
    for (int i = 0; i < n_persone; i++)
    {
        printf("\nInserimento dati persona %d\n", i + 1);
        printf("Nome: ");
        scanf("%s", persone[i].nome);
        printf("Cognome: ");
        scanf("%s", persone[i].cognome);
        printf("Eta': ");
        scanf("%d", &persone[i].eta);
        printf("Codice fiscale: ");
        scanf("%s", persone[i].codice_fiscale);
        printf("Reddito annuo: ");
        scanf("%d", &persone[i].reddito_annuo);
        printf("Anno di nascita: ");
        scanf("%d", &persone[i].anno_nascita);
        printf("Residenza(citta'): ");
        scanf("%s", persone[i].residenza);
    }
}

void trova_reddito_estremi(Persona persone[], int n_persone, Persona **max, Persona **min)
{
    // iniziallizzazione dei puntatori al primo elemento
    *max = &persone[0];
    *min = &persone[0];
    for (int i = 0; i < n_persone; i++)
    {
        if (persone[i].reddito_annuo > (*max)->reddito_annuo)
            *max = &persone[i];
        if (persone[i].reddito_annuo < (*min)->reddito_annuo)
            *min = &persone[i];
    }
}

void ordina_per_anno_nascita(Persona persone[], int n_persone)
{
    for (int i = 0; i < n_persone - 1; i++) // bubble sort
    {
        for (int j = 0; j < n_persone - i - 1; j++)
        {
            if (persone[j].anno_nascita > persone[j + 1].anno_nascita)
            {
                Persona temp = persone[j];
                persone[j] = persone[j + 1];
                persone[j + 1] = temp;
            }
        }
    }
}

void cerca_per_codice_fiscale(Persona persone[], int n_persone, char codice[])
{
    for (int i = 0; i < n_persone; i++)
    {
        if (strcmp(persone[i].codice_fiscale, codice) == 0)
            stampa_persona(persone[i]);
    }
}

void filtra_per_reddito(Persona persone[], int n_persone, int reddito)
{
    for (int i = 0; i < n_persone; i++)
    {
        if (persone[i].reddito_annuo >= reddito)
            stampa_persona(persone[i]);
    }
}

double calcola_media_redditi(Persona persone[], int n_persone)
{
    int somma = 0;
    for (int i = 0; i < n_persone; i++)
    {
        somma += persone[i].reddito_annuo;
    }
    return (double)somma / n_persone;
}

void visualizza_per_anno(Persona persone[], int n_persone, int anno)
{
    for (int i = 0; i < n_persone; i++)
    {
        if (persone[i].anno_nascita == anno)
            stampa_persona(persone[i]);
    }
}

int main()
{
    // Dichiarazione delle variabili
    Persona persone[MAX_PERSONE];
    int n_persone, scelta;
    // Inserimento dati
    do
    {
        printf("Quante persone vuoi inserire(da 1 a 5): ");
        scanf("%d", &n_persone);
        inserisci_persone(persone, n_persone);
    } while (n_persone < 1 || n_persone > MAX_PERSONE);
    // Menu
    do
    {
        do
        {
            printf("\n=== MENU ===\n");
            printf("1. Visualizza persone con redditi estremi\n");
            printf("2. Ordina lista per anno di nascita (anziano-giovane)\n");
            printf("3. Ricerca per codice fiscale\n");
            printf("4. Visualizza persone con reddito >= a reddito scelto\n");
            printf("5. Calcola la media dei redditi\n");
            printf("6. Visualizza persone per anno di nascita\n");
            printf("0. Esci\n");
            printf("Inserisci scelta: ");
            scanf("%d", &scelta);
        } while (scelta < 0 || scelta > 6);
        switch (scelta)
        {
        case 1:
            Persona *max_reddito, *min_reddito;
            trova_reddito_estremi(persone, n_persone, &max_reddito, &min_reddito);
            printf("Reddito piu' alto\n");
            stampa_persona(*max_reddito);
            printf("Reddito piu' basso\n");
            stampa_persona(*min_reddito);
            break;
        case 2:
            ordina_per_anno_nascita(persone, n_persone);
            printf("\nLista ordinata per anno di nascita:\n");
            for (int i = 0; i < n_persone; i++)
            {
                stampa_persona(persone[i]);
            }
            break;
        case 3:
            char codice_ricerca[DIM];
            printf("Inserisci il codice da cercare: ");
            scanf("%s", codice_ricerca);
            cerca_per_codice_fiscale(persone, n_persone, codice_ricerca);
            break;
        case 4:
            int reddito_scelto;
            printf("Inserisci il reddito: ");
            scanf("%d", &reddito_scelto);
            filtra_per_reddito(persone, n_persone, reddito_scelto);
            break;
        case 5:
            double media = calcola_media_redditi(persone, n_persone);
            printf("Media redditi: %.2f\n", media);
            break;
        case 6:
            int anno_ricerca;
            printf("Inserisci l'anno da cercare: ");
            scanf("%d", &anno_ricerca);
            visualizza_per_anno(persone, n_persone, anno_ricerca);
            break;
        case 0:
            printf("Uscita dal programma\n");
            scelta = 0;
        default:
            break;
        }
    } while (scelta != 0);
    return 0;
}