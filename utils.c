#include "utils.h"

static size_t buf_offset;

// Helper function to create and initialize a CAM message
CAM_t* create_cam_message(int lat, int lon) {
    CAM_t* cam = (CAM_t*)calloc(1, sizeof(CAM_t));
    if (!cam) return NULL;

    // Initialize header
    cam->header.protocolVersion = 2;
    cam->header.messageID = 2;  // CAM message ID
    cam->header.stationID = 10;

    // Initialize generation delta time (current time)
    cam->cam.generationDeltaTime = 10000;

    // Initialize basic container
    cam->cam.camParameters.basicContainer.stationType = 5;  // passengerCar
    
    // Set reference position
    cam->cam.camParameters.basicContainer.referencePosition.latitude = lat;
    cam->cam.camParameters.basicContainer.referencePosition.longitude = lon;
    cam->cam.camParameters.basicContainer.referencePosition.positionConfidenceEllipse.semiMajorConfidence = 282;
    cam->cam.camParameters.basicContainer.referencePosition.positionConfidenceEllipse.semiMinorConfidence = 280;
    cam->cam.camParameters.basicContainer.referencePosition.positionConfidenceEllipse.semiMajorOrientation = 1138;
    cam->cam.camParameters.basicContainer.referencePosition.altitude.altitudeValue = 6050;
    cam->cam.camParameters.basicContainer.referencePosition.altitude.altitudeConfidence = AltitudeConfidence_alt_020_00;

    // Initialize high frequency container
    cam->cam.camParameters.highFrequencyContainer.present = HighFrequencyContainer_PR_basicVehicleContainerHighFrequency;
    BasicVehicleContainerHighFrequency_t* highFreq = &cam->cam.camParameters.highFrequencyContainer.choice.basicVehicleContainerHighFrequency;

    // Set high-frequency parameters
    highFreq->heading.headingValue = 62;
    highFreq->heading.headingConfidence = 8;
    highFreq->speed.speedValue = 1163;
    highFreq->speed.speedConfidence = 4;
    highFreq->driveDirection = DriveDirection_forward;
    highFreq->vehicleLength.vehicleLengthValue = 42;
    highFreq->vehicleLength.vehicleLengthConfidenceIndication = VehicleLengthConfidenceIndication_trailerPresenceIsUnknown;
    highFreq->vehicleWidth = 18;
    highFreq->longitudinalAcceleration.longitudinalAccelerationValue = -2;
    highFreq->longitudinalAcceleration.longitudinalAccelerationConfidence = 102;
    highFreq->curvature.curvatureValue = 386;
    highFreq->curvature.curvatureConfidence = CurvatureConfidence_onePerMeter_0_01;
    highFreq->curvatureCalculationMode = CurvatureCalculationMode_yawRateUsed;
    highFreq->yawRate.yawRateValue = 2354;
    highFreq->yawRate.yawRateConfidence = YawRateConfidence_unavailable;

    // Set acceleration control
    uint8_t accelControl = 0x40;
    highFreq->accelerationControl = (AccelerationControl_t*)calloc(1, sizeof(AccelerationControl_t));
    highFreq->accelerationControl->buf = (uint8_t*)calloc(1, sizeof(uint8_t));
    highFreq->accelerationControl->buf[0] = accelControl;
    highFreq->accelerationControl->size = 1;
    highFreq->accelerationControl->bits_unused = 1;

    // Set steering wheel angle
    highFreq->steeringWheelAngle = (SteeringWheelAngle_t*)calloc(1, sizeof(SteeringWheelAngle_t));
    highFreq->steeringWheelAngle->steeringWheelAngleValue = 57;
    highFreq->steeringWheelAngle->steeringWheelAngleConfidence = 1;

    // Set lateral acceleration
    highFreq->lateralAcceleration = (LateralAcceleration_t*)calloc(1, sizeof(LateralAcceleration_t));
    highFreq->lateralAcceleration->lateralAccelerationValue = 43;
    highFreq->lateralAcceleration->lateralAccelerationConfidence = 102;
    
    return cam;
}

ritorno encode_cam_message(const CAM_t* cam) {
    asn_enc_rval_t er;
    ritorno ritorno;
    asn_encode_to_new_buffer_result_t res;
    
    int encoding = ATS_UNALIGNED_CANONICAL_PER;

    res = asn_encode_to_new_buffer(0, encoding, &asn_DEF_CAM, cam);
    if(res.result.encoded == -1){
        fprintf(stderr, "Could not encode Rectangle (at %s)\n",
        er.failed_type ? er.failed_type->name : "unknown");
        ritorno.r = res;
        ritorno.b = false;
    } else {
        //if(res.buffer){
        //    char stringa_uper[res.result.encoded];
        //    for(size_t i=0; i<res.result.encoded; i++){
        //        snprintf(&stringa_uper[i], res.result.encoded, "%02x", (char *)res.buffer);
        //        printf("%02x", ((char *)res.buffer)[i]);
        //    }
        //}
        ritorno.r = res;
        ritorno.b = true;
        }

    return ritorno;  
}

void bin_to_hex(const unsigned char *bin, size_t bin_len, char **hex_str) {
    *hex_str = malloc(bin_len * 2 + 1); // Allocate memory for hex string (2 chars per byte + 1 for null terminator)
    
    for (size_t i = 0; i < bin_len; i++) {
        sprintf(*hex_str + (i * 2), "%02x", bin[i]); // Convert each byte to 2 hex characters
    }
    (*hex_str)[bin_len * 2] = '\0'; // Null-terminate the string
}

void process_hex_string(const char *hex_str) {
    printf("Received hex string: %s\n", hex_str);
}
