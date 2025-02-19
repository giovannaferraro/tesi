#include <stdio.h>	/* for stdout */
#include <stdlib.h>	/* for malloc() */
#include <assert.h>	/* for run-time control */
#include "CAM.h"	/* Include MyTypes definition */

static int save_to_file(const void *data, size_t size, void *key) {
    FILE *fp = key;
    return (fwrite(data, 1, size, fp) == size) ? 0 : 1;
}

static int write_out(const void *buffer, size_t size, void *app_key) {
	FILE *out_fp = app_key;
	size_t wrote = fwrite(buffer, 1, size, out_fp);
	return (wrote == size) ? 0 : 1;
}

static unsigned char buf[4096];
static size_t buf_offset;


int main(int ac, char **av) {
	/* Define an OBJECT IDENTIFIER value */
	int oid = 1;

	CAM_t *myType;
	myType = calloc(1, sizeof *myType);
	assert(myType);	/* Assume infinite memory */

	myType->protocolVersion = 124;
    myType->subCauseCodeType = 872;

    asn_enc_rval_t er;
	const char *filename = av[1];
	FILE *fp = fopen(filename, "w"); /* for BER output */
	if(!fp) {
		perror(filename);
		exit(1);
	}
	er = asn_encode_to_buffer(0,ATS_UNALIGNED_CANONICAL_PER,&asn_DEF_CAM,myType,buf,sizeof(buf));
	
	if(er.encoded == -1) {
	fprintf(stderr, "Could not encode Rectangle (at %s)\n",
	er.failed_type ? er.failed_type->name : "unknown");
	exit(1);
	} else {
	for(size_t i = 0; i < sizeof(buf); i++){
		if(buf[i] == 0){
			break;
		}
		printf("%x \n", buf[i]);
	}
	fprintf(stderr, "Created %hhn with UPER encoded Rectangle\n", buf);
	asn_fprint(stdout, &asn_DEF_CAM, myType);
	}

	//fp = fopen(filename, "r");
	//if(!fp) {
	//	perror(filename);
	//	exit(1);
	//}
//
	//size_t size = fread(buf, 1, sizeof(buf), fp);
	//fclose(fp);
	//if(!size) {
	//	fprintf(stderr, "%s: Empty or broken\n", filename);
	//	exit(1);
	//}
//
	//rval = asn_decode(0, ATS_UNALIGNED_CANONICAL_PER, &asn_DEF_MyTypes, (void **)&tipo, buf, size);
	//if(rval.code != RC_OK) {
	//	fprintf(stderr,"”%s: Broken Rectangle encoding at byte %ld\n", filename, (long)rval.consumed);
	//	exit(1);
	//}
	///* Print the decoded Rectangle type as XML */
	//asn_fprint(stdout, &asn_DEF_MyTypes, tipo);
	
}


