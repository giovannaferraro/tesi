/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_ReferencePosition_H_
#define	_ReferencePosition_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Latitude.h"
#include "Longitude.h"
#include "PosConfidenceEllipse.h"
#include "Altitude.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ReferencePosition */
typedef struct ReferencePosition {
	Latitude_t	 latitude;
	Longitude_t	 longitude;
	PosConfidenceEllipse_t	 positionConfidenceEllipse;
	Altitude_t	 altitude;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ReferencePosition_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ReferencePosition;
extern asn_SEQUENCE_specifics_t asn_SPC_ReferencePosition_specs_1;
extern asn_TYPE_member_t asn_MBR_ReferencePosition_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _ReferencePosition_H_ */
#include <asn_internal.h>
