import socket
import sys
import time
import struct
import hashlib

# Create a UDP socket

srcsock_r3 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #We create a UDP client socket for R_3
srcsock_r3.settimeout(4)

seqNumber = 0

server_ip3 = '10.10.3.2' #Roter_3 Ip Address

server_port_r3 = 26613  #Server Port for R_3

# server_Addr_r1=(server_ip1,server_port_r1)  #Server Address for R_1
# server_Addr_r2=(server_ip2,server_port_r2)  #Server Address for R_2
# server_Addr_r3=(server_ip3,server_port_r3)  #Server Address for R_3

server_Addr_r3=(server_ip3,9999)

#with concurrent.futures.ThreadPoolExecutor(max_workers=1) as pipeLineParam:
#        for i1 in range(window_size):
#            print("windowi1: ", str(window[i1]))
#            window_res[i1] = pipeLineParam.submit(send_pck, r3addr, window[i1], i1).result()

# Opens input file for reading and sending it to r3
with open("input.txt", "rb") as inputFile:
	# Read 512KB data from file
	data = inputFile.read(900)
	#startTime = struct.pack("d", time.time())


	while data:
		# Hashing data with hashlib function and packed it
		md5ChecksumFile = hashlib.md5(data)
		#print(md5ChecksumFile.hexdigest())
		packedChecksum = struct.pack("32s", md5ChecksumFile.hexdigest().encode())

		# packed Sequence Number of Packet
		seqNumber_packed = struct.pack("d", seqNumber)
		print('Now sending seq number --> ',seqNumber)
		data = seqNumber_packed + packedChecksum + data
		try:
			if srcsock_r3.sendto(data,server_Addr_r3):
				data1,addr1 = srcsock_r3.recvfrom(1000)
				incoming_ack = struct.unpack('d',data1)[0]
				print('Now incoming ack number -->: ',int(incoming_ack))
				if incoming_ack == seqNumber:
					seqNumber = seqNumber + 1
					data = inputFile.read(900)
				print ("Packect is sending Sequence Number -->",seqNumber, "__________window -->", int(incoming_ack/4)+1)
		except:
			print('timeout occurred')
