import json

class PublishDataResponse:
    status:int

    def __init__(self, status:int):
        self.status = status

    @staticmethod
    def from_raw_json(raw_json:str):
        return PublishDataResponse(json.loads(raw_json)["Status"])