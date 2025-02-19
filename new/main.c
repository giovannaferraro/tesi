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


//int main(int ac, char **av) {
//    char buf[1024];
//    asn_dec_rval_t rval;
//    MyTypes_t *tipo = 0;
//    FILE *fp;
//    size_t size;
//    char *filename;
//
//    if (ac != 2){
//        fprintf(stderr, "usare: %s <file>\n", av[0]);
//        exit(1);
//    } else {
//		printf("SIAMO QUA DENTRO");
//        filename = av[1];
//    }
//
//    
//}