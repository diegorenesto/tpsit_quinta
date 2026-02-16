import socket
import tkinter as tk
from tkinter import ttk, messagebox
import threading
from datetime import datetime


class server_taxi:
    def __init__(self):
        self.disponibilita = 10
        self.prenotazioni = []

    def prenota(self, citta_partenza, citta_arrivo):
        if self.disponibilita > 0:
            self.disponibilita -= 1
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            prenotazione = f"{timestamp} - Da {citta_partenza} a {citta_arrivo}"
            self.prenotazioni.append(prenotazione)
            self.salva_prenotazioni()
            return f"Taxi disponibile! Prenotazione confermata. Rimasti: {self.disponibilita}"
        return "Nessun taxi disponibile."

    def reset_disponibilita(self):
        self.disponibilita = 10

    def salva_prenotazioni(self):
        with open("prenotazioni.txt", "a") as f:
            f.write("\n".join(self.prenotazioni[-1:]) + "\n")  # aggiunge l'ultima


host = "127.0.0.1"
port = 8080
centrale = server_taxi()


def avvia_server():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((host, port))
            s.listen()
            label_status.config(text=f"In ascolto su {host}:{port}", foreground="green")

            while True:
                conn, addr = s.accept()
                with conn:
                    data = conn.recv(1024).decode("utf-8")
                    if not data:
                        continue

                    try:
                        citta_partenza, citta_arrivo = data.split(";")
                        risposta = centrale.prenota(citta_partenza, citta_arrivo)
                        conn.sendall(risposta.encode("utf-8"))
                        aggiorna_lista()
                    except ValueError:
                        conn.sendall(
                            "Errore: formato non valido (usa 'partenza;arrivo')".encode(
                                "utf-8"
                            )
                        )
    except Exception as e:
        messagebox.showerror("Errore Server", f"{e}", parent=root)


def aggiorna_lista():
    tree.delete(*tree.get_children())
    for pren in centrale.prenotazioni:
        tree.insert("", "end", values=(pren,))
    label_disponibilita.config(text=f"Disponibilità: {centrale.disponibilita}")


# GUI Server  (https://docs.python.org/3/library/tkinter.ttk.html#using-ttk)
root = tk.Tk()
root.title("Centrale Taxi - Server")
root.geometry("500x400")
root.configure(bg="#2c3e50")

style = ttk.Style()
style.theme_use("clam")
style.configure("TLabel", background="#2c3e50", foreground="white")
style.configure("TButton", background="#3498db", foreground="white")
style.configure(
    "Treeview", background="#34495e", foreground="white", fieldbackground="#34495e"
)
style.map("Treeview", background=[("selected", "#2980b9")])

frame_top = ttk.Frame(root)
frame_top.pack(pady=10)

label_status = ttk.Label(frame_top, text="Server spento", font=("Arial", 12))
label_status.pack()

label_disponibilita = ttk.Label(
    root, text=f"Disponibilità: {centrale.disponibilita}", font=("Arial", 14, "bold")
)
label_disponibilita.pack(pady=10)

btn_avvia = ttk.Button(
    root,
    text="Avvia Server",
    command=lambda: threading.Thread(target=avvia_server, daemon=True).start(),
)
btn_avvia.pack(pady=5)

btn_reset = ttk.Button(
    root,
    text="Reset Disponibilità",
    command=lambda: [centrale.reset_disponibilita(), aggiorna_lista()],
)
btn_reset.pack(pady=5)

# lista prenotazioni
ttk.Label(root, text="Storico Prenotazioni:", font=("Arial", 12)).pack(pady=10)

scrollbar = ttk.Scrollbar(root)
scrollbar.pack(side="right", fill="y")

tree = ttk.Treeview(
    root, columns=("Prenotazione",), show="headings", yscrollcommand=scrollbar.set
)
tree.heading("Prenotazione", text="Dettagli")
tree.pack(fill="both", expand=True)
scrollbar.config(command=tree.yview)

root.mainloop()
