/**
 * @author Diego Renesto
 * @file funzioni.c
 * @brief File contenente le funzioni per non scrivere ogni volta tutto quanto, con alcuni omonimi per la ricerca
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define DIM 50

/* ============================================================
 *                 CONTA PAROLE
 * ============================================================ */
int conta_parole(char str[])
{
    int cont = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
            cont++;
    }
    return cont;
}

/* ============================================================
 *                 TOUPPER, MAIUSCOLO
 * ============================================================ */
void maiuscolo(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toupper(str[i]);
    }
}

/* ============================================================
 *                 TOLOWER, MINUSCOLO
 * ============================================================ */
void minuscolo(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

/* ============================================================
 *                 CONTA LETTERE, CONTA CARATTERI
 * ============================================================ */
int conta_lettere(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]))
            cont++;
    }
    return cont;
}

/* ============================================================
 *                 CONTA CIFRE, CONTA NUMERI
 * ============================================================ */
int conta_cifre(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isdigit(str[i]))
            cont++;
    }
    return cont;
}

/* ============================================================
 *                 CONTA SPAZI, SPAZIO
 * ============================================================ */
int conta_spazi(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
            cont++;
    }
    return cont;
}

/* ============================================================
 *                 CONTA SPECIALI, CARATTERI SPECIALI
 * ============================================================ */
int conta_speciali(char str[])
{
    int cont = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (isgraph(str[i]) && !isalnum(str[i]))
            cont++;
    }
    return cont;
}

/* ============================================================
 *                 RIMUOVI DUPLICATI, DOPPIE
 * ============================================================ */
void rimuovi_duplicati(char str[])
{
    int j = 1;
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (str[i] != str[i - 1])
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

/* ============================================================
 *                 INVERTI STR, STRREV
 * ============================================================ */
void inverti_stringa(char str[])
{
    int j = strlen(str);
    for (int i = 0; i < j / 2; i++)
    {
        char temp = str[i];
        str[i] = str[j - i - 1];
        str[j - i - 1] = temp;
    }
}

/* ============================================================
 *                 CONTA VOCALI
 * ============================================================ */
int conta_vocali(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
            str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
            cont++;
    }
    return cont;
}

/* ============================================================
 *                 STRINGA ALFABETICA
 * ============================================================ */
void str_alfabetica(char str[])
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]))
        {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';
}

/* ============================================================
 *                 RIMUOVI VOCALI
 * ============================================================ */
char rimuovi_vocali(char str[])
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
              str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U'))
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

/* ============================================================
 *                 STRINGA PALINDROMA
 * ============================================================ */
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

/* ============================================================
 *                 CONTA OCCORRENZE
 * ============================================================ */
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

/* ============================================================
 *                 ORDINA ALFABETICAMENTE
 * ============================================================ */
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

/* ============================================================
 *                 LETTERE PARI, POS PARI
 * ============================================================ */
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

/* ============================================================
 *                 LETTERE DISPARI, POS DISPARI
 * ============================================================ */
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

/* ============================================================
 *                 CONFRONTA LUNGHEZZE, DIM
 * ============================================================ */
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

/* ============================================================
 *                 SOMMA PARI
 * ============================================================ */
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

/* ============================================================
 *                 SOMMA DISPARI
 * ============================================================ */
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

/* ============================================================
 *                 CONTA MAIUSCOLE
 * ============================================================ */
int conta_maiuscole(char str[])
{
    int cont = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isupper(str[i])) // isupper funzione definita in ctype.h, controlla che il carattere sia in uppercase
            cont++;
    }
    return cont;
}

/* ============================================================
 *                 STRINGA SPECIALE, CARATTERI SPECIALI
 * ============================================================ */
void stringa_speciale(char str[])
{
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isgraph(str[i]) && !isalnum(str[i]))
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}