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
#define DIM 50

int main()
{
    struct sockaddr_in servizio;
    int socketfd;
    char str[DIM], pari[DIM], dispari[DIM];
    int len_pari, len_dispari;

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    printf("Inserisci la stringa: ");
    scanf("%s", str);
    write(socketfd, str, sizeof(str));

    // invio prima la lunghezza (altrimenti non saprebbe quale dato leggere e stampare)
    read(socketfd, &len_pari, sizeof(int));
    read(socketfd, pari, len_pari);
    read(socketfd, &len_dispari, sizeof(int));
    read(socketfd, dispari, len_dispari);

    printf("Stringa indici pari: %s\n", pari);
    printf("Stringa indici dispari: %s\n", dispari);

    close(socketfd);
    return 0;
}