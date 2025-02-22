/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_RescueAndRecoveryWorkInProgressSubCauseCode_H_
#define	_RescueAndRecoveryWorkInProgressSubCauseCode_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RescueAndRecoveryWorkInProgressSubCauseCode {
	RescueAndRecoveryWorkInProgressSubCauseCode_unavailable	= 0,
	RescueAndRecoveryWorkInProgressSubCauseCode_emergencyVehicles	= 1,
	RescueAndRecoveryWorkInProgressSubCauseCode_rescueHelicopterLanding	= 2,
	RescueAndRecoveryWorkInProgressSubCauseCode_policeActivityOngoing	= 3,
	RescueAndRecoveryWorkInProgressSubCauseCode_medicalEmergencyOngoing	= 4,
	RescueAndRecoveryWorkInProgressSubCauseCode_childAbductionInProgress	= 5
} e_RescueAndRecoveryWorkInProgressSubCauseCode;

/* RescueAndRecoveryWorkInProgressSubCauseCode */
typedef long	 RescueAndRecoveryWorkInProgressSubCauseCode_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RescueAndRecoveryWorkInProgressSubCauseCode;
asn_struct_free_f RescueAndRecoveryWorkInProgressSubCauseCode_free;
asn_struct_print_f RescueAndRecoveryWorkInProgressSubCauseCode_print;
asn_constr_check_f RescueAndRecoveryWorkInProgressSubCauseCode_constraint;
ber_type_decoder_f RescueAndRecoveryWorkInProgressSubCauseCode_decode_ber;
der_type_encoder_f RescueAndRecoveryWorkInProgressSubCauseCode_encode_der;
xer_type_decoder_f RescueAndRecoveryWorkInProgressSubCauseCode_decode_xer;
xer_type_encoder_f RescueAndRecoveryWorkInProgressSubCauseCode_encode_xer;
oer_type_decoder_f RescueAndRecoveryWorkInProgressSubCauseCode_decode_oer;
oer_type_encoder_f RescueAndRecoveryWorkInProgressSubCauseCode_encode_oer;
per_type_decoder_f RescueAndRecoveryWorkInProgressSubCauseCode_decode_uper;
per_type_encoder_f RescueAndRecoveryWorkInProgressSubCauseCode_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _RescueAndRecoveryWorkInProgressSubCauseCode_H_ */
#include <asn_internal.h>
