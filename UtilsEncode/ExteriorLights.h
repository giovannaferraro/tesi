/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_ExteriorLights_H_
#define	_ExteriorLights_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ExteriorLights {
	ExteriorLights_lowBeamHeadlightsOn	= 0,
	ExteriorLights_highBeamHeadlightsOn	= 1,
	ExteriorLights_leftTurnSignalOn	= 2,
	ExteriorLights_rightTurnSignalOn	= 3,
	ExteriorLights_daytimeRunningLightsOn	= 4,
	ExteriorLights_reverseLightOn	= 5,
	ExteriorLights_fogLightOn	= 6,
	ExteriorLights_parkingLightsOn	= 7
} e_ExteriorLights;

/* ExteriorLights */
typedef BIT_STRING_t	 ExteriorLights_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ExteriorLights_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ExteriorLights;
asn_struct_free_f ExteriorLights_free;
asn_struct_print_f ExteriorLights_print;
asn_constr_check_f ExteriorLights_constraint;
ber_type_decoder_f ExteriorLights_decode_ber;
der_type_encoder_f ExteriorLights_encode_der;
xer_type_decoder_f ExteriorLights_decode_xer;
xer_type_encoder_f ExteriorLights_encode_xer;
oer_type_decoder_f ExteriorLights_decode_oer;
oer_type_encoder_f ExteriorLights_encode_oer;
per_type_decoder_f ExteriorLights_decode_uper;
per_type_encoder_f ExteriorLights_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ExteriorLights_H_ */
#include <asn_internal.h>
