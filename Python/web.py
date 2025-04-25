import socket

ip = "34.116.68.59"
start_port = 61000
end_port = 61500
message = b"EMU"

for port in range(start_port, end_port + 1):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.settimeout(1.5)
            s.connect((ip, port))
            s.sendall(message)
            data = s.recv(1024)
            if data:
                print(f"[+] Port {port} responded: {data.decode()}")
    except Exception as e: 
        print(f"[-] Port {port} failed: {e}")
        continue