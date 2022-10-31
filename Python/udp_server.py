
import socket
import struct 
 

localIP     = "127.0.0.1"

localPort   = 20001

bufferSize  = 1024

 

msgFromServer       = "Hello UDP Client"

bytesToSend         = str.encode(msgFromServer)

 

# Create a datagram socket

UDPServerSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

 

# Bind to address and ip

UDPServerSocket.bind((localIP, localPort))

 

print("UDP server up and listening")

 

# Listen for incoming datagrams

while(True):

    bytesAddressPair = UDPServerSocket.recvfrom(bufferSize)

    data = bytesAddressPair[0]

    address = bytesAddressPair[1]

    # clientMsg = "Message from Client:{}".format(message)
    # clientIP  = "Client IP Address:{}".format(address)
    
    # print(message)
    # print(clientIP)

    tx = struct.unpack('>f', data[0:4])
    ty = struct.unpack('>f', data[4:8])
    tz = struct.unpack('>f', data[8:12])

    rx = struct.unpack('>f', data[12:16])
    ry = struct.unpack('>f', data[16:20])
    rz = struct.unpack('>f', data[20:24])
    rw = struct.unpack('>f', data[24:28])

    print(f"position x: {tx}")
    print(f"position y: {ty}")
    print(f"position z: {tz}")
    print(f"rotation x: {rx}")
    print(f"rotation y: {ry}")
    print(f"rotation z: {rz}")
    print(f"rotation w: {rw}")
   

    # Sending a reply to client

    # UDPServerSocket.sendto(bytesToSend, address)