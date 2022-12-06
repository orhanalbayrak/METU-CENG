import socket  # We imported this lib. to be able use python socket functions
import sys
import time    # We imported time lib. to measure link cost bewtween source, routers, destination also for end-to-end-delay
import _thread # We used threads so that we can communicate with more than one client at the same time in the same network.


csock_r1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #We create a UDP client socket for R_1
csock_r2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #We create a UDP client socket for R_2
csock_r3 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #We create a UDP client socket for R_3

server_ip1 = '10.10.1.2' #Roter_1 Ip Address
server_ip2 = '10.10.2.1' #Roter_2 Ip Address
server_ip3 = '10.10.3.2' #Roter_3 Ip Address

server_port_r1 = 26211  #Server Port for R_1
server_port_r2 = 26212  #Server Port for R_2
server_port_r3 = 26213  #Server Port for R_3

message = b'This is a message from source to routers' #This is message that we sent to routers

def source_send2_r1 ():  #This is function for sending packets from source to Router_1
    star_time_r1 = time.time()  #Time is starting just before sending process
    i=0
    while i < 1000:
        print('sending to r1 {!r}'.format(message))
        sent2_r1 = csock_r1.sendto(message, (server_ip1, server_port_r1))  #Send to messages Router_1
        print('waiting to receive')
        data, server = csock_r1.recvfrom(4096)   # Receive response from Router_1
        print('received {!r}'.format(data))
        print(i+1) # Sequence number of packets
        i+=1
    end_time_r1 = time.time()  #After taking all Router_1 acks arrived we stopped time to find total time
    total_time_r1 = end_time_r1 - star_time_r1  #Total time
    avr_time_r1 = total_time_r1 / 1000  #Average time for RTT source and Router_1
    print('1000 messages are sent from source to r_1')
    print('Total RTT for Source-Router-1 -->',total_time_r1)
    print('RTT per one message for Source-Router-1 -->',avr_time_r1)
    final_message = "RTT for source_r1:" + str(avr_time_r1)
    sent2_r1 = csock_r1.sendto(final_message.encode(), (server_ip1, server_port_r1))

def source_send2_r2 ():  #This is function for sending packets from source to Router_2
    star_time_r2 = time.time()  #Time is starting just before sending process
    i=0
    while i < 1000:
        print('sending to r_2 {!r}'.format(message))
        sent2_r2 = csock_r2.sendto(message, (server_ip2, server_port_r2))  #Send to messages Router_2
        print('waiting to receive')
        data, server = csock_r2.recvfrom(4096)   # Receive response from Router_2
        print('received {!r}'.format(data))
        print(i+1) # Sequence number of packets
        i+=1
    end_time_r2 = time.time()  #After taking all Router_2 acks arrived we stopped time to find total time
    total_time_r2 = end_time_r2 - star_time_r2  #Total time
    avr_time_r2 = total_time_r2 / 1000  #Average time for RTT source and Router_2
    print('1000 messages are sent from source to r_2')
    print('Total RTT for Source-Router-2 -->',total_time_r2)
    print('RTT per one message for Source-Router-2 -->',avr_time_r2)
    final_message = "RTT for source_r2:" + str(avr_time_r2)
    sent2_r2 = csock_r2.sendto(final_message.encode(), (server_ip2, server_port_r2))

def source_send2_r3 ():  #This is function for sending packets from source to Router_3
    star_time_r3 = time.time()  #Time is starting just before sending process
    i=0
    while i < 1000:
        print('sending to r_3 {!r}'.format(message))
        sent2_r3 = csock_r3.sendto(message, (server_ip3, server_port_r3))  #Send to messages Router_3
        print('waiting to receive')
        data, server = csock_r3.recvfrom(4096)   # Receive response from Router_3
        print('received {!r}'.format(data))
        print(i+1) # Sequence number of packets
        i+=1
    end_time_r3 = time.time()  #After taking all Router_3 acks arrived we stopped time to find total time
    total_time_r3 = end_time_r3 - star_time_r3  #Total time
    avr_time_r3 = total_time_r3 / 1000  #Average time for RTT source and Router_3
    print('1000 messages are sent from source to r_3')
    print('Total RTT for Source-Router-3 -->',total_time_r3)
    print('RTT per one message for Source-Router-3 -->',avr_time_r3)
    final_message = "RTT for source_r3:" + str(avr_time_r3)
    sent2_r3 = csock_r3.sendto(final_message.encode(), (server_ip3, server_port_r3))


try:
    source_send2_r2()
    source_send2_r1()
    source_send2_r3()




finally:
    print('closing socket r1')
    csock_r1.close()
    print('closing socket r2')
    csock_r2.close()
    print('closing socket r3')
    csock_r3.close()
