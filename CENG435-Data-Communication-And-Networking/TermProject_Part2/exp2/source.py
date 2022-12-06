
import socket
import sys
import time
import struct
import hashlib

# Create a UDP socket

srcsock_r1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # We create a UDP client socket for R_1
srcsock_r2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # We create a UDP client socket for R_2
srcsock_r1.settimeout(2)
srcsock_r2.settimeout(2)

seqNumber = 0
r1_alive = True
r2_alive = True

server_ip1 = '10.10.1.2' #Roter_1 Ip Address
server_ip2 = '10.10.2.1' #Roter_2 Ip Address

server_Addr_r1 = (server_ip1, 9999)
server_Addr_r2 = (server_ip2, 9997)

file_buffer = 900

# with concurrent.futures.ThreadPoolExecutor(max_workers=1) as pipeLineParam:
#        for i1 in range(window_size):
#            print("windowi1: ", str(window[i1]))
#            window_res[i1] = pipeLineParam.submit(send_pck, r3addr, window[i1], i1).result()

# Opens input file for reading and sending it to r3
with open("input.txt", "rb") as inputFile:
    # Read 512KB data from file
    data = inputFile.read(file_buffer)

    while data:
        # Hashing data with hashlib function and packed it
        md5ChecksumFile = hashlib.md5(data)
        # print(md5ChecksumFile.hexdigest())
        packedChecksum = struct.pack("32s", md5ChecksumFile.hexdigest().encode())

        # packed Sequence Number of Packet
        seqNumber_packed = struct.pack("d", seqNumber)
        print('Now sending seq number --> ', seqNumber)
        data = seqNumber_packed + packedChecksum + data
        if seqNumber == 5556:
            break
        if seqNumber % 2 == 0 and r1_alive:  # use r1
            try:
                if srcsock_r1.sendto(data, server_Addr_r1):
                    data1, addr1 = srcsock_r1.recvfrom(1000)
                    incoming_ack = struct.unpack('d', data1)[0]
                    print('Now incoming ack number -->: ', int(incoming_ack))
                    print("111Packect is sending Sequence Number -->", seqNumber, "__________window -->",
                          int(incoming_ack / 4) + 1)
                    if incoming_ack == seqNumber:
                        seqNumber = seqNumber + 1
                        data = inputFile.read(file_buffer)
            except:
                r1_alive = False
                print('timeout occurred at r1')
        elif seqNumber % 2 == 1 and r2_alive:  # use r2
            try:
                if srcsock_r2.sendto(data, server_Addr_r2):
                    data1, addr1 = srcsock_r2.recvfrom(1000)
                    incoming_ack = struct.unpack('d', data1)[0]
                    print('Now incoming ack number -->: ', int(incoming_ack))
                    if incoming_ack == seqNumber:
                        seqNumber = seqNumber + 1
                        data = inputFile.read(file_buffer)
                    print("222Packect is sending Sequence Number -->", seqNumber, "__________window -->",
                          int(incoming_ack / 4) + 1)
            except:
                r2_alive = False
                print('timeout occurred at r2')
        elif seqNumber % 2 == 0 and not r1_alive:
            try:
                if srcsock_r2.sendto(data, server_Addr_r2):
                    data1, addr1 = srcsock_r2.recvfrom(1000)
                    incoming_ack = struct.unpack('d', data1)[0]
                    print('Now incoming ack number -->: ', int(incoming_ack))
                    if incoming_ack == seqNumber:
                        seqNumber = seqNumber + 1
                        data = inputFile.read(file_buffer)
                    print("333Packect is sending Sequence Number -->", seqNumber, "__________window -->",
                          int(incoming_ack / 4) + 1)
            except:
                r2_alive = False
                print('timeout occurred at r2')
        elif seqNumber % 2 == 1 and not r2_alive:
            try:
                if srcsock_r1.sendto(data, server_Addr_r1):
                    data1, addr1 = srcsock_r1.recvfrom(1000)
                    incoming_ack = struct.unpack('d', data1)[0]
                    print('Now incoming ack number -->: ', int(incoming_ack))
                    if incoming_ack == seqNumber:
                        seqNumber = seqNumber + 1
                        data = inputFile.read(file_buffer)
                        if not data:
                            print("file bitti aq")
                            break
                    print("444Packect is sending Sequence Number -->", seqNumber, "__________window -->",
                          int(incoming_ack / 4) + 1)
            except:
                r1_alive = False
                print('timeout occurred at r1')

