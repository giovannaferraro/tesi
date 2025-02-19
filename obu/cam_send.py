from scapy.all import *
import time, subprocess
import asn1tools as asn
import os
from time import sleep

recipients_mac_adress= 'ff:ff:ff:ff:ff:ff'
your_mac_adress= 'b4:b5:b6:c4:11:49'
interface = 'wlan1'

latitude = 446351418
longitude = 108136683

file = "test_4.json"
f = open(file, 'r')
obj = json.load(f)

cam = asn.compile_files('ITS-Container.asn','uper')
dict_to_send = {'header': {'protocolVersion': 2, 'messageID': 2, 'stationID': 10},
                 'cam': {'generationDeltaTime': int(time.time()), 'camParameters':
                          {'basicContainer': {'stationType': 5, 'referencePosition': {'latitude': 449224306, 'longitude': 109968809,
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


cam_bytes = cam.encode('CAM', dict_to_send)

uper_string = cam_bytes.hex()

# Definisci il livello di protocollo GeoNetworking
class GeoNetworking(Packet):
    name = "GeoNetworking"
    fields_desc = [
        #BASIC HEADER
        BitField("version", 1,4),
        BitField("basic_next_header", 0,4),
        BitField("reserved", 0,8),
        # The LTMultiplier is a 6 bit unsigned integer, which represents a multiplier range from 0 to 26 - 1 = 63. Nel pacchetti GWONW di movyon è 60
        BitField("life_time_multiplier", 60,6,8), 
        # The LTBase sub-field represents a two bit unsigned selector that chooses one out of four predefined values -->
        #0 50 ms
        #1 1 s
        #2 10 s
        #3 100 s
        BitField("life_time_base", 0,2), 
        BitField("remaining_hop_limit", 0, 8),

        #COMMON HEADER
        #0 (usato da movyon) UNSPECIFIED
        #1 BTP-A
        #2 BTP-B
        #3 IPV6
        BitField("common_next_header", 1,4), 
        BitField("h_reserved", 0,4), #set to 0
        BitField("header_type", 0,4), # 0 unspecified, 1 BEACON etc.
        BitField("header_sub_type", 0,4),
        BitField("traffic_story_carry_forward", 0,1),
        BitField("traffic_channel_offload", 0,1),
        BitField("traffic_class_id", 0,6),
        BitField("mobility_flags", 0,1),
        BitField("flags_reserved", 0,7), #reserved to 0
        BitField("payload_lenght", 0,16),
        BitField("maximum_hop_limit", 1,8),
        BitField("Reserved", 0,8), #set to 0

        #BEACON HEADER
        #GN_ADDR
        #BitField("gn_addr_manual", 0,1),
        #BitField("gn_addr_its_type", 0,5),
        #BitField("gn_addr_its_country_code", 0,10),
        #MACField("gn_addr_address", "78:5e:e8:50:08:a2"),

        #BitField("timestamp", 0,32), #number of elapsed TAI milliseconds since 2004-01-01 00:00:00.000 UTC
        #BitField("latitude", 0,32),
        #BitField("longitude", 0,32),
        #Set to 1 (i.e. True) if the semiMajorConfidence
        #of the PosConfidenceEllipse as specified in
        #ETSI TS 102 894-2 [11] is smaller than the GN
        #protocol constant itsGnPaiInterval / 2
        #Set to 0 (i.e. False) otherwise

        #BitField("position_accuracy_indicator", 0,1),
        #BitField("speed", 0,15),
        #BitField("heading", 0,16),

        #TOPOLOGICALLY SCOPED PACKET 

        BitField("gn_addr_manual", 0,1),
        BitField("gn_addr_its_type", 0,5),
        BitField("gn_addr_its_country_code", 0,10),
        MACField("gn_addr_address", "78:5e:e8:50:08:a2"),

        BitField("timestamp", 0,32), #number of elapsed TAI milliseconds since 2004-01-01 00:00:00.000 UTC
        BitField("latitude", 0,32),
        BitField("longitude", 0,32),
        #Set to 1 (i.e. True) if the semiMajorConfidence
        #of the PosConfidenceEllipse as specified in
        #ETSI TS 102 894-2 [11] is smaller than the GN
        #protocol constant itsGnPaiInterval / 2
        #Set to 0 (i.e. False) otherwise

        BitField("position_accuracy_indicator", 0,1),
        BitField("speed", 0,15),
        BitField("heading", 0,16),

        BitField('local_channel_busy_ratio',0,8),
        BitField('max_neighbouring_cbr',0,8),
        BitField('output_power',0,5),
        BitField('reserved_tsbp',0,3),
	BitField('reserved_tsbp_2',0,8)
    ]





# Registra il nuovo livello di protocollo
#bind_layers(Dot11, GeoNetworking, type=0x8947)  # Usa il valore EtherType corretto

'''

# Creare un pacchetto GeoNetworking personalizzato ---> BEACON PACKET
geo = GeoNetworking(version= 1,basic_next_header = 1, reserved = 0,
                            life_time_multiplier = 60, life_time_base = 1,
                            remaining_hop_limit = 1, common_next_header = 0, h_reserved = 0,
                            header_type = 1, header_sub_type = 0, traffic_story_carry_forward = 0,
                            traffic_channel_offload = 0, traffic_class_id = 3, mobility_flags = 0,
                            flags_reserved = 0, payload_lenght = 0, maximum_hop_limit = 1, Reserved = 0,
                            gn_addr_manual = 0, gn_addr_its_type = 15, gn_addr_its_country_code = 0,
                            gn_addr_address = your_mac_adress ,timestamp = int(time.time()),
                            latitude = latitude, longitude = longitude, position_accuracy_indicator = 0,
                            speed = 0, heading = 0)
'''

# Creare un pacchetto CAM personalizzato 


while True:
	
	command = 'date +%3S%3N'
	geo = GeoNetworking(version= 1,basic_next_header = 1, reserved = 0,
                            life_time_multiplier = 60, life_time_base = 1,
                            remaining_hop_limit = 1, common_next_header = 2, h_reserved = 0,
                            header_type = 5, header_sub_type = 0, traffic_story_carry_forward = 0,
                            traffic_channel_offload = 0, traffic_class_id = 2, mobility_flags = 0,
                            flags_reserved = 0, payload_lenght = 50, maximum_hop_limit = 1, Reserved = 0,
                            gn_addr_manual = 0, gn_addr_its_type = 15, gn_addr_its_country_code = 0,
                            gn_addr_address = your_mac_adress ,timestamp = int(subprocess.check_output(command, shell=True, text=True)),
                            latitude = latitude, longitude = longitude, position_accuracy_indicator = 0,
                            speed = 0, heading = 0,local_channel_busy_ratio = 0,max_neighbouring_cbr = 0,
                            output_power = 23,reserved_tsbp = 0,reserved_tsbp_2 = 0)



	print(geo)

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
	mex = RadioTap(present = 0x400000, timestamp = int(subprocess.check_output(command, shell=True, text=True)),  ts_accuracy = 0,  ts_position = 0,ts_flags = None)/dot11/qos/llc/snap/raww

	
	

	print(len(mex))
	print(geo_raw)
	answer = sendp(mex, iface=interface)
	sleep(0.5)

