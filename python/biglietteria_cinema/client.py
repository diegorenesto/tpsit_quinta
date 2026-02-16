import socket
import json
import tkinter as tk
from tkinter import messagebox

def start_client():
    localhost = '127.0.0.1'
    port = 8080

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((localhost, port))

    data = client_socket.recv(1024).decode()
    film = json.loads(data)

    root = tk.Tk()
    root.title("Biglietteria Cinema")

    tk.Label(root, text="Seleziona film:").pack()
    film_var = tk.StringVar(root)
    film_var.set(list(film.keys())[0])

    menu = tk.OptionMenu(root, film_var, *film.keys())
    menu.pack()

    tk.Label(root, text="Numero biglietti:").pack()
    entry_biglietti = tk.Entry(root)
    entry_biglietti.pack()

    def acquista():
        try:
            numero = int(entry_biglietti.get())
            if numero <= 0:
                messagebox.showerror("Errore", "Numero non valido")
                return
        except:
            messagebox.showerror("Errore", "Inserire un numero valido")
            return

        richiesta = {
            "film": film_var.get(),
            "biglietti": numero
        }

        client_socket.send(json.dumps(richiesta).encode())

        risposta = json.loads(client_socket.recv(1024).decode())

        if "errore" in risposta:
            messagebox.showerror("Errore", risposta["errore"])
        else:
            messagebox.showinfo(
                "Risultato",
                f"Totale: {risposta['totale']}€\n"
                f"Sconto: {risposta['sconto']}€\n"
                f"Finale: {risposta['finale']}€"
            )

    tk.Button(root, text="Acquista", command=acquista).pack()

    root.mainloop()
    client_socket.close()

if __name__ == "__main__":
    start_client()