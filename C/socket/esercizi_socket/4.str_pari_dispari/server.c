#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>

#define SERVERPORT 1313
#define DIM 20

void lettere_pari(char *str, char *pari)
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i += 2)
    {
        pari[j] = str[i];
        j++;
    }
    pari[j] = '\0';
}

void lettere_dispari(char *str, char *dispari)
{
    int j = 0;
    for (int i = 1; str[i] != '\0'; i += 2)
    {
        dispari[j] = str[i];
        j++;
    }
    dispari[j] = '\0';
}

int main()
{
    struct sockaddr_in servizio;
    int socketfd, fromlen, soa;
    char str[DIM], pari[DIM], dispari[DIM];

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

        lettere_pari(str, pari);
        lettere_dispari(str, dispari);
        int len_pari = strlen(pari) + 1; // + 1 per il terminatore
        int len_dispari = strlen(dispari) + 1;

        write(soa, &len_pari, sizeof(int));
        write(soa, pari, len_pari);

        write(soa, &len_dispari, sizeof(int));
        write(soa, dispari, len_dispari);

        close(soa);
    }

    return 0;
}