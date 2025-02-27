
import paho.mqtt.subscribe as subscribe
import ujson as json
import base64
import os
import time
from datetime import timedelta
from funzioni import *

schema = compile_asn()

def print_msg(client, userdata, message):
    global i
    dizionario = json.loads(message.payload.decode('utf-8'))
    data = dizionario["data"]
    '''
    t1 - t0
    '''
    tmp = str(data["head"]["stamp"])
    glass_time = float(tmp[:10]+"."+tmp[10:])
    primad = time.time()
    print("T1 - T0 = TEMPO INFERENZA: ", primad - glass_time) # tempo impiegato per ricevere msg mqtt + processing del tempo

    '''
    t2 - t1 
    creazione cam
    '''
    #Ip_address, username, password, lat, lon, cam
    lat = int(str(data["objects"][0]["latitude"]).replace(".", "")[:8])
    lon = int(str(data["objects"][0]["longitude"]).replace(".", "")[:8])
    
    send_cam(lat, lon, schema)
    gencam = time.time()
    print("T2 - T1 = TEMPO INFERENZA: ", gencam - primad, "\n\n") #tempo per generare la stringa json da mandare
    print("T2 - T0 = tempo totale:  ", gencam - glass_time) #tempo totale
    #tempo = str(gencam - glass_time)
    with open('test9.txt','a+') as f:
        f.write(f"{(gencam - glass_time)*1000}\n") 

subscribe.callback(print_msg, "/haura/data", hostname="127.0.0.1")
