/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_LowFrequencyContainer_H_
#define	_LowFrequencyContainer_H_


#include <asn_application.h>

/* Including external dependencies */
#include "BasicVehicleContainerLowFrequency.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LowFrequencyContainer_PR {
	LowFrequencyContainer_PR_NOTHING,	/* No components present */
	LowFrequencyContainer_PR_basicVehicleContainerLowFrequency
	/* Extensions may appear below */
	
} LowFrequencyContainer_PR;

/* LowFrequencyContainer */
typedef struct LowFrequencyContainer {
	LowFrequencyContainer_PR present;
	union LowFrequencyContainer_u {
		BasicVehicleContainerLowFrequency_t	 basicVehicleContainerLowFrequency;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LowFrequencyContainer_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LowFrequencyContainer;
extern asn_CHOICE_specifics_t asn_SPC_LowFrequencyContainer_specs_1;
extern asn_TYPE_member_t asn_MBR_LowFrequencyContainer_1[1];
extern asn_per_constraints_t asn_PER_type_LowFrequencyContainer_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _LowFrequencyContainer_H_ */
#include <asn_internal.h>
