#include "sui_transaction.h"

char *SuiTransaction::signTransaction(const char *sender, const char *recipient, unsigned long long amount) {
	char *result = programmable_transaction(sender, recipient, amount);
	return result;
}

char *SuiTransaction::programmableTransactionAllowSponser(const char *sender_address, const char *recipient_address, unsigned long long amount, const char *sponser_address) {
	char *result = programmable_transaction_allow_sponser(sender_address, recipient_address, amount, sponser_address);
	return result;
}

const char *SuiTransaction::requestTokensFromFaucet(const char *address_str) {
	return request_tokens_from_faucet_(address_str);
}
