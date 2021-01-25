import json

class PublisherHandshakeResponse:
    id:str
    status:int

    def __init__(self, id:str, status:int):
        self.id = id
        self.status = status

    @staticmethod
    def from_json_string(raw_json:str):
        obj = json.loads(raw_json)
        
        return PublisherHandshakeResponse(obj["id"], obj["status"])
