#include <stdio.h>	/* for stdout */
#include <stdlib.h>	/* for malloc() */
#include <assert.h>	/* for run-time control */
#include "MyTypes.h"	/* Include MyTypes definition */


static int save_to_file(const void *data, size_t size, void *key) {
    FILE *fp = key;
    return (fwrite(data, 1, size, fp) == size) ? 0 : 1;
}

/* Write the encoded output into some FILE stream. */
static int write_out(const void *buffer, size_t size, void *app_key) {
	FILE *out_fp = app_key;
	size_t wrote = fwrite(buffer, 1, size, out_fp);
	return (wrote == size) ? 0 : 1;
}

static unsigned char buf[4096];
static size_t buf_offset;


int main(int ac, char **av) {
	/* Define an OBJECT IDENTIFIER value */
	int oid[] = { 1, 3, 6, 1, 4, 1, 9363, 1, 5, 0, 1, 3, 6, 1, 4, 1, 9363, 1, 5, 0, 1, 3, 6, 1, 4, 1, 9363, 1, 5, 0}; /* or whatever */

	/* Declare a pointer to a new instance of MyTypes type */
	MyTypes_t *myType;
	/* Declare a pointer to a MyInt type */
	MyInt_t *myInt;

	/* Temporary return value */
	int ret;

	/* Allocate an instance of MyTypes */
	myType = calloc(1, sizeof *myType);
	assert(myType);	/* Assume infinite memory */

	/*
	 * Fill in myObjectId
	 */
	ret = OBJECT_IDENTIFIER_set_arcs(&myType->myObjectId,
			oid, sizeof(oid) / sizeof(oid[0]));
	assert(ret == 0);

	
    
	/*
	 * Fill in myBitString
	 */

	/* Allocate some space for bitmask */
	myType->myBitString.buf = calloc(1, 1);
	assert(myType->myBitString.buf);
	myType->myBitString.size = 1;	/* 1 byte */

	/* Set the value of muxToken */
	myType->myBitString.buf[0] |= 1 << (7 - myBitString_muxToken);

	/* Also set the value of modemToken */
	myType->myBitString.buf[0] |= 1 << (7 - myBitString_modemToken);

	/* Trim unused bits (optional) */
	myType->myBitString.bits_unused = 6;

	/*
	 * Print the resulting structure as XER (XML)
	 */
	//xer_fprint(stdout, &asn_DEF_MyTypes, myType);
    //xer_fprint(stdout, &asn_DEF_MyTypes, myType);
    //asn_fprint(stdout, &asn_DEF_MyTypes, myType);


    //fp = fopen("prova.txt",'w');
    asn_enc_rval_t er;
	const char *filename = av[1];
	FILE *fp = fopen(filename, "w"); /* for BER output */
	if(!fp) {
		perror(filename);
		exit(1);
	}
    //er = xer_encode(&asn_DEF_MyTypes,myType,XER_F_CANONICAL,save_to_file,fp);
	er = asn_encode_to_buffer(0,ATS_UNALIGNED_CANONICAL_PER,&asn_DEF_MyTypes,myType,buf,sizeof(buf));
	

	if(er.encoded == -1) {
	fprintf(stderr, "Could not encode Rectangle (at %s)\n",
	er.failed_type ? er.failed_type->name : "unknown");
	exit(1);
	} else {
	unsigned char* p = (unsigned char*)&buf;
    printf("%x \n", p[0]); // outputs the first byte of `foo`. stampa un hex quindi 16 bit, due byte
    printf("%x \n", p[1]); // outputs the second byte of `foo`
	printf("%x \n", p[2]); // outputs the first byte of `foo`. stampa un hex quindi 16 bit, due byte
    printf("%x \n", p[3]); // outputs the second byte of `foo`
	printf("%x \n", p[4]); // outputs the first byte of `foo`. stampa un hex quindi 16 bit, due byte
    printf("%x \n", p[5]); // outputs the second byte of `foo`
	printf("%x\n", p[6]); // outputs the first byte of `foo`. stampa un hex quindi 16 bit, due byte
    printf("%x\n", p[7]); // outputs the second byte of `foo`
	fprintf(stderr, "Created %hhn with BER encoded Rectangle\n", buf);
	fwrite(p,1,sizeof(p),fp);
	printf("len of p: %ld", sizeof(p));
	}


	fp = fopen(filename, "r");
	if(!fp) {
		perror(filename);
		exit(1);
	}

	size_t size = fread(buf, 1, sizeof(buf), fp);
	fclose(fp);
	if(!size) {
		fprintf(stderr, "%s: Empty or broken\n", filename);
		exit(1);
	}

	rval = asn_decode(0, ATS_UNALIGNED_CANONICAL_PER, &asn_DEF_MyTypes, (void **)&tipo, buf, size);
	if(rval.code != RC_OK) {
		fprintf(stderr,"”%s: Broken Rectangle encoding at byte %ld\n", filename, (long)rval.consumed);
		exit(1);
	}
	/* Print the decoded Rectangle type as XML */
	asn_fprint(stdout, &asn_DEF_MyTypes, tipo);
	


    
	
}


