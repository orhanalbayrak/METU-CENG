import socket
import sys

# Create a UDP socket

ssock_dest_r3 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  #We create a UDP server socket for R_3

server_ip_dest_r3 = '10.10.7.1'

server_port = 26210  #Server Port for routers

ssock_dest_r3.bind((server_ip_dest_r3, server_port))  #Server socket for dest ________# Bind the socket to the port




k=0
while k<1000:
    print('\nDestination is waiting to receive message coming from Router_3')
    data, address = ssock_dest_r3.recvfrom(4096)

    print('received {} bytes from {}'.format(
        len(data), address))
    print(data)

    if data:
        sent = ssock_dest_r3.sendto(data, address)
        print('sent {} bytes back to {}'.format(
            sent, address))
        k+=1
