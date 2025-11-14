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
#define DIM 10

int main()
{
    // dichiarazione variabili
    int network_socket;
    struct sockaddr_in server_addr;
    int arr[DIM];

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

    printf("Inserisci 10 numeri interi:\n");
    for(int i = 0; i < DIM; i++)
    {
        printf("Numero %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    send(network_socket, (char*)arr, sizeof(arr), 0);
    
    // leggo i risultati
    int pari, dispari;
    read(network_socket, (char*)&pari, sizeof(pari));
    read(network_socket, (char*)&dispari, sizeof(dispari));
    
    printf("\nRisultati dal server\n");
    printf("Somma pari: %d\n", pari);
    printf("Somma dispari: %d\n", dispari);

    close(network_socket);
    return 0;
}