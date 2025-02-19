import json
import os
from funzioni import *
import string
import time
from datetime import timedelta
import asn1tools as asn
from test_latenza import GeoNetworking
from time import sleep
from scapy.all import *


def compile_asn():
    schema = asn.compile_files('ITS-Container.asn','uper')
    return schema

def send_frame(frame, ip, usr, psw, schema):
    '''
    input:
        dict: dizionario contenente tutte le informazioni di un frame
            appartenenti ad una singola fotocamera
        ip: indirizzo ip del device
        usr: nome del device
        psw: password del device
        schema: compilazione asn fatta una volta sola
    '''
    
    
    for object in frame["data"]["objects"]:
        
        latfull = str(object["latitude"])
        lonfull = str(object["longitude"])

        # soluzione uno
        lat = latfull.strip(".")[:2] + latfull.strip(".")[3:10]
        lon = lonfull.strip(".")[:2] + lonfull.strip(".")[3:10]
        send_cam(ip, usr, psw, int(lat),int(lon), schema)
        
        # soluzione due
        '''
        lat = int(latfull.replace(".", "")[:9])
        lon = int(lonfull.replace(".", "")[:9])
        send_cam(ip, usr, psw, lat, lon, schema)
        '''

def send_frame_to_rasp(frame, schema):
    recipients_mac_adress= 'ff:ff:ff:ff:ff:ff'
    your_mac_adress= 'b4:b5:b6:c4:11:49'
    interface = 'wlan1'
    somma = 0.0
    
    for object in frame["data"]["objects"]:
            #while True:
            prima = time.perf_counter()
            latfull = str(object["latitude"])
            lonfull = str(object["longitude"])
            # soluzione uno
            #lat = latfull.strip(".")[:2] + latfull.strip(".")[3:10]
            #lon = lonfull.strip(".")[:2] + lonfull.strip(".")[3:10]
            #send_cam(ip, usr, psw, int(lat),int(lon), cam)
            # soluzione due
            lat = int(latfull.replace(".", "")[:9])
            lon = int(lonfull.replace(".", "")[:9])
            dict_to_send = {'header': {'protocolVersion': 2, 'messageID': 2, 'stationID': 10},
            'cam': {'generationDeltaTime': int(time.time()), 'camParameters':
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
            cam_bytes = schema.encode('CAM', dict_to_send)
            uper_string = cam_bytes.hex()
            command = 'date +%3S%3N'
            geo = GeoNetworking(version= 1,basic_next_header = 1, reserved = 0,
                            life_time_multiplier = 60, life_time_base = 1,
                            remaining_hop_limit = 1, common_next_header = 2, h_reserved = 0,
                            header_type = 5, header_sub_type = 0, traffic_story_carry_forward = 0,
                            traffic_channel_offload = 0, traffic_class_id = 2, mobility_flags = 0,
                            flags_reserved = 0, payload_lenght = 50, maximum_hop_limit = 1, Reserved = 0,
                            gn_addr_manual = 0, gn_addr_its_type = 15, gn_addr_its_country_code = 0,
                            gn_addr_address = your_mac_adress ,timestamp = int(subprocess.check_output(command, shell=True, text=True)),
                            latitude = lat, longitude = lon, position_accuracy_indicator = 0,
                            speed = 0, heading = 0,local_channel_busy_ratio = 0,max_neighbouring_cbr = 0,
                            output_power = 23,reserved_tsbp = 0,reserved_tsbp_2 = 0)
            # Visualizza il pacchetto
            cam_raw = raw(cam_bytes)
            geo_raw = raw(geo)
            #print(b)
            btp_b_raw = b'\x07\xd1\x54\x00'
            dot11 = Dot11(subtype=8,type=2, proto=0, ID=0, addr1="ff:ff:ff:ff:ff:ff", addr2=your_mac_adress, addr3="ff:ff:ff:ff:ff:ff", SC=480)
            qos = Dot11QoS(A_MSDU_Present=0, Ack_Policy=1, EOSP=0, TID=3, TXOP=0 )
            llc = LLC(dsap=0xaa, ssap=0xaa, ctrl=3)
            snap = SNAP(OUI=0, code=0x8947)
            raww = Raw(load=geo_raw+btp_b_raw+cam_raw)
            mex = RadioTap(present = 0x400000, timestamp = int(subprocess.check_output(command, shell=True, text=True)),  ts_accuracy = 0,ts_position = 0, ts_flags = None)/dot11/qos/llc/snap/raww
            print(len(mex))
            print(geo_raw)
            answer = sendp(mex, iface=interface)
            elps = timedelta(seconds=time.perf_counter()-prima)
            print("elapsed: ", elps)
            somma = somma + elps.total_seconds()
            #sleep(0.1)
            break
    print("somma di tutti gli oggetti: ", somma)
