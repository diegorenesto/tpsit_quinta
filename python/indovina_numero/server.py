import socket
import random

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = "127.0.0.1"  # localhost
port = 8080

# bind e listen
server_socket.bind((host, port))
server_socket.listen(2)
print("[SERVER] In ascolto sulla porta 8080")

# accept
conn, addr = server_socket.accept()
print("Client connesso:", addr)

# numero rand segreto
num = random.randint(1, 100)
# print("Numero rand:", num)

while True:
    data = conn.recv(1024).decode()
    if not data:
        break

    tentativo = int(data)
    if tentativo > num:
        risposta = "troppo alto"
    elif tentativo < num:
        risposta = "troppo basso"
    else:
        risposta = "bravo"
        conn.send(risposta.encode())
        break
    conn.send(risposta.encode())

conn.close()
server_socket.close()
