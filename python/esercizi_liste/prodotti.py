"""
Scrivi un programma che gestisca un magazzino di prodotti.
Ogni prodotto è descritto da: nome, prezzo e quantità disponibile.
Il programma deve:
● salvare i prodotti in una lista di dizionari (o liste)
● usare una funzione per calcolare il valore totale del magazzino
● usare un ciclo per trovare il prodotto con il valore totale più alto (prezzo x quantità)
● creare una lista dei prodotti esauriti (quantità = 0)

● stampare un riepilogo finale
"""


def calcola_valore_totale(magazzino: []) -> float:  # type: ignore
    valore_totale = 0
    for prodotto in magazzino:
        valore_totale += prodotto["prezzo"] * prodotto["quantita"]
    return valore_totale


magazzino = []

num_prodotti = int(input("Inserisci il numero di prodotti: "))
for i in range(num_prodotti):
    nome = input("Nome prodotto: ")
    prezzo = float(input("Prezzo: "))
    quantita = int(input("Quantità disponibile: "))
    prodotto = {"nome": nome, "prezzo": prezzo, "quantita": quantita}
    magazzino.append(prodotto)

valore_magazzino = calcola_valore_totale(magazzino)
print(f"\nValore totale magazzino: €{valore_magazzino:.2f}")

prodotto_valore_max = magazzino[0]
for prodotto in magazzino:
    valore_prodotto = prodotto["prezzo"] * prodotto["quantita"]
    valore_max = prodotto_valore_max["prezzo"] * prodotto_valore_max["quantita"]
    if valore_prodotto > valore_max:
        prodotto_valore_max = prodotto

print(f"Prodotto con valore totale più alto: {prodotto_valore_max['nome']}")
print(f"Valore: €{prodotto_valore_max['prezzo'] * prodotto_valore_max['quantita']:.2f}")

esauriti = []
for prodotto in magazzino:
    if prodotto["quantita"] == 0:
        esauriti.append(prodotto["nome"])


# riepilogo
print("\n=== RIEPILOGO MAGAZZINO ===")
for prodotto in magazzino:
    valore = prodotto["prezzo"] * prodotto["quantita"]
    print(
        f"Nome: {prodotto['nome']}, Prezzo: €{prodotto['prezzo']:.2f}, "
        f"Quantità: {prodotto['quantita']}, Valore totale: €{valore:.2f}"
    )

print(f"\nProdotti esauriti: {esauriti if esauriti else 'Nessuno'}")
