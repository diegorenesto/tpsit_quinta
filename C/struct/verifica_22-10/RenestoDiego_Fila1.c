/**
 * @author Renesto Diego 5F
 * @date 22 Ottobre 2025
 * @brief Verifica tpsit fila 1
*/
#include <stdio.h>
#include <string.h>

#define DIM 20
#define MAX_LIBRI 5

typedef struct
{
    char titolo[DIM];
    char autore[50];
    int anno_pubblicazione, pagine_tot, pagine_lette;
} Libro;

/**
 * @brief Funzione stampa di un'istanza della struct Libro.
 * @param l Istanza della struct.
*/
void stampa_libro(Libro l)
{
    printf("Titolo: %s, Autore: %s, Anno di pubblicazione: %d, Pagine totali: %d, Pagine lette: %d\n", l.titolo, l.autore, l.anno_pubblicazione, l.pagine_tot, l.pagine_lette);
}

/**
 * @brief Funzione inserimento di un libro all'interno dell'array.
 * @param libri Array di struct Libro.
 * @param n_libri Puntatore alla dimensione dinamica dell'array.
*/
void inserisci_libro(Libro libri[], int *n_libri)
{
    printf("Titolo: ");
    scanf("%s", libri[*n_libri].titolo);
    printf("Autore: ");
    scanf("%s", libri[*n_libri].autore);
    printf("Anno di pubblicazione: ");
    scanf("%d", &libri[*n_libri].anno_pubblicazione);
    printf("Pagine totali: ");
    scanf("%d", &libri[*n_libri].pagine_tot);
    printf("Pagine lette: ");
    scanf("%d", &libri[*n_libri].pagine_lette);
    
    (*n_libri)++; // aumento della dimensione (dinamica) dell'array 'libri'
}

/**
 * @brief Metodo calcola somma pagine totali.
 * @param libri Array di struct Libro.
 * @param n_libri Puntatore alla dimensione dinamica dell'array.
 * @return somma_totale Somma delle pagine totale.
*/
int calcola_somma_totale(Libro libri[], int n_libri)
{
    int somma_totale = 0;
    for(int i = 0; i < n_libri; i++)
    {
        somma_totale += libri[i].pagine_tot;
    }
    return somma_totale;
}

/**
 * @brief Metodo calcola somma pagine lette.
 * @param libri Array di struct Libro.
 * @param n_libri Puntatore alla dimensione dinamica dell'array.
 * @return somma_totale Somma delle pagine lette.
*/
int calcola_somma_lette(Libro libri[], int n_libri)
{
    int somma_lette = 0;
    for(int i = 0; i < n_libri; i++)
    {
        somma_lette += libri[i].pagine_lette;
    }
    return somma_lette;
}

/** @brief Metodo ricerca indice del libro da eliminare.
 * @param libri Array di struct Libro.
 * @param n_libri Puntatore alla dimensione dinamica dell'array.
 * @param titolo_elimina Titolo del libro da eliminare.
 * @return i Indice del libro da eliminare.
*/
int ricerca_index_elimina(Libro libri[], int n_libri, char titolo_elimina[])
{
    for(int i = 0; i < n_libri; i++)
    {
        if(strcmp(libri[i].titolo, titolo_elimina) == 0)
        {
            return i;
        }
    }
    return 0;
}

/**
 * @brief Funzione visualizza libri di un autore.
 * @param libri Array di struct Libro.
 * @param n_libri Puntatore alla dimensione dinamica dell'array.
 * @param autore Autore da ricercare nell'array.
 */
void visualizza_libri_autore(Libro libri[], int n_libri, char autore[])
{
    int trovato = 0;
    for(int i = 0; i < n_libri; i++)
    {
        if(strcmp(libri[i].autore, autore) == 0)
        {
            stampa_libro(libri[i]);
            trovato = 1;
        }
    }
    if(!trovato)
        printf("Nessun libro di '%s' trovato\n", autore);
}

/**
 * @return 0 Se ha successo
*/
int main()
{
    Libro libri[MAX_LIBRI];
    int n_libri = 0;
    int scelta;
    
    do
    {
        do
        {
            printf("\n===MENU===\n");
            printf("1. Inserisci libro\n");
            printf("2. Calcola percentuale di pagine lette\n");
            printf("3. Elimina un libro dall'array\n");
            printf("4. Visualizza i libri di un autore\n");
            printf("5. Calcola la media delle pagine\n");
            printf("0. Esci\n");
            printf("Inserisci la scelta: ");
            scanf("%d", &scelta);
        } while (scelta < 0 || scelta > 5); // controllo che la scelta sia valida
        
        switch(scelta)
        {
            case 1:
                if(n_libri < MAX_LIBRI) // controllo spazio all'interno dell'array
                {
                    inserisci_libro(libri, &n_libri);
                }
                else
                    printf("Numero massimo di libri gia' inserito\n");
                break;
                
            case 2:
                if(n_libri > 0) // controllo presenza istanze all'interno dell'array
                {
                    int somma_lette = calcola_somma_lette(libri, n_libri);
                    int somma_totale = calcola_somma_totale(libri, n_libri);
                    printf("Somma pagine lette: %d\n", somma_lette);
                    printf("Somma pagine totali: %d\n", somma_totale);
                    float rapporto = ((float)somma_lette / somma_totale) * 100;
                    printf("Rapporto: %.2f%\n", rapporto);
                }
                else
                    printf("Array vuoto\n");
                break;
                
            case 3:
                if(n_libri > 0)
                {
                    char titolo_elimina[DIM];
                    Libro libri_nuovo[MAX_LIBRI];
                    int j = 0;
                    printf("Inserisci il titolo del libro da eliminare: ");
                    scanf("%s", titolo_elimina);
                    int index = ricerca_index_elimina(libri, n_libri, titolo_elimina); // assegno a index l'indice del libro da eliminare
                    
                    for(int i = 0; i < n_libri; i++)
                    {
                        if(i == index) continue; // salto l'elemento da eliminare
                        libri_nuovo[j++] = libri[i];
                    }
                    printf("Nuovo elenco\n");
                    for(int i = 0; i < n_libri - 1; i++)
                    {
                        stampa_libro(libri_nuovo[i]);
                    }
                }
                else
                    printf("Array vuoto\n");
                break;
                
            case 4:
                if(n_libri > 0)
                {
                    char autore_ricerca[DIM];
                    printf("Inserisci l'autore del libro da cercare: ");
                    scanf("%s", autore_ricerca);
                    visualizza_libri_autore(libri, n_libri, autore_ricerca);
                }
                else
                    printf("Array vuoto\n");
                break;
                
            case 5:
                if(n_libri > 0)    
                {
                    int somma_totale = calcola_somma_totale(libri, n_libri);
                    float media = (float)somma_totale / n_libri;
                    printf("Media totale: %.2f\n", media);
                }
                else
                    printf("Array vuoto\n");
                break;
            
            case 0:
                printf("Uscita dal programma\n");
                break;
                
            default:
                break;
        }
    } while (scelta != 0);
    return 0;
}