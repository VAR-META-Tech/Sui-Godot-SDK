#ifndef GODOT_SUI_TRANSACTION_H
#define GODOT_SUI_TRANSACTION_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"

class SuiTransaction
{
protected:
public:
	String signTransaction(String sender, String recipient, unsigned long long int amount);
	String programmableTransactionAllowSponser(String sender_address, String recipient_address, unsigned long long int amount, String sponser_address);
	String requestTokensFromFaucet(String address_str);
};

#endif
