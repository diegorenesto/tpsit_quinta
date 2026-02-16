import socket
from datetime import datetime


def calcola_statistiche(dati):
    if not dati:
        return {
            "num_giorni": 0,
            "num_rilevazioni": 0,
            "media": 0,
            "massima": 0,
            "minima": 0,
        }

    # raccolgo tutte le temperature in una lista
    tutte_temp = []
    for giorno in dati:
        tutte_temp.append(giorno[1])
        tutte_temp.append(giorno[2])

    num_giorni = len(dati)
    num_rilevazioni = len(tutte_temp)
    media = sum(tutte_temp) / num_rilevazioni
    massima = max(tutte_temp)
    minima = min(tutte_temp)

    return {
        "num_giorni": num_giorni,
        "num_rilevazioni": num_rilevazioni,
        "media": round(media, 2),
        "massima": massima,
        "minima": minima,
    }


def elabora_dati_ricevuti(dati_raw):
    righe = dati_raw.strip().split("\n")
    dati_elaborati = []

    for riga in righe:
        if not riga.strip():
            continue  # salta le righe vuote

        parti = riga.strip().split(";")
        if len(parti) != 3:
            return None, f"Formato errato nella riga: {riga}"

        data_str, temp12_str, temp24_str = parti

        try:
            datetime.strptime(data_str, "%d/%m/%Y")
        except ValueError:
            return None, f"Data non valida: {data_str} (formato richiesto: gg/mm/aaaa)"

        try:
            temp12 = float(temp12_str)
            temp24 = float(temp24_str)
        except ValueError:
            return None, f"Temperature non valide nella riga: {riga}"

        dati_elaborati.append((data_str, temp12, temp24))

    return dati_elaborati, None


def avvia_server():
    localhost = "127.0.0.1"
    port = 8080

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((localhost, port))
    server_socket.listen(1)

    print(f"===SERVER MONITORAGGIO TEMPERATURE===")
    print(f"In ascolto su {localhost}:{port}")

    while True:
        try:
            client_socket, addr = server_socket.accept()
            print(f"Connessione accettata da {addr}")

            dati_ricevuti = client_socket.recv(4096).decode("utf-8")
            print(f"Dati ricevuti:\n{dati_ricevuti}")

            if not dati_ricevuti:
                risposta = "ERRORE: Nessun dato ricevuto"
            else:
                dati_elaborati, errore = elabora_dati_ricevuti(dati_ricevuti)

                if errore:
                    risposta = f"ERRORE: {errore}"
                else:
                    stats = calcola_statistiche(
                        dati_elaborati
                    )
                    risposta = f"""===RISULTATI ANALISI TEMPERATURE===

Numero giorni analizzati: {stats["num_giorni"]}
Numero rilevazioni totali: {stats["num_rilevazioni"]}

Temperatura media: {stats["media"]} °C
Temperatura massima: {stats["massima"]} °C
Temperatura minima: {stats["minima"]} °C
"""

            client_socket.sendall(risposta.encode("utf-8"))
            print("Risposta inviata al client\n")

            client_socket.close()

        except Exception as e:
            print(f"Errore durante la gestione del client: {e}")
            try:
                client_socket.close()
            except:
                pass


if __name__ == "__main__":
    try:
        avvia_server()
    except KeyboardInterrupt:
        print("\nServer terminato dall'utente")
