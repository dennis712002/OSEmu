#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "aes.h"
#include "des.h"
#include "md5.h"

#ifndef uchar
typedef unsigned char uchar;
#endif

#define MAX_ECM_SIZE 512

//ECM rc codes:
#define E_FOUND         0
///////above is all found
#define E_NOTFOUND  4  //for selection of found, use < E_NOTFOUND
#define E_FAKE          7
#define E_INVALID       8
#define E_STOPPED       13 //for selection of error, use <= E_STOPPED and exclude selection of found
///////above is all notfound, some error or problem
#define E_UNHANDLED 100 //for selection of unhandled, use >= E_UNHANDLED


extern int8_t debuglog;
extern int8_t havelogfile;
extern char*  logfile;
extern int bg;

struct aes_keys {
	AES_KEY			aeskey_encrypt;		// encryption key needed by monitor and used by camd33, camd35
	AES_KEY			aeskey_decrypt;		// decryption key needed by monitor and used by camd33, camd35
};

typedef struct ecm_request_t {
	uchar			cw[16];
	int16_t			ecmlen;
	uint16_t		caid;
	uint16_t		srvid;
	uint32_t		prid;
	int8_t			rc;
} ECM_REQUEST;
