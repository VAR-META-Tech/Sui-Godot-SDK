#include "sui_transaction.h"

char *SuiTransaction::signTransaction(const char *sender, const char *recipient, unsigned long long amount) {
	char *result = programmable_transaction(sender, recipient, amount);
	return result;
}
