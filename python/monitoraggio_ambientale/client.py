import socket
import tkinter as tk
from tkinter import messagebox, scrolledtext
from datetime import datetime


class ClientTemperatureGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Invio temperature giornaliere")
        self.root.geometry("600x500")
        self.root.resizable(True, True)

        self.server_host = "localhost"
        self.server_port = 8080

        self.crea_interfaccia()

    def crea_interfaccia(self):
        main_frame = tk.Frame(self.root, padx=10, pady=10)
        main_frame.pack(fill=tk.BOTH, expand=True)

        tk.Label(
            main_frame,
            text="Inserisci i dati in formato: gg/mm/aaaa;temperatura12;temperatura24",
            font=("Arial", 10, "bold"),
        ).pack(pady=(0, 5))

        tk.Label(
            main_frame,
            text="Esempio: 16/02/2026;18.5;16.2\n(Un giorno per riga)",
            font=("Arial", 9),
            fg="gray",
        ).pack(pady=(0, 10))

        tk.Label(main_frame, text="Dati:", anchor="w").pack(fill=tk.X)

        self.text_area = scrolledtext.ScrolledText(
            main_frame,
            height=8,
            width=60,
            font=("Courier", 10),
            wrap=tk.NONE,
        )

        self.text_area.pack(fill=tk.BOTH, expand=True, pady=(0, 10))

        self.text_area.insert(
            "1.0", "16/02/2026;18.5;16.2\n17/02/2026;19.1;17.0\n18/02/2026;20.0;18.4"
        )

        # frame pulsanti
        button_frame = tk.Frame(main_frame)
        button_frame.pack(fill=tk.X, pady=5)

        # pulsante invio
        self.invia_btn = tk.Button(
            button_frame,
            text="Invia dati",
            command=self.invia_dati,
            bg="#4CAF50",
            fg="white",
            padx=20,
            pady=5,
            font=("Arial", 10, "bold"),
        )
        self.invia_btn.pack(side=tk.LEFT, padx=5)

        tk.Button(
            button_frame,
            text="Cancella tutto",
            command=self.cancella_tutto,
            bg="#f44336",
            fg="white",
            padx=20,
            pady=5,
        ).pack(side=tk.LEFT, padx=5)

        tk.Label(main_frame, text="Risultati:", anchor="w").pack(
            fill=tk.X, pady=(10, 0)
        )

        self.risultati_area = scrolledtext.ScrolledText(
            main_frame,
            height=8,
            width=60,
            font=("Courier", 10),
            state="disabled",
            bg="#f0f0f0",
        )
        self.risultati_area.pack(fill=tk.BOTH, expand=True, pady=(0, 10))

        self.status_bar = tk.Label(
            self.root, text="Pronto", bd=1, relief=tk.SUNKEN, anchor=tk.W
        )
        self.status_bar.pack(side=tk.BOTTOM, fill=tk.X)

    def valida_dati_locali(self, testo):
        righe = testo.strip().split("\n")

        for i, riga in enumerate(righe, 1):
            if not riga.strip():
                continue

            parti = riga.strip().split(";")
            if len(parti) != 3:
                return (
                    False,
                    f"Riga {i}: formato non valido (richiesti 3 campi separati da ;)",
                )

            data, temp12, temp24 = parti

            try:
                datetime.strptime(data, "%d/%m/%Y")
            except ValueError:
                return False, f"Riga {i}: data non valida '{data}' (formato gg/mm/aaaa)"

            try:
                float(temp12)
                float(temp24)
            except ValueError:
                return False, f"Riga {i}: temperature non numeriche"

        return True, "OK"

    def invia_dati(self):
        dati_da_inviare = self.text_area.get("1.0", tk.END).strip()

        if not dati_da_inviare:
            messagebox.showwarning("Attenzione", "Inserire almeno un giorno di dati")
            return

        # AGGIUNTO: validazione dati prima dell'invio
        valido, msg = self.valida_dati_locali(dati_da_inviare)
        if not valido:
            messagebox.showerror("Errore di validazione", msg)
            return

        self.invia_btn.config(state="disabled", text="Invio in corso...")
        self.status_bar.config(text="Connessione al server...")
        self.root.update()

        try:
            # =========================
            client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client_socket.settimeout(10)  # AGGIUNTO: timeout di 10 secondi

            self.status_bar.config(
                text=f"Connessione a {self.server_host}:{self.server_port}..."
            )
            self.root.update()

            client_socket.connect((self.server_host, self.server_port))

            self.status_bar.config(text="Invio dati in corso")
            client_socket.send(dati_da_inviare.encode("utf-8"))

            self.status_bar.config(text="Attesa risposta dal server...")
            risposta = client_socket.recv(4096).decode("utf-8")

            self.risultati_area.config(state="normal")
            self.risultati_area.delete("1.0", tk.END)
            self.risultati_area.insert(tk.END, risposta)
            self.risultati_area.config(state="disabled")

            self.status_bar.config(text="Operazione completata con successo")

            if risposta.startswith("ERRORE"):
                messagebox.showerror("Errore dal server", risposta)
            else:
                messagebox.showinfo(
                    "Successo", "Dati elaborati correttamente dal server"
                )

            client_socket.close()

        except ConnectionRefusedError:
            self.status_bar.config(text="ERRORE: Server non attivo")
            messagebox.showerror(
                "Errore di connessione",
                f"Impossibile connettersi al server {self.server_host}:{self.server_port}\n"
                "Verifica che il server sia in esecuzione.",
            )
        except socket.timeout:
            self.status_bar.config(text="ERRORE: Timeout connessione")
            messagebox.showerror("Errore", "Timeout: il server non risponde")
        except Exception as e:
            self.status_bar.config(text=f"ERRORE: {str(e)[:50]}")
            messagebox.showerror(
                "Errore", f"Errore durante la comunicazione:\n{str(e)}"
            )
        finally:
            # riabilita il pulsante
            self.invia_btn.config(state="normal", text="Invia dati")

    def cancella_tutto(self):
        if messagebox.askyesno("Conferma", "Cancellare tutti i dati?"):
            self.text_area.delete("1.0", tk.END)
            self.risultati_area.config(state="normal")
            self.risultati_area.delete("1.0", tk.END)
            self.risultati_area.config(state="disabled")
            self.status_bar.config(text="Dati cancellati")


def main():
    root = tk.Tk()
    app = ClientTemperatureGUI(root)

    def on_closing():
        if messagebox.askokcancel("Uscita", "Chiudere l'applicazione?"):
            root.destroy()

    root.protocol("WM_DELETE_WINDOW", on_closing)
    root.mainloop()


if __name__ == "__main__":
    main()
