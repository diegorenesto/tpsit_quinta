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
    char str[DIM];

    servizio.sin_family = AF_INET;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    printf("Inserisci la stringa: ");
    scanf("%s", str);

    write(socketfd, str, sizeof(str));

    read(socketfd, str, sizeof(str));
    printf("Stringa ordinata alfabeticamente: %s\n", str);
    close(socketfd);

    return 0;
}