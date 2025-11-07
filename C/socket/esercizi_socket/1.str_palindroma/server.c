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

int palindroma(char str[])
{
    int i, j;
    j = strlen(str);

    for (i = 0; i < j - 1; i++, j--)
    {
        if (str[i] != str[j])
            return -1;
    }
    return 0;
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, soa, fromlen;
    char str[DIM];

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
        printf("Stringa ricevuta: %s\n", str);

        if (palindroma(str) == 0)
            printf("La stringa e' palindroma\n");
        else
            printf("La stringa non e' palindroma\n");

        close(soa);
    }

    return 0;
}