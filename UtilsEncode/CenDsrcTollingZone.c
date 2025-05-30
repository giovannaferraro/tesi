/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ITS-Container"
 * 	found in "ITS-Container.asn"
 */

#include "CenDsrcTollingZone.h"

asn_TYPE_member_t asn_MBR_CenDsrcTollingZone_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct CenDsrcTollingZone, protectedZoneLatitude),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Latitude,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"protectedZoneLatitude"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct CenDsrcTollingZone, protectedZoneLongitude),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Longitude,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"protectedZoneLongitude"
		},
	{ ATF_POINTER, 1, offsetof(struct CenDsrcTollingZone, cenDsrcTollingZoneID),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CenDsrcTollingZoneID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cenDsrcTollingZoneID"
		},
};
static const int asn_MAP_CenDsrcTollingZone_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_CenDsrcTollingZone_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_CenDsrcTollingZone_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* protectedZoneLatitude */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* protectedZoneLongitude */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* cenDsrcTollingZoneID */
};
asn_SEQUENCE_specifics_t asn_SPC_CenDsrcTollingZone_specs_1 = {
	sizeof(struct CenDsrcTollingZone),
	offsetof(struct CenDsrcTollingZone, _asn_ctx),
	asn_MAP_CenDsrcTollingZone_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_CenDsrcTollingZone_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_CenDsrcTollingZone = {
	"CenDsrcTollingZone",
	"CenDsrcTollingZone",
	&asn_OP_SEQUENCE,
	asn_DEF_CenDsrcTollingZone_tags_1,
	sizeof(asn_DEF_CenDsrcTollingZone_tags_1)
		/sizeof(asn_DEF_CenDsrcTollingZone_tags_1[0]), /* 1 */
	asn_DEF_CenDsrcTollingZone_tags_1,	/* Same as above */
	sizeof(asn_DEF_CenDsrcTollingZone_tags_1)
		/sizeof(asn_DEF_CenDsrcTollingZone_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_CenDsrcTollingZone_1,
	3,	/* Elements count */
	&asn_SPC_CenDsrcTollingZone_specs_1	/* Additional specs */
};

