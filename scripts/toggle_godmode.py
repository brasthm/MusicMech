import socket
import struct
import sys

# Hash identique à Utils::hash(SERVER_NAME + SERVER_VERSION)
def utils_hash(key: str) -> int:
    PRIME_CONST = 2
    h = 0
    for i, c in enumerate(key):
        h += ord(c) * (PRIME_CONST ** i)
        h %= 16777216
    return h

SERVER_NAME = "SYNCHROBEATSERV"
SERVER_VERSION = "2.0"
ADMIN_PORT = 41110

def send_admin(ip: str, command: str):
    # En-tete : hash Int32 (big-endian) puis string SFML (Uint32 length + bytes)
    header_hash = utils_hash(SERVER_NAME + SERVER_VERSION)
    cmd_bytes = command.encode("ascii")
    packet = struct.pack(">iI", header_hash, len(cmd_bytes)) + cmd_bytes

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.settimeout(3)
    sock.sendto(packet, (ip, ADMIN_PORT))
    try:
        data, addr = sock.recvfrom(1024)
        print(f"Reponse du serveur: {data}")
    except socket.timeout:
        print("Pas de reponse (mais la commande a ete envoyee)")
    finally:
        sock.close()

if __name__ == "__main__":
    ip = sys.argv[1] if len(sys.argv) > 1 else "127.0.0.1"
    cmd = sys.argv[2] if len(sys.argv) > 2 else "GOD_MODE"
    print(f"Envoi de '{cmd}' vers {ip}:{ADMIN_PORT} ...")
    send_admin(ip, cmd)
