#ifndef SUI_MULTISIG_H
#define SUI_MULTISIG_H

#include <inttypes.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>

extern "C" {
struct CU8Array {
	const uint8_t *data;
	uint32_t len;
	const char *error;
};

struct MultiSig {
	const char *address;
	CU8Array bytes;
	const char *error;
};
class SuiMultisig {
public:
	static MultiSig get_or_create_multisig(SuiClient::CStringArray addresses, CU8Array weights, uint16_t threshold);
	static CU8Array create_transaction(const char *from_address, const char *to_address, uint64_t amount);
	static const char *sign_and_execute_transaction(CU8Array multisig, CU8Array tx, SuiClient::CStringArray addresses);
	static void free_multisig(MultiSig multisig);
};
}

#endif // SUI_MULTISIG_H
