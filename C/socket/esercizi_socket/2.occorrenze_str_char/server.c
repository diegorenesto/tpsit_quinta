#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define SERVERPORT 1313
#define DIM 50

int conta_occorrenze(char *str, char c)
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
        {
            cont++;
        }
    }
    return cont;
}

int main()
{
    struct sockaddr_in servizio;
    int socketfd, soa, fromlen;
    char str[DIM], carattere;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    fromlen = sizeof(servizio);
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(socketfd, (struct sockaddr *)&servizio, fromlen);
    listen(socketfd, 10);

    for (;;)
    {
        printf("\nServer in ascolto\n");
        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&servizio, &fromlen);

        read(soa, str, sizeof(str));
        read(soa, &carattere, sizeof(carattere));
        printf("Stringa ricevuta: %s\n", str);
        printf("Carattere ricevuto: %c\n", carattere);

        int occorrenze = conta_occorrenze(str, carattere);
        // restituisce il numero di occorrenze al client
        write(soa, &occorrenze, sizeof(occorrenze));

        close(soa);
    }

    return 0;
}