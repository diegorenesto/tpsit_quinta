import socket
import json

def calcola_sconto(n_biglietti, totale):
    if n_biglietti >= 5:
        return totale * 0.1
    return 0

def start_server():

    localhost = '127.0.0.1'
    port = 8080

    film = {
        "Matrix": {"posti": 50, "prezzo": 8} ,
        "The prestige": {"posti": 40, "prezzo": 7},
        "Avatar": {"posti": 50, "prezzo": 8}
    }

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((localhost, port))
    server_socket.listen(5)

    print(f"[SERVER] In ascolto sulla porta {port}\n")
    
    conn, addr = server_socket.accept()
    print("Connessione da", addr)

    conn.send(json.dumps(film).encode())
    data = conn.recv(1024).decode()
    richiesta = json.loads(data)

    nome_film = richiesta["film"]
    n_biglietti = richiesta["biglietti"]


    if n_biglietti <= 0:
        risposta = {"errore": "numero di biglietti non valido"}
    elif n_biglietti > film[nome_film]["posti"]:
        risposta = {"errore": "biglietti non disponibili"}
    else:
        prezzo = film[nome_film]["prezzo"]
        totale = prezzo * n_biglietti
        sconto = calcola_sconto(n_biglietti, totale)
        finale = totale - sconto

        film[nome_film]["posti"] -= n_biglietti

        risposta = {
            "totale": totale,
            "sconto": sconto,
            "finale": finale
        }

        conn.send(json.dumps(risposta).encode())

        conn.close()
        server_socket.close()

if __name__ == "__main__":
    start_server()