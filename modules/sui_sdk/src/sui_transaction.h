#ifndef GODOT_SUI_TRANSACTION_H
#define GODOT_SUI_TRANSACTION_H

#include "../header/sui_lib.h"

class SuiTransaction {
protected:
	// static void _bind_methods();

public:
	char *signTransaction(const char *sender, const char *recipient, uint64_t amount);
	char *programmableTransactionAllowSponser(const char *sender_address, const char *recipient_address, uint64_t amount, const char *sponser_address);
	const char *requestTokensFromFaucet(const char *address_str);
};

#endif
