from math import sqrt

# https://www.programmareinpython.it/video-corso-python-base/checkpoint-costruiamo-una-calcolatrice-con-python/
# modificato con una lista di tuple

hello_message = """
Benvenuti al programma calcolatrice!

Di seguito un elenco delle varie funzioni disponibili:

- Per effettuare un'Addizione, seleziona 1;
- Per effettuare una Sottrazione, seleziona 2;
- Per effettuare una Moltiplicazione, seleziona 3;
- Per effettuare una Divisione, seleziona 4;
- Per effettuare un Calcolo Esponenziale, seleziona 5;
- Per effettuare una Radice Quadrata, seleziona 6;
- Per uscire dal programma puoi digitare ESC;
"""


def addizione():
    print("\nHai scelto: Addizione\n")
    a = float(input("Inserisci il Primo Numero -> "))
    b = float(input("Inserisci il Secondo Numero -> "))
    print("Il risultato dell'Addizione è: ", str(a + b))


def sottrazione():
    print("\nHai scelto: Sottrazione\n")
    a = float(input("Inserisci il Primo Numero -> "))
    b = float(input("Inserisci il Secondo Numero -> "))
    print("Il risultato della Sottrazione è: ", str(a - b))


def moltiplicazione():
    print("\nHai scelto: Moltiplicazione\n")
    a = float(input("Inserisci il Primo Numero -> "))
    b = float(input("Inserisci il Secondo Numero -> "))
    print("Il risultato della Moltiplicazione è: ", str(a * b))


def divisione():
    print("\nHai scelto: Divisione\n")
    a = float(input("Inserisci il Primo Numero -> "))
    b = float(input("Inserisci il Secondo Numero -> "))
    print("Il risultato della Divisione è: ", str(a / b))


def calcolo_esponenziale():
    print("\nHai scelto: Calcolo Esponenziale\n")
    a = float(input("Inserisci la Base -> "))
    b = float(input("Inserisci l'Esponente -> "))
    print("Il risultato del Calcolo Esponenziale è: ", str(a**b))


def radice_quadrata():
    print("\nHai scelto: Radice Quadrata\n")
    a = float(input("Inserisci il Numero -> "))
    print("Il risultato dell'operazione è: ", sqrt(a))


# lista di tuple (input utente, funzione correlata)
operazioni = [
    ("1", addizione),
    ("2", sottrazione),
    ("3", moltiplicazione),
    ("4", divisione),
    ("5", calcolo_esponenziale),
    ("6", radice_quadrata),
]


def __main__():
    while True:
        print(hello_message)

        action = input(
            "Inserisci il numero corrispondente all'operazione da effettuare: "
        )

        for op in operazioni:
            # controllo se l'input action corrisponde a una delle operazioni della lista
            if action == op[0]:
                op[1]()
                break

        if action == "ESC":
            print("\nL'Applicazione verrà chiusa\n")
            break

        new_action = input("\nDesideri continuare ad usare l'applicazione? S/N ")
        if new_action == "N" or new_action == "n":
            print("A presto!\n")
            break

        print("Sto tornando al menù principale\n")


if __name__ == "__main__":
    __main__()
