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
 * @brief Funzione conta maiuscole di una stringa
 * @param str Stringa
 * @return Numero di maiuscole (cont)
 */
int conta_maiuscole(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isupper(str[i])) // isupper funzione definita in ctype.h, controlla che il carattere sia in uppercase
            cont++;
    }
    return cont;
}

/**
 * @brief Funzione caratteri speciali di una stinga
 * @param str Stringa
 */
void stringa_speciale(char str[])
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isgraph(str[i]) && !isalnum(str[i]))
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

/**
 * @brief Funzione principale del programma
 * @return 0 Se ha successo
 */
int main()
{
    // Dichiarazione variabili
    struct sockaddr_in server_addr;
    int server_socket, client_socket, fromlen, bind_status, codice;
    char str[DIM];

    // creazione socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // IPv4, tipo di socket, 0 prende un protocollo random
    if (server_socket == -1)
    {
        perror("Errore creazione socket\n");
        exit(-1);
    }

    // indirizzo server
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_port = htons(SERVERPORT); // assegno la porta
    server_addr.sin_addr.s_addr = INADDR_ANY;

    fromlen = sizeof(server_addr);

    // bind (assegnazione di un IP alla porta dedicata alla socket)
    bind_status = bind(server_socket, (struct sockaddr *)&server_addr, fromlen);
    listen(server_socket, 5);

    for (;;)
    {
        printf("[SERVER] In ascolto sulla porta 8080\n");
        // accetto la richiesta di connessione del client
        client_socket = accept(server_socket, (struct sockaddr *)&server_addr, &fromlen);
        if (client_socket == -1)
        {
            perror("Errore accept\n");
            exit(-1);
        }
        // leggo il file descriptor lato client
        read(client_socket, str, sizeof(str));
        printf("Stringa ricevuta: %s\n", str);
        // leggo il codice
        read(client_socket, &codice, sizeof(codice));
        printf("Codice ricevuto: %d\n", codice);

        switch (codice)
        {
        case 0:
            // numero di maiuscole
            int n_maiuscole = conta_maiuscole(str);
            write(client_socket, &n_maiuscole, sizeof(n_maiuscole));
            break;

        case 1:
            // stringa con caratteri speciali
            stringa_speciale(str);
            write(client_socket, str, sizeof(str));
            break;

        default:
            break;
        }

        close(client_socket);
    }

    return 0;
}