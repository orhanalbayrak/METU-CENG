import socket  # We imported this lib. to be able use python socket functions 
import sys
import time    # We imported time lib. to measure link cost bewtween source, routers, destination also for end-to-end-delay



csock_r3 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #We create a UDP client socket for R_3

server_ip3 = '10.10.3.2' #Roter_3 Ip Address

server_port_r3 = 26213  #Server Port for R_3

message = b'This is a message from source to routers' #This is message that we sent to routers

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
    print('End to end delay for Source-Router-3 -->',total_time_r3)
    print('RTT per one message for Source-Router-3 -->',avr_time_r3)
    final_message = "RTT for source_r3:" + str(avr_time_r3)
    


try:
    source_send2_r3()


finally:
    print('closing socket r3')
    csock_r3.close()