/**
 * @author Diego Renesto
 * @date 10 Dicembre 2025
 * @brief Verifica Fila 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>

#define SERVERPORT 8080
#define DIM 50

/**
 * @brief Funzione principale del programma
 * @return 0 Se ha successo
 */
int main()
{
    // Dichiarazione variabili
    struct sockaddr_in server_addr;
    int network_socket, connection_status, codice;
    char str[DIM];

    // creazione socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0); // IPv4, tipo di socket, 0 prende un protocollo random
    if (network_socket == -1)
    {
        perror("Errore creazione socket\n");
        exit(-1);
    }

    // indirizzo server
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_port = htons(SERVERPORT); // assegno la porta
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // connessione al server (richiesta di connessione al server)
    connection_status = connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connection_status == -1)
    {
        perror("Errore connect\n");
        exit(-1);
    }

    // inserimento stringa
    printf("Inserisci una stringa: ");
    fgets(str, DIM, stdin);
    write(network_socket, str, sizeof(str)); // scrivo la stringa sul file descriptor della socket
    // scelta operazioni
    do
    {
        printf("===MENU===\n0. Conta numero maiuscole\n1. Stringa con caratteri speciali\n");
        printf("Inserisci il codice: ");
        scanf("%d", &codice);
    } while (codice < 0);
    write(network_socket, &codice, sizeof(codice));

    switch (codice)
    {
    case 0:
        // numero di maiuscole
        int n_maiuscole;
        read(network_socket, &n_maiuscole, sizeof(n_maiuscole));
        printf("Numero maiuscole: %d\n", n_maiuscole);
        break;

    case 1:
        // stringa con caratteri speciali
        char str_speciale[DIM];
        read(network_socket, str_speciale, sizeof(str_speciale));
        printf("Stringa caratteri speciali: %s\n", str_speciale);
        break;

    default:
        break;
    }

    // chiusura socket
    close(network_socket);

    return 0;
}