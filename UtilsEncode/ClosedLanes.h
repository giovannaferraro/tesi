/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_ClosedLanes_H_
#define	_ClosedLanes_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HardShoulderStatus.h"
#include "DrivingLaneStatus.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ClosedLanes */
typedef struct ClosedLanes {
	HardShoulderStatus_t	*innerhardShoulderStatus	/* OPTIONAL */;
	HardShoulderStatus_t	*outerhardShoulderStatus	/* OPTIONAL */;
	DrivingLaneStatus_t	*drivingLaneStatus	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ClosedLanes_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ClosedLanes;
extern asn_SEQUENCE_specifics_t asn_SPC_ClosedLanes_specs_1;
extern asn_TYPE_member_t asn_MBR_ClosedLanes_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _ClosedLanes_H_ */
#include <asn_internal.h>
