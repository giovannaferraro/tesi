import requests
import asn1tools as asn
import os, subprocess,time
from requests import Request
import sys
from datetime import datetime
import hashlib
import os
import json

def compile_asn():
  schema = asn.compile_files('ITS-Container.asn','uper')
  return schema

def encode(dict, cam):
  cam_bytes = cam.encode('CAM', dict)
  #print("byte: ", cam_bytes)
  return cam_bytes.hex()

def generate_cam(lat, lon, cam):
    dict_to_send = {'header': {'protocolVersion': 2, 'messageID': 2, 'stationID': 10},
                 'cam': {'generationDeltaTime': 12345, 'camParameters':
                          {'basicContainer': {'stationType': 5, 'referencePosition': {'latitude': lat, 'longitude': lon,
                         'positionConfidenceEllipse': {'semiMajorConfidence': 282, 'semiMinorConfidence': 280, 'semiMajorOrientation': 1138},
                           'altitude': {'altitudeValue': 6050, 'altitudeConfidence': 'alt-020-00'}}}, 'highFrequencyContainer': 
                           ('basicVehicleContainerHighFrequency', {'heading': {'headingValue': 62, 'headingConfidence': 8}, 'speed': 
                            {'speedValue': 1163, 'speedConfidence': 4}, 'driveDirection': 'forward', 'vehicleLength': 
                            {'vehicleLengthValue': 42, 'vehicleLengthConfidenceIndication': 'trailerPresenceIsUnknown'}, 'vehicleWidth': 18,
                              'longitudinalAcceleration': {'longitudinalAccelerationValue': -2, 'longitudinalAccelerationConfidence': 102},
                             'curvature': {'curvatureValue': 386, 'curvatureConfidence': 'onePerMeter-0-01'}, 'curvatureCalculationMode': 
                             'yawRateUsed', 'yawRate': {'yawRateValue': 2354, 'yawRateConfidence': 'unavailable'}, 'accelerationControl': (b'@', 7), 
                             'steeringWheelAngle': {'steeringWheelAngleValue': 57, 'steeringWheelAngleConfidence': 1}, 'lateralAcceleration': 
                             {'lateralAccelerationValue': 43, 'lateralAccelerationConfidence': 102}})}}}

    messagebody = encode(dict_to_send, cam)
    return messagebody


def calculate_hash_256(bodyMessage):
    m = hashlib.sha256(bodyMessage.encode('utf-8')).hexdigest()
    return m

#def send_cam(Ip_address, username, password, lat, lon, cam):
def send_cam(lat, lon, cam):
    # qua le variabili vanno inizializzate manualmente in quanto i valori non vengono più presi da cloud.
    messageID = "2"
    timestamp = "Thu Mar 11 17:21:11 CET 2024"
    messageBodyFormat = "UPER"
    messageType = "CAM"
    messageDirection = "Upstream"
    ripetitionDurantion = 1 # tempo in cui diffondo il msg --> (ripetitionduration * 1000 / ripetitioninterval)
    ripetitionInterval = 1000  # intervallo tra ogni messaggio
    messageBody = generate_cam(lat, lon, cam)
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

    #r = requests.post('http://' + Ip_address + '/proxy/msg', auth = (username,password), json= json_to_send)

    #response = r.content
    print("generato cam")
