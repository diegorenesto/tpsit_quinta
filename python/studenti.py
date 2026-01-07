"""
Scrivi un programma che gestisca i dati di una classe.
L’utente inserisce per ogni studente: nome e una lista di voti (numeri interi da 1 a 10).
Il programma deve:
● salvare i dati in una lista di liste (o lista di dizionari)
● usare una funzione per calcolare la media dei voti di ogni studente
● usare un ciclo per determinare:
○ lo studente con la media più alta
○ lo studente con la media più bassa
● creare una nuova lista con i nomi degli studenti promossi (media ≥ 6)
● stampare un riepilogo finale con nome, media e stato (promosso / bocciato)
"""


def calcola_media(voti):
    somma = 0
    for voto in voti:
        somma += voto
    media = somma / len(voti)
    return media


classe = []

num_studenti = int(input("Inserisci il numero di studenti: "))
# nome, nvoti, voti[]
for i in range(num_studenti):
    nome = input("Nome: ")
    voti = []
    num_voti = int(input("Quanti voti vuoi inserire: "))
    for j in range(num_voti):
        voto = int(input(f"Voto {j+1}(3-10): "))
        voti.append(voto)
    studente = {"nome": nome, "voti": voti}
    classe.append(studente)

# calcolo media studente
for studente in classe:
    studente["media"] = calcola_media(studente["voti"])

# studente con media migliore e peggiore
media_migliore = classe[0]
media_peggiore = classe[0]
for studente in classe:
    if studente["media"] > media_migliore["media"]:
        media_migliore = studente
    if studente["media"] < media_peggiore["media"]:
        media_peggiore = studente

# nuova lista con studenti promossi
promossi = []

for studente in classe:
    if studente["media"] >= 6:
        stato = "promosso"
        promossi.append(studente["nome"])
        studente["stato"] = "promosso"
    else:
        stato = "bocciato"
        studente["stato"] = "bocciato"
    print(f"Nome: {studente['nome']}, Media: {studente['media']:.2f}, Stato: {stato}")


print("Studente con la media più alta: ")
print(media_migliore["nome"], "-", f"{media_migliore['media']:.2f}")
print("Studente con la media più bassa: ")
print(media_peggiore["nome"], "-", f"{media_peggiore['media']:.2f}")
print("Riepilogo finale\n")
for studente in classe:
    print(studente)
