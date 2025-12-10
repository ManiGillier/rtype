


import socket
import struct
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7270))

time.sleep(5)

print("CA MARCHE !")

u8 = struct.unpack("B", s.recv(1))[0]
print(u8)

u32 = struct.unpack("I", s.recv(4))[0]
print(u32)

i1 = struct.unpack("i", s.recv(4))[0]
i2 = struct.unpack("i", s.recv(4))[0]

print(i1)
print(i2)
