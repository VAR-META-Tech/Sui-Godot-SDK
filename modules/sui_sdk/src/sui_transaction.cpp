#include "sui_transaction.h"
#include <iostream>
#include <string.h>

/**
 * Main function
 */

String SuiTransaction::signTransaction(String sender, String recipient, uint64_t amount)
{
	return programmable_transaction(sender.utf8().get_data(), recipient.utf8().get_data(), amount);
}

String SuiTransaction::programmableTransactionAllowSponser(String sender_address, String recipient_address, uint64_t amount, String sponser_address)
{
	return programmable_transaction_allow_sponser(sender_address.utf8().get_data(), recipient_address.utf8().get_data(), amount, sponser_address.utf8().get_data());
}

String SuiTransaction::requestTokensFromFaucet(String address_str)
{
	return request_tokens_from_faucet(address_str.utf8().get_data());
}
