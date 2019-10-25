#ifndef __SENSETYPE_H__
#define __SENSETYPE_H__

#ifdef _WIN32
#pragma pack(push, 1)
#endif

#define IO_PACKAGE_HEADER_SIZE 2 //IO package header length:tag+len
#define MAX_IO_DATA_SIZE	0xf8 // maximum IO data size

#define MAX_BUFF_SIZE  0xf0      //maximum buffer size

/* command group definition */
#define CMD_UPDATE		0x01
#define CMD_READ		0x02
#define CMD_CALC_SHA1   0x04

/* common error code. */
#define ERR_SUCCESS				0x00	// success
#define ERR_SES					0x80	// SES function execution error
#define ERR_INVALID_PARAMETER	0x81	// invalid parameter

/* user-specific data block */
typedef struct _FILE_OP_BLOCK
{
	unsigned short fid;     // objective file ID
	unsigned short offset;  // operating offset
	unsigned char len; 	    // buffer length(update)
	// read length(read)
	unsigned char buff[MAX_BUFF_SIZE];
} FILE_OP_BLOCK;

/* IO package */
typedef struct _IO_PACKAGE
{
	unsigned char tag;
	unsigned char len;
	unsigned char buff[MAX_IO_DATA_SIZE];
} IO_PACKAGE;

#ifdef _WIN32
#pragma pack(pop)
#endif


#endif
