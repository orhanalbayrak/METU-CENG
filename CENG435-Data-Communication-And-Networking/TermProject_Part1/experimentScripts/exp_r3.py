import socket
import sys
import time



# Create a UDP socket
ssock_source_r3 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  #We create a UDP server socket for R_3
csock_dest = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)   #We create a UDP client socket for dest
server_ip3 = '10.10.3.2'
dest_ip = '10.10.7.1'
server_port_r3 = 26213  #Server Port for R_3 
server_port_dest = 26210   #Server Port for dest 

message = b'This is a message from r_3' #This is message from Router_3


ssock_source_r3.bind((server_ip3, server_port_r3))  #Server socket for Router_3 ________# Bind the socket to the port

def r3_send2_dest ():  #This is function for sending packets from r1 to dest
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
    print('1000 messages are sent from r_3 to dest') 
    print('Total RTT for Router-3 to dest -->',total_time_dest)
    print('RTT per one message for Router-3 to dest -->',avr_time_dest)
    

try:
    r3_send2_dest()
    

finally:
    print('closing socket dest')
    csock_dest.close()

q=0
while q<10:
    print('\nrouter_3 is waiting to receive message from source')
    data, address = ssock_source_r3.recvfrom(4096)

    print('received {} bytes from {}'.format(
        len(data), address))
    print(data)


    if data:
        sent = ssock_source_r3.sendto(data, address)
        print('sent {} bytes back to {}'.format(
            sent, address))
        q+=1


