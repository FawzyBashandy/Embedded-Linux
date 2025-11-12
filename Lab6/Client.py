import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('localhost', 8080))

while True:
    # Receive server prompt and respond
    prompt = client.recv(1024).decode()
    print(prompt, end='')
    first_number = input()
    client.sendall(first_number.encode())

    prompt = client.recv(1024).decode()
    print(prompt, end='')
    second_number = input()
    client.sendall(second_number.encode())

    prompt = client.recv(1024).decode()
    print(prompt, end='')
    operation = input()
    client.sendall(operation.encode())

    # Receive and print result
    result = client.recv(1024).decode()
    print(result)
    break  # Exit after one calculation (remove to keep looping)
