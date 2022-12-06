import socket
import sys
import time

# Open a file
fo = open("link_costs.txt", "w")

# Create a UDP socket
ssock_source_r1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  #We create a UDP server socket for R_1
csock_dest = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)   #We create a UDP client socket for dest
csock_r2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)   #We create a UDP client socket for R_2
server_ip1 = '10.10.1.2'
dest_ip = '10.10.4.2'
r2_ip = '10.10.8.2'
server_port_r1 = 26211  #Server Port for R_1
server_port_r2 = 26212  #Server Port for R_2
server_port_dest = 26210   #Server Port for dest

message = b'This is a message from r_1' #This is message from Router_1




ssock_source_r1.bind((server_ip1, server_port_r1))  #Server socket for Router_1 ________# Bind the socket to the port

def r1_send2_dest ():  #This is function for sending packets from r1 to dest
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
    print('1000 messages are sent from r_1 to dest')
    print('Total RTT for Router-1 to dest -->',total_time_dest)
    print('RTT per one message for Router-1 to dest -->',avr_time_dest)
    fo.write('\nRTT per one message for Router-1 to dest -->' + str(avr_time_dest))

def r1_send2_r2 ():  #This is function for sending packets from r1 to r2
    star_time_r2 = time.time()  #Time is starting just before sending process
    i=0
    while i < 1000:
        print('sending to r2 {!r}'.format(message))
        sent2_r2 = csock_r2.sendto(message, (r2_ip, server_port_r2))  #Send to messages r2
        print('waiting to receive')
        data, server = csock_r2.recvfrom(4096)   # Receive response from r2
        print('received {!r}'.format(data))
        print(i+1) # Sequence number of packets
        i+=1
    end_time_r2 = time.time()  #After taking all r2 acks arrived we stopped time to find total time
    total_time_r2 = end_time_r2 - star_time_r2  #Total time
    avr_time_r2 = total_time_r2 / 1000  #Average time for RTT source and r2
    print('1000 messages are sent from r_1 to r2')
    print('Total RTT for Router-1 to r2 -->',total_time_r2)
    print('RTT per one message for Router-1 to r2 -->',avr_time_r2)
    fo.write('\nRTT per one message for Router-1 to r2 -->' + str(avr_time_r2))


try:
    r1_send2_dest()

    r1_send2_r2()

finally:
    print('closing socket dest')
    csock_dest.close()
    print('closing socket r2')
    csock_r2.close()
q=0
while q<1000:
    print('\nrouter_1 is waiting to receive message from source')
    data, address = ssock_source_r1.recvfrom(4096)

    print('received {} bytes from {}'.format(
        len(data), address))
    print(data)


    if data:
        sent = ssock_source_r1.sendto(data, address)
        print('sent {} bytes back to {}'.format(
            sent, address))
        q+=1


data, address = ssock_source_r1.recvfrom(4096)
print(data.decode())
fo.write(data.decode())




# Close opend file
fo.close()
