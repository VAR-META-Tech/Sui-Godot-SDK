#include "sui_transaction.h"

String SuiTransaction::signTransaction(String sender, String recipient, unsigned long long int amount)
{
	return programmable_transaction(sender.utf8().get_data(), recipient.utf8().get_data(), amount);
}

String SuiTransaction::programmableTransactionAllowSponser(String sender_address, String recipient_address, unsigned long long int amount, String sponser_address)
{
	return  programmable_transaction_allow_sponser(sender_address.utf8().get_data(), recipient_address.utf8().get_data(), amount, sponser_address.utf8().get_data());
}

String SuiTransaction::requestTokensFromFaucet(String address_str)
{
	return request_tokens_from_faucet_(address_str.utf8().get_data());
}