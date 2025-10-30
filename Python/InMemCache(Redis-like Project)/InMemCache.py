from gevent import socket
from gevent.server import StreamServer
from gevent import monkey
import logging

monkey.patch_all()

logger = logging.getLogger("InMemCache")

logging.basicConfig(level=logging.DEBUG)

class KeyValueStore(object):
    def __init__(self):
        # in-memory cache (data is lost when server stops)
        self.data = {}

    def set(self, key, value):
        self.data[key] = value
        return "OK"

    def get(self, key):
        # return "NULL" if not found (like Redis)
        return self.data.get(key, "NULL")

    def delete(self, key):
        if key in self.data:
            del self.data[key]
            return "1"   # 1 = deleted
        return "0"       # 0 = not found


class Server(object):
    """
    - Single in-memory key-value cache
    - Text protocol (NOT RESP yet)
    - Supported commands:
        SET <key> <value>
        GET <key>
        DELETE <key>
    Planned for 100%:
        - multi-key ops (MGET/MSET)
        - FLUSH (clear all)
        - RESP protocol
        - persistence to disk
        - TTL/expiration
    """

    def __init__(self, host="127.0.0.1", port=31337):
        self.host = host
        self.port = port
        self.store = KeyValueStore()
        self.server = StreamServer((host, port), self.handle_client)

    def start(self):
        logger.debug(f"Server started on {self.host}:{self.port}")
        self.server.serve_forever()

    def handle_client(self, conn, address):
        logger.debug(f"Client connected: {address[0]}:{address[1]}")
        fh = conn.makefile("rwb")

        while True:
            line = fh.readline()
            if not line:
                logger.debug(f"Client disconnected: {address[0]}:{address[1]}")
                break

            # Convert bytes -> str, remove \r\n
            line = line.decode("utf-8", "replace").strip()
            if not line:
                continue

            parts = line.split(" ", 2)
            cmd = parts[0].upper()

            # ----- SET key value
            if cmd == "SET":
                if len(parts) < 3:
                    resp = "ERR missing value\n"
                else:
                    key = parts[1]
                    value = parts[2]
                    resp = self.store.set(key, value) + "\n"

            # ----- GET key
            elif cmd == "GET":
                if len(parts) < 2:
                    resp = "ERR missing key\n"
                else:
                    key = parts[1]
                    resp = str(self.store.get(key)) + "\n"

            # ----- DELETE key
            elif cmd == "DELETE":
                if len(parts) < 2:
                    resp = "ERR missing key\n"
                else:
                    key = parts[1]
                    resp = self.store.delete(key) + "\n"

            # ----- unknown command
            else:
                resp = "ERR unknown command\n"

            # send response back
            fh.write(resp.encode("utf-8"))
            fh.flush()


class Client(object):


    def __init__(self, host="127.0.0.1", port=31337):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((host, port))
        self.fh = self.sock.makefile("rwb")

    def send_command(self, line):
        self.fh.write((line.strip() + "\n").encode("utf-8"))
        self.fh.flush()
        resp = self.fh.readline().decode("utf-8").strip()
        return resp

    def set(self, key, value):
        return self.send_command(f"SET {key} {value}")

    def get(self, key):
        return self.send_command(f"GET {key}")

    def delete(self, key):
        return self.send_command(f"DELETE {key}")


if __name__ == "__main__":
    Server().start()
