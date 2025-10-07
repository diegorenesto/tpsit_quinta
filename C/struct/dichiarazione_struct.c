#include <stdio.h>
#include <string.h>

/* METODO 1
struct Persona
{
    char nome[50];
    char cognome[50];
    int eta;
    float altezza;
};

int main()
{

    // Dichiarazione delle variabili
    struct Persona persona1;

    return 0;
} */

// METODO 2
typedef struct
{
    char nome[50];
    char cognome[50];
    int eta;
    float altezza;
} Persona;

void stampa_dettagli_persona(Persona p)
{
    // passaggio per valore, NON per indirizzo (non c'è *) => si passa per indirizzo al cambiamento di qualche valore
    printf("Nome: %s\n", p.nome); // accesso al campo tramite l'operatore 'punto' (.)
    printf("Cognome: %s\n", p.cognome);
    printf("Eta': %d\n", p.eta);
    printf("Altezza: %.2f\n", p.altezza);
}

// passaggio per indirizzo
void aggiorna_eta(Persona *p, int nuova_eta)
{
    (*p).eta = nuova_eta;
}

int main()
{
    Persona persona1 = {"Diego", "Renesto", 18, 1.85};
    stampa_dettagli_persona(persona1);

    // passaggio per indirizzo, modifica valore
    printf("Eta' prima: %d\n", persona1.eta);
    aggiorna_eta(&persona1, 19);
    printf("Eta' dopo: %d\n", persona1.eta);

    // Array di struct
    Persona persone[10];

    return 0;
}