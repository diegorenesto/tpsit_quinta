import socket

HOST = "127.0.0.1"
PORT = 8080


def start_client():
    citta_partenza = input("Inserisci la città di partenza: ").strip()
    citta_arrivo = input("Inserisci la città di arrivo: ").strip()

    if not citta_partenza or not citta_arrivo:
        return

    dati = f"{citta_partenza};{citta_arrivo}"

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(dati.encode("utf-8"))
        risposta = s.recv(1024).decode("utf-8")
        print("Risposta dal server:", risposta)


if __name__ == "__main__":
    start_client()
