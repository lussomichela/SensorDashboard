import socket
import sys
import time

# CONFIGURATION 
WINDOWS_IP = "192.168.64.1"
DASHBOARD_PORT = 1234
QEMU_SOCKET = "/tmp/qt_bridge.sock"

def start_bridge():
    # Connection to the Windows Dashboard (TCP)
    try:
        qt_app = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        qt_app.connect((WINDOWS_IP, DASHBOARD_PORT))
        print(">>> Connected to Windows Dashboard")
    except Exception as e:
        print(f"ERROR: Could not connect to Dashboard: {e}")
        return

    # Connection to the QEMU Unix Socket (RPMsg Channel)
    try:
        qemu_socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        qemu_socket.connect(QEMU_SOCKET)
        print(">>> Connected to QEMU (RPMsg Channel)")
    except Exception as e:
        print(f"ERROR: Could not connect to QEMU socket: {e}")
        qt_app.close()
        return

    # Buffer 
    data_buffer = ""

    while True:
        try:
            raw_data = qemu_socket.recv(1024)
            
            if not raw_data:
                print(">>> QEMU closed the connection.")
                break

            chunk = raw_data.decode('utf-8', errors='ignore')
            data_buffer += chunk

            while "\n" in data_buffer:
                line, data_buffer = data_buffer.split("\n", 1)
                line = line.strip()

                # Look for our custom data protocol prefix
                if "DATA|" in line:
                    start_index = line.find("DATA|")
                    clean_line = line[start_index:]
                    
                    print(f"Received RPMsg: {clean_line}")

                    # Forward the clean string to the Windows App
                    qt_app.sendall((clean_line + "\n").encode('utf-8'))

                    # Local terminal debug 
                    parts = clean_line.split('|')
                    if len(parts) >= 6:
                        print(f"  [Parsed] Temp: {parts[1]}, Hum: {parts[2]}, Press: {parts[3]}")

        except KeyboardInterrupt:
            print("\nStopping bridge...")
            break
        except Exception as e:
            print(f"Loop Error: {e}")
            break

    # Resource cleanup
    qemu_socket.close()
    qt_app.close()
    print(">>> Bridge closed.")

if __name__ == "__main__":
    start_bridge()