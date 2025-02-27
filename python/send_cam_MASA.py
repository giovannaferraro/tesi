import requests
from requests import Request
import sys
from datetime import datetime
import hashlib
import os
#from google.cloud import firestore
import json

#Ip_address = '10.0.1.157'
#username = 'root'
#password = 'suV2X01!'
Ip_address = '10.0.1.158'
username = 'root'
password = 'v2x'

def calculate_hash_256(bodyMessage):
    m = hashlib.sha256(bodyMessage.encode('utf-8')).hexdigest()
    return m


# qua le variabili vanno inizializzate manualmente in quanto i valori non vengono più presi da cloud.
messageID = "2"
timestamp = "Thu Mar 11 17:21:11 CET 2024"
messageBodyFormat = "UPER"
messageType = "CAM"
messageDirection = "Upstream"
ripetitionDurantion = -1
ripetitionInterval = 0 
messageBody = "02020000670e89d8005a0d70ee4e3af9f522342308e433c8545803e0e2458302968a7b35818224c2104700197980"
hash = calculate_hash_256(messageBody)

json_to_send = {
        "messageId": messageID,
        "timestamp": timestamp,
        "hash": hash,
        "messageBodyFormat": messageBodyFormat,
        "messageType": messageType,
        "messageDirection": messageDirection,
        "repetitionDuration": ripetitionDurantion,
        "repetitionInterval": ripetitionInterval,
        "messageBody": messageBody
        }

r = requests.post('http://' + Ip_address + '/proxy/msg', auth = (username,password), json= json_to_send)

response = r.content


if r.status_code == 200:
    print("Request was successful.")
else:
    print(f"Request failed with status code {response.status_code}.")