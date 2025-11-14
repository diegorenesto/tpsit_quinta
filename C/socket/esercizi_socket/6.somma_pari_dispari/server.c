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

int somma_pari(int arr[])
{
    int somma = 0;
    for (int i = 0; i < DIM; i++)
    {
        if (arr[i] % 2 == 0)
        {
            somma += arr[i];
        }
    }
    return somma;
}

int somma_dispari(int arr[])
{
    int somma = 0;
    for (int i = 0; i < DIM; i++)
    {
        if (arr[i] % 2 != 0)
        {
            somma += arr[i];
        }
    }
    return somma;
}

int main()
{
    // dichiarazione variabili
    int server_socket, client_socket, fromlen;
    struct sockaddr_in server_addr;
    int arr[DIM];

    // creazione socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Errore creazione socket\n");
    }

    // configurazione indirizzo server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    fromlen = sizeof(server_addr);

    bind(server_socket, (struct sockaddr *)&server_addr, fromlen); // associazione indirizzo e porta alla socket
    listen(server_socket, 5);

    for (;;)
    {
        printf("[SERVER] In ascolto sulla porta 8080\n");
        client_socket = accept(server_socket, (struct sockaddr *)&server_addr, &fromlen);
        if (client_socket == -1)
        {
            perror("Errore accept\n");
        }

        recv(client_socket, (char*)arr, sizeof(arr), 0);
        
        int pari = somma_pari(arr);
        int dispari = somma_dispari(arr);
        printf("Somma pari: %d\n", pari);
        printf("Somma dispari: %d\n\n", dispari);
        
        // invio dei risultati al client
        write(client_socket, (char*)&pari, sizeof(pari));
        write(client_socket, (char*)&dispari, sizeof(dispari));

        close(client_socket);
    }

    return 0;
}