/*\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
  COMMON.H
    the common utilities of all files are saved in this file.
/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\*/

#ifndef _COMMON_H_
#define _COMMON_H_

#include        <stdio.h>
#include        <string.h>
#include	    <stdlib.h>

#include	    <stdarg.h>
#include	    <fcntl.h>
#include        <unistd.h> /* fork() */
#include	    <signal.h>
#include	    <time.h>
#include        <sys/wait.h> /* wait */
#include        <sys/types.h>
#include	    <sys/ioctl.h> /* get local ip */
#include		<assert.h>

#include	    <pthread.h>
#include        <semaphore.h>
#include	    <sys/ipc.h>
#include	    <sys/shm.h>
#include	    <sys/sem.h>
#include	    <sys/msg.h>
#include 	    <sys/time.h>
#include 	    <sys/times.h>
#include	    <sys/param.h>
#include        <sys/socket.h>
#include        <netinet/in.h> /* get local ip */ 
#include	    <net/if.h>     /* get local ip */
#include	    <linux/if_packet.h>
#include 		</usr/include/linux/filter.h>
#include 		<linux/if_ether.h>
#include        <arpa/inet.h> /* inet_addr(), struct sockaddr_in */
#include	    <netdb.h>
#include	    <termio.h>
#include        <malloc.h>
#include        <memory.h>
#include		<pthread.h>

#include        <getopt.h>

typedef unsigned char	BOOL;
typedef short		STATUS;
typedef unsigned char       U8;
typedef U8                  u8;
typedef unsigned short      U16;
typedef U16                 u16;
typedef unsigned int		U32;
typedef U32					u32;					
typedef int		tIPC_ID;

#define _LIT_ENDIAN
#define ETH_MTU		(16*1024)
#define ERROR		-1

typedef enum {
	FALSE,
	TRUE
} MY_BOOL;

#include		"util.h"
#include		"ipc.h"
#include		"ip_codec.h"

typedef struct _T_MAIL {
	char data[ETH_MTU];
	int  type;
	int  evt;
	void *ccb;
	int  who;
} tMAIL;

#endif
