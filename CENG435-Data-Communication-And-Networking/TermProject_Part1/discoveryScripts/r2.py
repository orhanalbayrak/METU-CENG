import socket
import sys
import time


# Open a file
fo = open("link_costs.txt", "w")

# Create a UDP socket
ssock_r2_r1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  #We create a UDP server socket for R_1
ssock_r2_r3 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  #We create a UDP server socket for R_3
ssock_r2_s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  #We create a UDP server socket for source
csock_dest = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)   #We create a UDP client socket for dest
server_ip_r2_r1 = '10.10.8.2'
server_ip_r2_r3 = '10.10.6.1'
server_ip_r2_s = '10.10.2.1'
dest_ip = '10.10.5.2'
server_port_r2 = 26212  #Server Port for R_2
server_port_dest = 26210   #Server Port for dest

message = b'This is a message from r_2' #This is message from Router_2




ssock_r2_r1.bind((server_ip_r2_r1, server_port_r2))  #Server socket for Router_2 ________# Bind the socket to the port
ssock_r2_r3.bind((server_ip_r2_r3, server_port_r2))  #Server socket for Router_2 ________# Bind the socket to the port
ssock_r2_s.bind((server_ip_r2_s, server_port_r2))    #Server socket for Router_2 ________# Bind the socket to the port

def r2_send2_dest ():  #This is function for sending packets from r2 to dest
    star_time_dest = time.time()  #Time is starting just before sending process
    i=0
    while i < 1000:
        print('sending to dest {!r}'.format(message))
        sent2_dest = csock_dest.sendto(message, (dest_ip, server_port_dest))  #Send to messages dest
        print('waiting to receive')
        data, server = csock_dest.recvfrom(4096)   # Receive response from dest
        print('received {!r}'.format(data))
        print(i+1) # Sequence number of packets
        i+=1
    end_time_dest = time.time()  #After taking all dest acks arrived we stopped time to find total time
    total_time_dest = end_time_dest - star_time_dest  #Total time
    avr_time_dest = total_time_dest / 1000  #Average time for RTT source and dest
    print('1000 messages are sent from r_2 to dest')
    print('Total RTT for Router-2 to dest -->',total_time_dest)
    print('RTT per one message for Router-2 to dest -->',avr_time_dest)
    fo.write('\nRTT per one message for Router-2 to dest -->' + str(avr_time_dest))

try:
    r2_send2_dest()

finally:
    print('closing socket dest')
    csock_dest.close()

j=0
while j<1000:
    print('\nrouter_2 is waiting to receive message coming from r1')
    data, address = ssock_r2_r1.recvfrom(4096)

    print('received {} bytes from {}'.format(
        len(data), address))
    print(data)


    if data:
        sent = ssock_r2_r1.sendto(data, address)
        print('sent {} bytes back to {}'.format(
            sent, address))
        j+=1

k=0
while k<1000:
    print('\nrouter_2 is waiting to receive message coming from r3')
    data, address = ssock_r2_r3.recvfrom(4096)

    print('received {} bytes from {}'.format(
        len(data), address))
    print(data)


    if data:
        sent = ssock_r2_r3.sendto(data, address)
        print('sent {} bytes back to {}'.format(
            sent, address))
        k+=1





i=0
while i<1000:
    print('\nrouter_2 is waiting to receive message coming from source')
    data, address = ssock_r2_s.recvfrom(4096)

    print('received {} bytes from {}'.format(
        len(data), address))
    print(data)


    if data:
        sent = ssock_r2_s.sendto(data, address)
        print('sent {} bytes back to {}'.format(
            sent, address))
        i+=1

data, address = ssock_r2_s.recvfrom(4096)
print(data.decode())
fo.write(data.decode())

# Close opend file
fo.close()
