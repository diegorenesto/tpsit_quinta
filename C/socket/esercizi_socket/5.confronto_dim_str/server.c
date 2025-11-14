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

int confronta_lunghezze(char str[], char str2[])
{
    if (strlen(str) > strlen(str2))
    {
        return 1;
    }
    else if (strlen(str) < strlen(str2))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

int main()
{
    // dichiarazione variabili
    int server_socket, client_socket, fromlen;
    struct sockaddr_in server_addr;
    char str[DIM], str2[DIM];

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
        read(client_socket, str, sizeof(str));
        printf("Stringa ricevuta: %s", str);
        read(client_socket, str2, sizeof(str2));
        printf("Stringa ricevuta: %s", str2);

        // confronto delle lunghezze delle stringhe
        int risultato = confronta_lunghezze(str, str2);
        if (risultato == 1)
        {
            printf("La prima stringa e' piu' lunga della seconda\n\n");
            write(client_socket, "La prima stringa e' piu' lunga della seconda\n", sizeof("La prima stringa e' piu' lunga della seconda\n"));
        }
        else if (risultato == 2)
        {
            printf("La seconda stringa e' piu' lunga della prima\n\n");
            write(client_socket, "La seconda stringa e' piu' lunga della prima\n", sizeof("La seconda stringa e' piu' lunga della prima\n"));
        }
        else
        {
            printf("Le due stringhe hanno la stessa lunghezza\n\n");
            write(client_socket, "Le due stringhe hanno la stessa lunghezza\n", sizeof("Le due stringhe hanno la stessa lunghezza\n"));
        }

        close(client_socket);
    }

    return 0;
}