
/*
 * Licensed Materials - Property of IBM
 *
 * trousers - An open source TCG Software Stack
 *
 * (C) Copyright International Business Machines Corp. 2004-2006
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <netdb.h>

#include "trousers/tss.h"
#include "spi_internal_types.h"
#include "tcs_tsp.h"
#include "tcs_utils.h"
#include "tcs_int_literals.h"
#include "capabilities.h"
#include "tcslog.h"
#include "tcsd_wrap.h"
#include "tcsd.h"
#include "tcs_utils.h"
#include "rpc_tcstp_tcs.h"


TSS_RESULT
tcs_wrap_PhysicalSetDeactivated(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_BOOL state;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_BOOL, 1, &state, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_PhysicalSetDeactivated_Internal(hContext, state);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_DisableOwnerClear(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;
	TPM_AUTH auth;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_AUTH, 1, &auth, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_DisableOwnerClear_Internal(hContext, &auth);

	MUTEX_UNLOCK(tcsp_lock);

	if (result == TSS_SUCCESS) {
		initData(&data->comm, 1);
		if (setData(TCSD_PACKET_TYPE_AUTH, 0, &auth, 0, &data->comm)) {
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
	} else
		initData(&data->comm, 0);

	data->comm.hdr.u.result = result;
	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_ForceClear(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_ForceClear_Internal(hContext);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_DisableForceClear(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_DisableForceClear_Internal(hContext);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_PhysicalEnable(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_PhysicalEnable_Internal(hContext);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_SetOwnerInstall(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_BOOL state;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_BOOL, 1, &state, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_SetOwnerInstall_Internal(hContext, state);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_OwnerSetDisable(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_BOOL disableState;
	TPM_AUTH ownerAuth;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_BOOL, 1, &disableState, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	if (getData(TCSD_PACKET_TYPE_AUTH, 2, &ownerAuth, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_OwnerSetDisable_Internal(hContext, disableState, &ownerAuth);

	MUTEX_UNLOCK(tcsp_lock);

	if (result == TSS_SUCCESS) {
		initData(&data->comm, 1);
		if (setData(TCSD_PACKET_TYPE_AUTH, 0, &ownerAuth, 0, &data->comm)) {
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
	} else
		initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_PhysicalDisable(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_PhysicalDisable_Internal(hContext);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_PhysicalPresence(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;
	TCPA_PHYSICAL_PRESENCE phyPresFlags;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_UINT16, 1, &phyPresFlags, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_PhysicalPresence_Internal(hContext, phyPresFlags);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_SetTempDeactivated(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_SetTempDeactivated_Internal(hContext);

	MUTEX_UNLOCK(tcsp_lock);

	initData(&data->comm, 0);
	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

TSS_RESULT
tcs_wrap_ResetLockValue(struct tcsd_thread_data *data)
{
	TCS_CONTEXT_HANDLE hContext;
	TPM_AUTH ownerAuth;
	TSS_RESULT result;

	if (getData(TCSD_PACKET_TYPE_UINT32, 0, &hContext, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	LogDebugFn("thread %zd context %x", THREAD_ID, hContext);

	if (getData(TCSD_PACKET_TYPE_AUTH, 1, &ownerAuth, 0, &data->comm))
		return TCSERR(TSS_E_INTERNAL_ERROR);

	MUTEX_LOCK(tcsp_lock);

	result = TCSP_ResetLockValue_Internal(hContext, &ownerAuth);

	MUTEX_UNLOCK(tcsp_lock);

	if (result == TSS_SUCCESS) {
		initData(&data->comm, 1);
		if (setData(TCSD_PACKET_TYPE_AUTH, 0, &ownerAuth, 0, &data->comm)) {
			return TCSERR(TSS_E_INTERNAL_ERROR);
		}
	} else
		initData(&data->comm, 0);

	data->comm.hdr.u.result = result;

	return TSS_SUCCESS;
}

