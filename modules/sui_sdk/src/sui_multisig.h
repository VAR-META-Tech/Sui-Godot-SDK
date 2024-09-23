#ifndef GODOT_SUI_MULTISIG_H
#define GODOT_SUI_MULTISIG_H

#include "../header/sui_lib.h"

class SuiMultisig {
protected:
	// static void _bind_methods();

public:
	MultiSig getOrCreateMultisig(CStringArray addresses, CU8Array weights, uint16_t threshold);
	CU8Array createTransaction(const char *from_address,
			const char *to_address, uint64_t amount);
	const char *signAndExecuteTransaction(
			CU8Array multisig,
			CU8Array tx,
			CStringArray addresses);
	void freeMultisig(MultiSig multisig);
};

#endif
