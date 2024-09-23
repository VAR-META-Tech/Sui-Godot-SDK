#include "sui_multisig.h"

MultiSig SuiMultisig::getOrCreateMultisig(CStringArray addresses, CU8Array weights, uint16_t threshold) {
	return get_or_create_multisig(addresses, weights, threshold);
}

CU8Array SuiMultisig::createTransaction(const char *from_address,
		const char *to_address, uint64_t amount) {
	return create_transaction(from_address, to_address, amount);
}

const char *SuiMultisig::signAndExecuteTransaction(CU8Array multisig,
		CU8Array tx,
		CStringArray addresses) {
	return sign_and_execute_transaction(multisig, tx, addresses);
}

void SuiMultisig::freeMultisig(MultiSig multisig) {
	free_multisig(multisig);
}
