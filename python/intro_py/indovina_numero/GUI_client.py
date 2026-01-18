import socket
import tkinter as tk

# socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(("127.0.0.1", 8080))


def invia_tentativo():
    tentativo = entry.get()
    client_socket.send(tentativo.encode())

    risposta = client_socket.recv(1024).decode()
    text_area.insert(tk.END, f"Tentativo: {tentativo}\n")
    text_area.insert(tk.END, f"Server: {risposta}\n\n")

    if risposta == "bravo":
        button.config(state=tk.DISABLED)

# root
root = tk.Tk()
root.title("Indovina il numero")

# label
label = tk.Label(root, text="Inserisci un numero (1-100): ")
label.pack(pady=5)

# entry (inserisci numero)
entry = tk.Entry(root)
entry.pack(pady=5)

# button (invia tentativo)
button = tk.Button(root, text="Prova", command=invia_tentativo)
button.pack(pady=5)

# text (mostra risposta al server)
text_area = tk.Text(root, height=10, width=40)
text_area.pack(pady=5)

root.mainloop()
client_socket.close