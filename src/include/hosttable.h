
/*
 * Licensed Materials - Property of IBM
 *
 * trousers - An open source TCG Software Stack
 *
 * (C) Copyright International Business Machines Corp. 2004-2006
 *
 */

#ifndef _HOSTTABLE_H_
#define _HOSTTABLE_H_

#include "rpc_tcstp.h"
#include "threads.h"


#define CONNECTION_TYPE_TCP_PERSISTANT	1

struct host_table_entry {
	struct host_table_entry *next;
	TCS_CONTEXT_HANDLE tcsContext;
	BYTE *hostname;
	int type;
	int socket;
	struct tcsd_comm_data comm;
	MUTEX_DECLARE(lock);
};

struct host_table {
	struct host_table_entry *entries;
	MUTEX_DECLARE(lock);
};

extern struct host_table *ht;
struct host_table_entry *get_table_entry(TCS_CONTEXT_HANDLE);
void put_table_entry(struct host_table_entry *);
TSS_RESULT add_table_entry(struct host_table_entry *, TCS_CONTEXT_HANDLE);
void remove_table_entry(TCS_CONTEXT_HANDLE);


#endif
