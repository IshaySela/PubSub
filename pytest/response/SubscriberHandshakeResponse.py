import json
import base64

class SubscriberHandshakeResponse:
    subscriber_id:str

    def __init__(self, subscriber_id:str):
        self.subscriber_id = subscriber_id

    @staticmethod
    def from_raw_json(raw_json:str):
        return SubscriberHandshakeResponse(json.loads(raw_json)["Id"])