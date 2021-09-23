/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
  UTIL.C
  Dennis Tseng
    the common utilities of all files are saved in this file.
/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

#include    "common.h"

/*----------------------------------------------------
 * DECODE_LIT_ENDIAN_U16()
 *---------------------------------------------------*/
U16  DECODE_LIT_ENDIAN_U16(U8 *message)
{
        char  cc[2];

        cc[1] = *message;  cc[0] = *(message+1);
        return *(U16*)cc;
}

/*----------------------------------------------------
 * DECODE_LIT_ENDIAN_U24
 *
 * Note: first incoming byte(biggest) saved in high mem
 *       small value <-> in low memory
 *           large value <-> in high memory
 * -+--+--+       +-------------
 *  |  |a | ----> |  |  |  |a |
 * -+--+--+       +-------------
 *                  0  1  2  3
 *---------------------------------------------------*/
U32  DECODE_LIT_ENDIAN_U24(U8 *message)
{
        char  cc[3];

        cc[2] = *(message+1);
        cc[1] = *(message+2);
        cc[0] = *(message+3);
        return *(U32*)cc;
}

/*----------------------------------------------------
 * DECODE_LIT_ENDIAN_U32()
 *
 * Note: first incoming byte(biggest) saved in high mem
 *       small value <-> in low memory
 *           large value <-> in high memory
 * -+--+--+       +-------------
 *  |  |a | ----> |  |  |  |a |
 * -+--+--+       +-------------
 *                  0  1  2  3
 *---------------------------------------------------*/
U32  DECODE_LIT_ENDIAN_U32(U8 *message)
{
        char  cc[4];

        cc[3] = *message;               cc[2] = *(message+1);
        cc[1] = *(message+2);   cc[0] = *(message+3);
        return *(U32*)cc;
}

/*----------------------------------------------------
 * DECODE_U16 :
 *
 * input  : mp
 * output : val
 *---------------------------------------------------*/
U8  *DECODE_U16(U16 *val, U8 *mp)
{
#       ifdef _BIG_ENDIAN
        *val = *(U16*)mp;
#       else
        *val = DECODE_LIT_ENDIAN_U16(mp);
#       endif

        return (mp+2);
}

/*----------------------------------------------------
 * DECODE_U24 :
 *
 * input  : mp
 * output : val
 *---------------------------------------------------*/
U8  *DECODE_U24(U32 *val, U8 *mp)
{
#       ifdef _BIG_ENDIAN
        *val = *(U32*)mp;
#       else
        *val = DECODE_LIT_ENDIAN_U32(mp);
#       endif

        return (mp+3);
}

/*----------------------------------------------------
 * DECODE_U32()
 *
 * input  : mp
 * output : val
 *---------------------------------------------------*/
U8  *DECODE_U32(U32 *val, U8 *mp)
{
#       ifdef _BIG_ENDIAN
        *val = *(U32*)mp;
#       else
        *val = DECODE_LIT_ENDIAN_U32(mp);
#       endif

        return (mp+4);
}

/*----------------------------------------------------
 * ENCODE_LIT_ENDIAN_U16
 *---------------------------------------------------*/
void ENCODE_LIT_ENDIAN_U16(U16 val, U8 *mp)
{
        U8 *cp=(U8*)&val;

        *mp++ = *(cp+1); /* biggest value will be put in the outgoing beginning addr */
        *mp = *cp;
}

/*---------------------------------------------------------------------
 * ENCODE_LIT_ENDIAN_U24
 *
 * Note: first outgoing byte(biggest) retrieved from lowest
 *       i.e. sent from high memory which used to save biggest value.
 *---------------------------------------------------------------------*/
void ENCODE_LIT_ENDIAN_U24(U32 val, U8 *mp)
{
        U8 *cp=(U8*)&val;

        *mp++ = *(cp+2); /* biggest value will be put in the outgoing beginning addr */
        *mp++ = *(cp+1);
        *mp = *cp;
}

/*----------------------------------------------------------------------
 * ENCODE_LIT_ENDIAN_U32
 *
 * Note: first outgoing byte(biggest) retrieved from lowest
 *       i.e. sent from high memory which used to save biggest value.
 *---------------------------------------------------------------------*/
void ENCODE_LIT_ENDIAN_U32(U32 val, U8 *mp)
{
        U8 *cp=(U8*)&val;

        *mp++ = *(cp+3); /* biggest value will be put in the outgoing beginning addr */
        *mp++ = *(cp+2);
        *mp++ = *(cp+1);
        *mp = *cp;
}

/*----------------------------------------------------
 * ENCODE_U16
 *
 * input  : val
 * output : mp
 *---------------------------------------------------*/
U8 *ENCODE_U16(U8 *mp, U16 val)
{
#       ifdef _BIG_ENDIAN
        *(U16*)mp = val;
#       else
        ENCODE_LIT_ENDIAN_U16(val,mp);
#       endif

        return (mp+2);
}

/*----------------------------------------------------
 * ENCODE_U24
 *
 * input  : val
 * output : mp
 *---------------------------------------------------*/
U8 *ENCODE_U24(U8 *mp, U32 val)
{
#       ifdef _BIG_ENDIAN
        *(U32*)mp = val;
#       else
        ENCODE_LIT_ENDIAN_U24(val,mp);
#       endif

        return (mp+3);
}

/*----------------------------------------------------
 * ENCODE_U32
 *
 * input  : val
 * output : mp
 *---------------------------------------------------*/
U8 *ENCODE_U32(U8 *mp, U32 val)
{
#       ifdef _BIG_ENDIAN
        *(U32*)mp = val;
#       else
        ENCODE_LIT_ENDIAN_U32(val,mp);
#       endif

        return (mp+4);
}

/*-----------------------------------------------
 * ADD_CARRY_FOR_CHKSUM
 *
 *----------------------------------------------*/
U16 ADD_CARRY_FOR_CHKSUM(U32 sum)
{
    U32  value;
    U8   carry;

    carry = (U8)(sum >> 16); //get carry
    value = sum & 0x0000ffff;
    sum = carry + value;

    carry = (U8)(sum >> 16);
    sum += carry;

    return sum;
}

/*-----------------------------------------------
 * CHECK_SUM
 *
 *----------------------------------------------*/
U16 CHECK_SUM(U32 sum)
{
    U32  value;
    U8   carry;

    carry = (U8)(sum >> 16); //get carry
    value = sum & 0x0000ffff;
    sum = carry + value;

    carry = (U8)(sum >> 16);
    sum += carry;

    return (U16)~sum;
}

/*------------------------------------------------------------
 * get_local_mac:
 *-----------------------------------------------------------*/
int get_local_mac(U8 *mac, char *sif)
{
        struct ifreq    sifreq; //socket Interface request
        int                     fd;

        fd = socket(PF_INET,SOCK_STREAM,0);
        if (fd < 0){
                printf("error! can not open socket when getting mac\n");
                return -1;
        }

        strncpy(sifreq.ifr_name, sif, IF_NAMESIZE);
        if (ioctl(fd, SIOCGIFHWADDR, &sifreq) != 0){
                printf("error! ioctl failed when getting mac\n");
                close(fd);
                return -1;
        }
        memmove((void*)&mac[0], (void*)&sifreq.ifr_ifru.ifru_hwaddr.sa_data[0], 6);
        return 0;
}

/********************************************************************
 * PRINT_MESSAGE()
 *
 ********************************************************************/
void  PRINT_MESSAGE(unsigned char *msg, int len)
{
	int  row_cnt,rows,rest_bytes,hex_cnt,ch_cnt,cnt,xi,ci;
	
	if (NULL == msg){
		printf("PRINT_MESSAGE(): NULL message ?\n");
		return;
	}
	
	/*if ((len*5) > 2048){ // 5 format bytes for one raw data byte
		printf("Too large[len(%d) > max(%d)] to print out!\n",len,2048);
		return;
	}*/
	
	rest_bytes = len % 16;
	rows = len / 16;
	ci = xi = 0;
	
	for(row_cnt=0; row_cnt<rows; row_cnt++){
		/*------------- print label for each row --------------*/
		printf("%04x:  ",(row_cnt+1)<<4);
		
		/*------------- print hex-part --------------*/
		for(hex_cnt=1; hex_cnt<=8; hex_cnt++){
		    if (hex_cnt < 8)
		        printf("%02x ",msg[xi++]); /* Must be unsigned, otherwise garbage displayed */
		    else
		        printf("%02x",msg[xi++]); /* Must be unsigned, otherwise garbage displayed */
		}
		
		/* delimiters space for each 8's Hex char */
		printf("  ");
		
		for(hex_cnt=9; hex_cnt<=16; hex_cnt++){
		    if (hex_cnt < 16)
		        printf("%02x ",msg[xi++]);
		    else
		        printf("%02x",msg[xi++]);
		}
		
		/* delimiters space bet. Hex and Character row */
		printf("    ");
		
		/*------------- print character-part --------------*/
		for(ch_cnt=1; ch_cnt<=16; ch_cnt++,ci++){
			if (msg[ci]>0x20 && msg[ci]<=0x7e){
		    	printf("%c",msg[ci]);
		    }
		    else{
		    	printf(".");
			}
		}
		printf("\n");
	} //for
	
	/*================ print the rest bytes(hex & char) ==================*/
	if (rest_bytes == 0) {
		printf("\n");
		return;
	}
	
	/*------------- print label for last row --------------*/
	printf("%04x:  ",(row_cnt+1)<<4);
		
	/*------------- print hex-part(rest) --------------*/
	if (rest_bytes < 8){
	    for(hex_cnt=1; hex_cnt<=rest_bytes; hex_cnt++){
	        printf("%02x ",msg[xi++]);
	    }
	
	    /* fill in the space for 16's Hex-part alignment */
	    for(cnt=rest_bytes+1; cnt<=8; cnt++){ /* from rest_bytes+1 to 8 */
	        if (cnt < 8)
	            printf("   ");
	        else
	            printf("  ");
	    }
	
	    /* delimiters bet. hex and char */
	    printf("  ");
	
	    for(cnt=9; cnt<=16; cnt++){
	        if (cnt < 16)
	            printf("   ");
	        else
	            printf("  ");
	    }
	    printf("    ");
	}
	else if (rest_bytes == 8){
	    for(hex_cnt=1; hex_cnt<=rest_bytes; hex_cnt++){
	        if (hex_cnt < 8)
	            printf("%02x ",msg[xi++]);
	        else
	            printf("%02x",msg[xi++]);
	    }
	    printf("  ");
	
	    for(cnt=9; cnt<=16; cnt++){
	        if (cnt < 16)
	            printf("   ");
	        else
	            printf("  ");
	    }
	    printf("    ");
	}
	else{ /* rest_bytes > 8 */
	    for(hex_cnt=1; hex_cnt<=8; hex_cnt++){
	        if (hex_cnt < 8)
	            printf("%02x ",msg[xi++]);
	        else
	            printf("%02x",msg[xi++]);
	    }
	
	    /* delimiters space for each 8's Hex char */
	    printf("  ");
	
	    for(hex_cnt=9; hex_cnt<=rest_bytes; hex_cnt++){ /* 9 - rest_bytes */
	        if (hex_cnt < 16)
	            printf("%02x ",msg[xi++]);
	        else
	            printf("%02x",msg[xi++]);
	    }
	
	    for(cnt=rest_bytes+1; cnt<=16; cnt++){
	        if (cnt < 16)
	            printf("   ");
	        else
	            printf("  ");
	    }
	    /* delimiters space bet. Hex and Character row */
	    printf("    ");
	} /* else */
	
	/*------------- print character-part --------------*/
	for(ch_cnt=1; ch_cnt<=rest_bytes; ch_cnt++,ci++){
		if (msg[ci]>0x20 && msg[ci]<=0x7e){
	        printf("%c",msg[ci]);
	    }
	    else
	        printf(".");
	}
	printf("\n");
}
