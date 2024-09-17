// rust_functions.h
#ifndef SUI_MULTISIG_H
#define SUI_MULTISIG_H
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	const uint8_t *data;
	uint32_t len;
	const char *error;
} CU8Array;

typedef struct
{
	const char *address;
	CU8Array bytes;
	const char *error;
} MultiSig;
extern MultiSig get_or_create_multisig(CStringArray addresses, CU8Array weights, uint16_t threshold);
extern CU8Array create_transaction(const char *from_address,
		const char *to_address, uint64_t amount);
const char *sign_and_execute_transaction(
		CU8Array multisig,
		CU8Array tx,
		CStringArray addresses);
extern void free_multisig(MultiSig multisig);
#ifdef __cplusplus
}
#endif

#endif // SUI_MULTISIG_H
