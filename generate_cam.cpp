'''
parte da un dizionario che riempie con lat, lon e genera la stringa di encoding UPER in c++
'''

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string generate_cam(double lat, double lon, const std::string& cam) {
    json dict_to_send = {
        {"header", {
            {"protocolVersion", 2},
            {"messageID", 2},
            {"stationID", 10}
        }},
        {"cam", {
            {"generationDeltaTime", 12345},
            {"camParameters", {
                {"basicContainer", {
                    {"stationType", 5},
                    {"referencePosition", {
                        {"latitude", lat},
                        {"longitude", lon},
                        {"positionConfidenceEllipse", {
                            {"semiMajorConfidence", 282},
                            {"semiMinorConfidence", 280},
                            {"semiMajorOrientation", 1138}
                        }},
                        {"altitude", {
                            {"altitudeValue", 6050},
                            {"altitudeConfidence", "alt-020-00"}
                        }}
                    }},
                    {"highFrequencyContainer", {
                        {"basicVehicleContainerHighFrequency", {
                            {"heading", {
                                {"headingValue", 62},
                                {"headingConfidence", 8}
                            }},
                            {"speed", {
                                {"speedValue", 1163},
                                {"speedConfidence", 4}
                            }},
                            {"driveDirection", "forward"},
                            {"vehicleLength", {
                                {"vehicleLengthValue", 42},
                                {"vehicleLengthConfidenceIndication", "trailerPresenceIsUnknown"}
                            }},
                            {"vehicleWidth", 18},
                            {"longitudinalAcceleration", {
                                {"longitudinalAccelerationValue", -2},
                                {"longitudinalAccelerationConfidence", 102}
                            }},
                            {"curvature", {
                                {"curvatureValue", 386},
                                {"curvatureConfidence", "onePerMeter-0-01"}
                            }},
                            {"curvatureCalculationMode", "yawRateUsed"},
                            {"yawRate", {
                                {"yawRateValue", 2354},
                                {"yawRateConfidence", "unavailable"}
                            }},
                            {"accelerationControl", {"@": "b", "7": 7}},
                            {"steeringWheelAngle", {
                                {"steeringWheelAngleValue", 57},
                                {"steeringWheelAngleConfidence", 1}
                            }},
                            {"lateralAcceleration", {
                                {"lateralAccelerationValue", 43},
                                {"lateralAccelerationConfidence", 102}
                            }}
                        }}
                    }}
                }}
            }}
        }}
    };

    // Replace this with your actual encoding function using the 'cam' parameter
    std::string messagebody = encode(dict_to_send, cam);

    return messagebody;
}