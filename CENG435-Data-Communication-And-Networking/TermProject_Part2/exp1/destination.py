

import socket
import sys
import select
import struct
import hashlib

host = "10.10.7.1"
port = 9998
s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind((host,port))
windows_size = 5

addr = (host,port)
buf=1000

print ("Now, I am listening to Source........")


f = open("output.txt",'wb')
expected_ack = 0
data,addr = s.recvfrom(buf)
s.settimeout(2)

try:
	while data:
		# Finding Ack and Seq Num. extracting packet
		ack_number = struct.unpack("d", data[:8])[0]

		# Obtaining hash of data with opening packet content
		check_from_source = struct.unpack("32s", data[8:40])[0].decode("utf-8")
		#print('hash: ',check_from_source)

		# Obtainin real data without ack and checksum
		data = data[40:]

		# After obtaning data, we get checksum of data again to compare
		check_from_r3 = hashlib.md5(data).hexdigest()
		#print('data hash: ',check_from_r3)

		if ack_number == expected_ack and check_from_r3 == check_from_source:
			print("Now this packet ack number --> (",int(ack_number+1),")has received successfully")
			f.write(data)
			res = struct.pack('d',expected_ack)
			s.sendto(res, addr)
			expected_ack += 1
		else:
			print('esit degil')
			res = struct.pack('d',expected_ack-1)
			s.sendto(res, addr)

		data,addr = s.recvfrom(buf)

except:
	if (ack_number == 99.0):
		f.close()
		s.close()
		print ("File Downloaded")

	else:
		res = struct.pack('d',expected_ack-1)
		s.sendto(res, addr)