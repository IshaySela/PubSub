import socket
import json
from ClientType import ClientType
import Settings

from response.PublishDataResponse import PublishDataResponse
from response.PublisherHandshakeResponse import PublisherHandshakeResponse

class Publisher:
    __rawClient:socket.socket
    __encrypted:bool
    __encryption_string:str

    handshakeResponse:PublisherHandshakeResponse
    def __init__(self,encrypt: bool = False, encryption_string:str = ""):
        self.__rawClient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.__encrypted = encrypt
        self.__encryption_string = encryption_string

        self.__handshake()
    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.__rawClient.close()

    def __handshake(self):
        self.__rawClient.connect((Settings.HOST, Settings.PORT))

        headers = {
            "ClientType": ClientType.Publisher,
            "Encrypt": self.__encrypted,
            "EncryptionString": self.__encryption_string
        }

        self.__rawClient.send(json.dumps(headers).encode())
        self.__delimiter()

        resp = self.__rawClient.recv(1024 * 4).decode()
        
        self.handshakeResponse = PublisherHandshakeResponse.from_json_string(resp)
    
    def __delimiter(self):
        self.__rawClient.send(b"\r\n\r\n")
    
    def publish(self,data: bytes, data_type:str = "Binary") -> PublishDataResponse:
        return self.publish(data, len(data), data_type)

    def publish(self, data:bytes, length: int, data_type:str):
        headers = {
            "Length": length,
            "DataType": data_type,
        }

        self.__rawClient.send(json.dumps(headers).encode())
        self.__delimiter()
        self.__rawClient.send(data)

        response_string = self.__rawClient.recv(1024 * 4).decode()
        if response_string == '\r\n\r\n':
            response_string = self.__rawClient.recv(1024 * 4).decode()

        return PublishDataResponse.from_raw_json(response_string)

def save_id(id):
    with open('./sub-id.txt', 'w+') as file:
        file.write(id)

def test():
    with Publisher() as publisher:
        msg = b'Hello, World!'
        print('Publisher id:', publisher.handshakeResponse.id)
        save_id(publisher.handshakeResponse.id)
        
        while True:
            msg = input("Enter message to emit: ")
            publisher.publish(msg.encode(), len(msg), "Binary")


if __name__ == "__main__":
    test()

