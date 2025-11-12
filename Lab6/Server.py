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
    client_socket.sendall("Enter First Number : ".encode())  # Encode string to bytes and send
    first_number = client_socket.recv(30).decode().strip()  # Receive up to 30 bytes and decode from bytes to string
    client_socket.sendall("Enter Second Number : ".encode())  # Encode string to bytes and send
    second_number = client_socket.recv(30).decode().strip()  # Receive up to 30 bytes and decode from bytes to string
    client_socket.sendall("Enter Operation (+, -, *, /) : ".encode())  # Encode string to bytes and send
    op = client_socket.recv(5).decode().strip()
      # Receive up to 5 bytes and decode from bytes to string
    result = 0
    try:
        num1 = float(first_number)
        num2 = float(second_number)
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
    except ValueError:
        result = "Invalid Number"
    except ZeroDivisionError:
        result = "Division by Zero Error"
    client_socket.sendall(f"Result: {result}\n".encode())  # Encode string to bytes and send
    client_socket.close() # Close the client socket after handling the request
