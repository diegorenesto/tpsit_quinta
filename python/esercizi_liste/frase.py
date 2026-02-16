"""
Scrivi un programma che chieda all’utente di inserire una frase.
Usa liste, cicli e funzioni per:
● separare la frase in una lista di parole
● contare quante volte compare ogni parola
● trovare la parola più lunga e quella più corta
● creare una lista delle parole che compaiono più di una volta
"""


def conta_parole(parole: []) -> dict:  # type: ignore
    conteggio = {}
    for parola in parole:
        if parola in conteggio:
            conteggio[parola] += 1
        else:
            conteggio[parola] = 1
    return conteggio


def trova_parola_lunga_corta(parole: []) -> tuple:  # type: ignore
    parola_piu_lunga = parole[0]
    parola_piu_corta = parole[0]
    for parola in parole:
        if len(parola) > len(parola_piu_lunga):
            parola_piu_lunga = parola
        if len(parola) < len(parola_piu_corta):
            parola_piu_corta = parola
    return parola_piu_lunga, parola_piu_corta


frase = input("Inserisci una frase: ").lower()
parole = frase.split()

if parole:
    conteggio_parole = conta_parole(parole)
    print("\n=== CONTEGGIO PAROLE ===")
    for parola, count in conteggio_parole.items():
        print(f"{parola}: {count}")

    parola_lunga, parola_corta = trova_parola_lunga_corta(parole)
    print(f"\nParola più lunga: {parola_lunga} ({len(parola_lunga)} caratteri)")
    print(f"Parola più corta: {parola_corta} ({len(parola_corta)} caratteri)")

    parole_ripetute = []
    for parola, count in conteggio_parole.items():
        if count > 1:
            parole_ripetute.append(parola)

    print(
        f"\nParole che compaiono più di una volta: {parole_ripetute if parole_ripetute else 'Nessuna'}"
    )

    # riepilogo
    print(f"\n=== RIEPILOGO ===")
    print(f"Frase: {frase}")
    print(f"Numero di parole: {len(parole)}")
    print(f"Numero di parole uniche: {len(conteggio_parole)}")
else:
    print("Nessuna parola inserita")
