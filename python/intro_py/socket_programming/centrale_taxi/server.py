import socket

disponibilita_taxi = 10

host = "127.0.0.1"
port = 8080


def avvia_server():
    global disponibilita_taxi

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        print(f"In ascolto su {host}:{port}...")

        while True:
            conn, addr = s.accept()
            with conn:
                data = conn.recv(1024).decode("utf-8")

                if not data:
                    continue

                citta_partenza, citta_arrivo = data.split(";")
                if disponibilita_taxi > 0:
                    risposta = f"Taxi disponibile! Prenotazione da {citta_partenza} a {citta_arrivo} confermata"
                    disponibilita_taxi -= 1
                else:
                    risposta = "Nessun taxi disponibile"

                conn.sendall(risposta.encode("utf-8"))


if __name__ == "__main__":
    avvia_server()
