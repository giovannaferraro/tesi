/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#ifndef	_VehicleMass_H_
#define	_VehicleMass_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum VehicleMass {
	VehicleMass_hundredKg	= 1,
	VehicleMass_unavailable	= 1024
} e_VehicleMass;

/* VehicleMass */
typedef long	 VehicleMass_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehicleMass;
asn_struct_free_f VehicleMass_free;
asn_struct_print_f VehicleMass_print;
asn_constr_check_f VehicleMass_constraint;
ber_type_decoder_f VehicleMass_decode_ber;
der_type_encoder_f VehicleMass_encode_der;
xer_type_decoder_f VehicleMass_decode_xer;
xer_type_encoder_f VehicleMass_encode_xer;
oer_type_decoder_f VehicleMass_decode_oer;
oer_type_encoder_f VehicleMass_encode_oer;
per_type_decoder_f VehicleMass_decode_uper;
per_type_encoder_f VehicleMass_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _VehicleMass_H_ */
#include <asn_internal.h>
