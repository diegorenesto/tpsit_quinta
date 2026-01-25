import socket
import tkinter as tk
from tkinter import ttk, messagebox
import threading
import time
from PIL import Image, ImageTk


host = "127.0.0.1"
port = 8080


def invia_richiesta():
    citta_partenza = entry_partenza.get().strip()
    citta_arrivo = entry_arrivo.get().strip()

    if not citta_partenza.isalpha() or not citta_arrivo.isalpha():
        messagebox.showerror(
            "Errore Input", "Le città devono contenere solo lettere", parent=root
        )
        return

    dati = f"{citta_partenza};{citta_arrivo}"

    # avvia spinner
    spinner_thread = threading.Thread(target=spinner_animazione, daemon=True)
    spinner_thread.start()

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            s.sendall(dati.encode("utf-8"))
            risposta = s.recv(1024).decode("utf-8")
            label_risposta.config(
                text=risposta,
                foreground="green" if "disponibile" in risposta else "red",
            )
    except ConnectionRefusedError:
        messagebox.showerror(
            "Errore Connessione", "Server non raggiungibile", parent=root
        )
    except Exception as e:
        messagebox.showerror("Errore Client", f"{e}", parent=root)
    finally:
        # stoppa spinner (impostando testo vuoto)
        label_spinner.config(text="")


def spinner_animazione():
    anim = ["|", "/", "-", "\\"]
    i = 0
    while label_risposta.cget("text") == "":  # finché non c'è risposta
        label_spinner.config(text=anim[i % 4])
        i += 1
        time.sleep(0.2)


# GUI Client
root = tk.Tk()
root.title("Prenota Taxi - Client")
root.geometry("400x550")
root.configure(bg="#2c3e50")  # Tema scuro

style = ttk.Style()
style.theme_use("clam")
style.configure("TLabel", background="#2c3e50", foreground="white")
style.configure("TButton", background="#27ae60", foreground="white")
style.configure("TEntry", fieldbackground="#34495e")

ttk.Label(root, text="Città Partenza:", font=("Arial", 12)).pack(pady=5)
entry_partenza = ttk.Entry(root)
entry_partenza.pack()

ttk.Label(root, text="Città Arrivo:", font=("Arial", 12)).pack(pady=5)
entry_arrivo = ttk.Entry(root)
entry_arrivo.pack()

btn_invia = ttk.Button(root, text="Verifica e Prenota", command=invia_richiesta)
btn_invia.pack(pady=10)

label_spinner = ttk.Label(root, text="", font=("Arial", 16))
label_spinner.pack()

label_risposta = ttk.Label(root, text="", font=("Arial", 12, "italic"), wraplength=300)
label_risposta.pack(pady=10)

canvas = tk.Canvas(root, width=350, height=250, bg="#34495e")
canvas.pack()

try:
    img = Image.open("taxi.png")
    img = img.resize((350, 250))
    photo = ImageTk.PhotoImage(img)
    canvas.create_image(0, 0, anchor=tk.NW, image=photo)
    canvas.image = photo
except Exception as e:
    canvas.create_text(175, 125, text="Immagine non trovata", fill="white")

root.mainloop()
