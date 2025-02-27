import asn1tools as asn
import os, subprocess,time


def encode(dict):
  cam = asn.compile_files('ITS-Container.asn','uper')
  cam_bytes = cam.encode('CAM', dict)
  return cam_bytes.hex()

dict_to_send = {'header': {'protocolVersion': 2, 'messageID': 2, 'stationID': 10},
                 'cam': {'generationDeltaTime': 10000, 
                  'camParameters':
                          {'basicContainer': 
                            {'stationType': 5, 'referencePosition': {'latitude': 449224306, 'longitude': 109968809,
                            'positionConfidenceEllipse': {'semiMajorConfidence': 282, 'semiMinorConfidence': 280, 'semiMajorOrientation': 1138},
                            'altitude': {'altitudeValue': 6050, 'altitudeConfidence': 'alt-020-00'}}
                            }, 
                            'highFrequencyContainer': ('basicVehicleContainerHighFrequency', 
                          {
                            'heading': {'headingValue': 62, 'headingConfidence': 8}, 
                            'speed': {'speedValue': 1163, 'speedConfidence': 4}, 
                            'driveDirection': 'forward', 
                            'vehicleLength': {'vehicleLengthValue': 42, 'vehicleLengthConfidenceIndication': 'trailerPresenceIsUnknown'}, 
                            'vehicleWidth': 18,
                            'longitudinalAcceleration': {'longitudinalAccelerationValue': -2, 'longitudinalAccelerationConfidence': 102},
                              'curvature': {'curvatureValue': 386, 'curvatureConfidence': 'onePerMeter-0-01'}, 
                              'curvatureCalculationMode': 'yawRateUsed', 
                              'yawRate': {'yawRateValue': 2354, 'yawRateConfidence': 'unavailable'}, 
                              'accelerationControl': (b'@', 7), 
                              'steeringWheelAngle': {'steeringWheelAngleValue': 57, 'steeringWheelAngleConfidence': 1}, 
                              'lateralAcceleration': {'lateralAccelerationValue': 43, 'lateralAccelerationConfidence': 102}
                          }
                          )
                          }
                        }
                }

uper_string = encode(dict_to_send)
print(uper_string)
#print("uper string type: ",type(uper_string))


#print("convert to bytes")
uper_bytes = bytes.fromhex(uper_string)
