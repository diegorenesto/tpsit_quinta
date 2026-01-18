import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = "127.0.0.1"
port = 8080

# connect
client_socket.connect((host, port))

while True:
    tentativo = input("Inserisci un numero (1-100): ")

    client_socket.send(tentativo.encode())

    risposta = client_socket.recv(1024).decode()
    print("Server:", risposta)

    if risposta == "bravo":
        break

client_socket.close()
