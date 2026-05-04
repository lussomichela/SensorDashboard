import socket

qemu_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
qemu_socket.connect("/tmp/qt_bridge.sock")
qt_app = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
qt_app.connect(("192.168.64.1", 1234)) 

while True:
    data = qemu_socket.recv(20) 
    if data:
        qt_app.sendall(data) 

