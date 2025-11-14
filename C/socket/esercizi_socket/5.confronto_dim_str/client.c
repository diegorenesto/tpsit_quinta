#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>

#define SERVERPORT 8080
#define DIM 50

int main()
{
    // dichiarazione variabili
    int network_socket;
    struct sockaddr_in server_addr;
    char str[DIM], str2[DIM];

    // creazione socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(network_socket == -1)
    {
        perror("Errore creazione socket\n");
    }

    // configurazione indirizzo server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // connessione al server
    if(connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Errore connect\n");
    }

    printf("Inserisci la prima stringa: ");
    fgets(str, DIM, stdin);
    printf("Inserisci la seconda stringa: ");
    fgets(str2, DIM, stdin);

    // invio stringhe al server
    write(network_socket, str, sizeof(str));
    write(network_socket, str2, sizeof(str2));

    // leggo la risposta del server
    char risposta[DIM];
    read(network_socket, risposta, DIM);
    printf("\nRisultato dal server: %s", risposta);

    close(network_socket);
    return 0;
}