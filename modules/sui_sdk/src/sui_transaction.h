#ifndef GODOT_SUI_TRANSACTION_H
#define GODOT_SUI_TRANSACTION_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"

class SuiTransaction
{
protected:
public:
	String signTransaction(String sender, String recipient, uint64_t amount);
	String programmableTransactionAllowSponser(String sender_address, String recipient_address, uint64_t amount, String sponser_address);
	String requestTokensFromFaucet(String address_str);
	String programmableTransactionBuilder(String sender, String recipient, uint64_t amount);
};

#endif
