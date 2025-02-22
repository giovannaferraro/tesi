/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_ItsPduHeader_H_
#define	_ItsPduHeader_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include "StationID.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum messageID {
	messageID_denm	= 1,
	messageID_cam	= 2,
	messageID_poi	= 3,
	messageID_spatem	= 4,
	messageID_mapem	= 5,
	messageID_ivim	= 6,
	messageID_ev_rsr	= 7,
	messageID_tistpgtransaction	= 8,
	messageID_srem	= 9,
	messageID_ssem	= 10,
	messageID_evcsn	= 11,
	messageID_saem	= 12,
	messageID_rtcmem	= 13
} e_messageID;

/* ItsPduHeader */
typedef struct ItsPduHeader {
	long	 protocolVersion;
	long	 messageID;
	StationID_t	 stationID;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ItsPduHeader_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ItsPduHeader;
extern asn_SEQUENCE_specifics_t asn_SPC_ItsPduHeader_specs_1;
extern asn_TYPE_member_t asn_MBR_ItsPduHeader_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _ItsPduHeader_H_ */
#include <asn_internal.h>
