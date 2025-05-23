/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_SignalViolationSubCauseCode_H_
#define	_SignalViolationSubCauseCode_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SignalViolationSubCauseCode {
	SignalViolationSubCauseCode_unavailable	= 0,
	SignalViolationSubCauseCode_stopSignViolation	= 1,
	SignalViolationSubCauseCode_trafficLightViolation	= 2,
	SignalViolationSubCauseCode_turningRegulationViolation	= 3
} e_SignalViolationSubCauseCode;

/* SignalViolationSubCauseCode */
typedef long	 SignalViolationSubCauseCode_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SignalViolationSubCauseCode;
asn_struct_free_f SignalViolationSubCauseCode_free;
asn_struct_print_f SignalViolationSubCauseCode_print;
asn_constr_check_f SignalViolationSubCauseCode_constraint;
ber_type_decoder_f SignalViolationSubCauseCode_decode_ber;
der_type_encoder_f SignalViolationSubCauseCode_encode_der;
xer_type_decoder_f SignalViolationSubCauseCode_decode_xer;
xer_type_encoder_f SignalViolationSubCauseCode_encode_xer;
oer_type_decoder_f SignalViolationSubCauseCode_decode_oer;
oer_type_encoder_f SignalViolationSubCauseCode_encode_oer;
per_type_decoder_f SignalViolationSubCauseCode_decode_uper;
per_type_encoder_f SignalViolationSubCauseCode_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _SignalViolationSubCauseCode_H_ */
#include <asn_internal.h>
