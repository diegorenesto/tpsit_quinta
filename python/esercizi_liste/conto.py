"""
Scrivi un programma che simuli un conto bancario.
L’utente inserisce una lista di operazioni (depositi positivi e prelievi negativi).
Il programma deve:
● usare una funzione per calcolare il saldo finale
● usare un ciclo per determinare il saldo massimo e minimo raggiunto nel tempo
● contare quante operazioni sono state depositi e quante prelievi
● creare una lista dei saldi dopo ogni operazione
● stampare un riepilogo finale del conto
"""


def calcola_saldo_finale(operazioni: []) -> float:  # type: ignore
    saldo = 0
    for operazione in operazioni:
        saldo += operazione
    return saldo


operazioni = []
saldi = [0]

num_operazioni = int(input("Inserisci il numero di operazioni: "))
for i in range(num_operazioni):
    operazione = float(
        input(f"Operazione {i+1} (positiva = deposito, negativa = prelievo): ")
    )
    operazioni.append(operazione)
    saldo_attuale = calcola_saldo_finale(operazioni)
    saldi.append(saldo_attuale)

saldo_finale = calcola_saldo_finale(operazioni)
print(f"\nSaldo finale: €{saldo_finale:.2f}")

saldo_max = max(saldi)
saldo_min = min(saldi)
print(f"Saldo massimo raggiunto: €{saldo_max:.2f}")
print(f"Saldo minimo raggiunto: €{saldo_min:.2f}")

num_depositi = 0
num_prelievi = 0
for operazione in operazioni:
    if operazione > 0:
        num_depositi += 1
    elif operazione < 0:
        num_prelievi += 1

print(f"\nNumero di depositi: {num_depositi}")
print(f"Numero di prelievi: {num_prelievi}")


# riepilogo
print("\n=== RIEPILOGO CONTO ===")
print("Saldi dopo ogni operazione:")
for i in range(len(saldi)):
    if i == 0:
        print(f"Saldo iniziale: €{saldi[i]:.2f}")
    else:
        print(f"Dopo operazione {i}: €{saldi[i]:.2f}")

print(f"\nSaldo finale: €{saldo_finale:.2f}")
