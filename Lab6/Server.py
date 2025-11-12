import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('localhost', 8080))
server.listen(5)
print("Server is listening on port 8080...")
first_number = 0
second_number = 0
op = ''
while True:
    client_socket, addr = server.accept()
    print(f"Connection from {addr} has been established!")

    client_socket.sendall("Enter First Number : ".encode())  
    first_number = client_socket.recv(30).decode().strip()

    client_socket.sendall("Enter Second Number : ".encode())  
    second_number = client_socket.recv(30).decode().strip()
    
    client_socket.sendall("Enter Operation (+, -, *, /) : ".encode())
    op = client_socket.recv(5).decode().strip()

    result = 0
    num2 = float(second_number)
    num1 = float(first_number)
    if op == '+':
        result = num1 + num2
    elif op == '-':
        result = num1 - num2
    elif op == '*':
        result = num1 * num2
    elif op == '/':
        result = num1 / num2
    else:
        result = "Invalid Operation"

    client_socket.sendall(f"Result: {result}\n".encode())  # Encode string to bytes and send
    client_socket.close() # Close the client socket after handling the request
