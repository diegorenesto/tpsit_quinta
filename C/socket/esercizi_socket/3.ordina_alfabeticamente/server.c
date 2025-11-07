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

void ordina_alfabeticamente(char *str)
{
    int len = strlen(str);
    int i, j;

    // bubble sort
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - i - 1; j++)
        {
            if (str[j] > str[j + 1])
            {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

int main()
{
    struct sockaddr_in servizio, addr_remoto;
    int socketfd, fromlen, soa;
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

        ordina_alfabeticamente(str);
        write(soa, str, sizeof(str)); // restituisce la stringa ordinata alfabeticamente al client

        close(soa);
    }

    return 0;
}