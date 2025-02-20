import paho.mqtt.client as mqtt
import base64
import os
import json
import time
from datetime import timedelta
#from send_frame_to_dev import *

#schema = compile_asn()

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    # Subscribe to the topic(s) you expect to receive JSON files on
    client.subscribe("/haura/#", 0)

def on_subscribe(client, userdata, mid, granted_qos):
    print("Subscribed to topic")

# The callback for when a PUBLISH message is received from the server.


def on_message(client, userdata, message):
    #prima = time.perf_counter()
    #send_frame(json.loads(message.payload.decode('utf-8')), "10.0.1.157", "root", "password", schema)
    #print("diop")
    dizionario = json.loads(message.payload.decode('utf-8'))
    #send_frame_to_rasp(dizionario, schema)
    tempo_post_send = time.time()
    tmp = str(dizionario["data"]["head"]["stamp"])
    glass_time = float(tmp[:10]+"."+tmp[10:17])
    print("tempo passato da frame a obu: ", tempo_post_send - glass_time)
    #print("elapsed fine frame: ", timedelta(seconds=time.perf_counter()-prima), " e numero oggetti: ", dizionario["data"]["nObjects"] )
    #print("dio dopo")
    #with open('test_5.txt','a+') as f:
         #f.write(message.payload.decode('utf-8') + ",\n")

client = mqtt.Client()
client.on_connect = on_connect
client.on_subscribe = on_subscribe
client.on_message = on_message

# Set the IP address of your Ethernet-connected device
client.connect("127.0.0.1", 1883, 120)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
client.loop_forever()
