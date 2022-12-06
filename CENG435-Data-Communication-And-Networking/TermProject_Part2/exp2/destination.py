import socket
import sys
import select
import struct
import hashlib

portr1 = 9990
portr2 = 9991
hostr1 = "10.10.4.2"  #
hostr2 = "10.10.5.2"  # 'localhost'
r1_is_alive = True
r2_is_alive = True

r1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
r1.bind((hostr1, portr1))
r2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
r2.bind((hostr2, portr2))

# addr = (host,port)
buf = 1000

print("Now, I am listening to Source........")

f = open("output.txt", 'wb')
expected_ack = 0
# data,addr = r1.recvfrom(buf)


while 1:
    if r1_is_alive and r2_is_alive:
        try:
            data, addr = r1.recvfrom(buf)
            r1.settimeout(2)
            # Finding Ack and Seq Num. extracting packet
            ack_number = struct.unpack("d", data[:8])[0]

            # Obtaining hash of data with opening packet content
            check_from_source = struct.unpack("32s", data[8:40])[0].decode("utf-8")
            # print('hash: ',check_from_source)

            # Obtainin real data without ack and checksum
            data = data[40:]

            # After obtaning data, we get checksum of data again to compare
            check_from_r3 = hashlib.md5(data).hexdigest()
            # print('data hash: ',check_from_r3)

            if ack_number == expected_ack and check_from_r3 == check_from_source:
                print("r1: Now this packet ack number --> (", int(ack_number + 1), ")has received successfully")
                f.write(data)
                res = struct.pack('d', expected_ack)
                r1.sendto(res, addr)
                expected_ack += 1
            else:
                print('wrong ack number came, discarding..')
                res = struct.pack('d', expected_ack - 1)
                r1.sendto(res, addr)
                continue
        except:
            print('r1 went down')
            r1_is_alive = False
            continue

        try:
            data, addr = r2.recvfrom(buf)
            r2.settimeout(2)
            # Finding Ack and Seq Num. extracting packet
            ack_number = struct.unpack("d", data[:8])[0]

            # Obtaining hash of data with opening packet content
            check_from_source = struct.unpack("32s", data[8:40])[0].decode("utf-8")
            # print('hash: ',check_from_source)

            # Obtainin real data without ack and checksum
            data = data[40:]

            # After obtaning data, we get checksum of data again to compare
            check_from_r3 = hashlib.md5(data).hexdigest()
            # print('data hash: ',check_from_r3)
            if ack_number == expected_ack and check_from_r3 == check_from_source:
                print("r2: Now this packet ack number --> (", int(ack_number + 1), ")has received successfully")
                f.write(data)
                res = struct.pack('d', expected_ack)
                r1.sendto(res, addr)
                expected_ack += 1
            else:
                print('wrong ack number came, discarding..')
                res = struct.pack('d', expected_ack - 1)
                r1.sendto(res, addr)
                continue
        except:
            print('r2 went down')
            r2_is_alive = False
            continue

    elif r1_is_alive and not r2_is_alive:
        try:
            data, addr = r1.recvfrom(buf)
            r1.settimeout(2)

            # Finding Ack and Seq Num. extracting packet
            ack_number = struct.unpack("d", data[:8])[0]

            # Obtaining hash of data with opening packet content
            check_from_source = struct.unpack("32s", data[8:40])[0].decode("utf-8")
            # print('hash: ',check_from_source)

            # Obtainin real data without ack and checksum
            data = data[40:]

            # After obtaning data, we get checksum of data again to compare
            check_from_r3 = hashlib.md5(data).hexdigest()
            # print('data hash: ',check_from_r3)

            if ack_number == expected_ack and check_from_r3 == check_from_source:
                print("r1: Now this packet ack number --> (", int(ack_number + 1), ")has received successfully")
                f.write(data)
                res = struct.pack('d', expected_ack)
                r1.sendto(res, addr)
                expected_ack += 1
            else:
                print('wrong ack number came, discarding..')
                res = struct.pack('d', expected_ack - 1)
                r1.sendto(res, addr)
                continue
        except:
            print('r1 went down')
            r1_is_alive = False
            continue

    elif not r1_is_alive and r2_is_alive:
        try:
            data, addr = r2.recvfrom(buf)
            r2.settimeout(2)

            # Finding Ack and Seq Num. extracting packet
            ack_number = struct.unpack("d", data[:8])[0]

            # Obtaining hash of data with opening packet content
            check_from_source = struct.unpack("32s", data[8:40])[0].decode("utf-8")
            # print('hash: ',check_from_source)

            # Obtainin real data without ack and checksum
            data = data[40:]

            # After obtaning data, we get checksum of data again to compare
            check_from_r3 = hashlib.md5(data).hexdigest()
            # print('data hash: ',check_from_r3)
            if ack_number == expected_ack and check_from_r3 == check_from_source:
                print("r2: Now this packet ack number --> (", int(ack_number + 1), ")has received successfully")
                f.write(data)
                res = struct.pack('d', expected_ack)
                r1.sendto(res, addr)
                expected_ack += 1
            else:
                print('wrong ack number came, discarding..')
                res = struct.pack('d', expected_ack - 1)
                r1.sendto(res, addr)
                continue
        except:
            print('r2 went down')
            r2_is_alive = False
            continue
    else:
        break
print('closing file')
f.close()
r1.close()
r2.close()
