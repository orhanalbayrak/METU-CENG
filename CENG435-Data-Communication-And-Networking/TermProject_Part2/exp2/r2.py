import socket

# Create a UDP socket
csock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_ip = '10.10.5.2'
client_port = 9997
ssock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client_ip = '10.10.2.1'
server_port = 9991
# Bind the socket to the port
buf = 1000
csock.bind((client_ip, client_port))

while True:
    print('\nwaiting client')
    data, address = csock.recvfrom(buf)

    # Send data
    ssock.sendto(data, (server_ip, server_port))

    # Receive response
    print('waiting server')
    data1, server = ssock.recvfrom(buf)

    if data1:
        sent = csock.sendto(data1, address)