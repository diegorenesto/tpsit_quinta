"""
Scrivi un programma che chieda all’utente di inserire una lista di numeri interi.
Usa funzioni e cicli per:
● calcolare la media dei numeri
● contare quanti numeri sono sopra la media e quanti sotto
● creare una nuova lista contenente solo i numeri maggiori della media
● determinare la lunghezza della sequenza più lunga di numeri consecutivi uguali
"""

numeri = []
numeri_sopra = []
numeri_sotto = []


def calcola_media(numeri: []) -> int:  # type: ignore
    somma = 0
    for i in range(len(numeri)):
        somma += numeri[i]
    media = somma / len(numeri)
    return media


def conta_sopra_sotto(numeri: [], media: float) -> None:  # type: ignore
    for num in numeri:
        if num > media:
            numeri_sopra.append(num)
        elif num < media:
            numeri_sotto.append(num)
        else:
            print("Il numero inserito è corrispondente alla media")


def lunghezza_sequenza(numeri: []) -> int:  # type: ignore
    sequenza_corrente = 1
    max_sequenza = 1
    for i in range(len(numeri)):
        if numeri[i] == numeri[i + 1]:
            sequenza_corrente += 1
            if sequenza_corrente > max_sequenza:
                max_sequenza = sequenza_corrente
        else:
            sequenza_corrente = 1
        return max_sequenza


num_numeri = int(input("Quanti numeri vuoi inserire: "))
for i in range(num_numeri):
    numero = int(input(f"Inserisci il numero {i+1}: "))
    numeri.append(numero)

if numeri:
    media = calcola_media(numeri)
    print(f"\nLa media è: {media}")

    conta_sopra_sotto(numeri, media)
    print(f"Numeri sopra la media: {len(numeri_sopra)}")
    print(f"Numeri sotto la media: {len(numeri_sotto)}")

    max_seq = lunghezza_sequenza(numeri)
    print(f"Lunghezza della sequenza più lunga di numeri consecutivi uguali: {max_seq}")
else:
    print("Nessun numero inserito")
