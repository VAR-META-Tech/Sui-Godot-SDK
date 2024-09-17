#include "sui_balance.h"
#include "header/sui_lib.h"

SuiBalance::Balance SuiBalance::getBalanceSync(const char *address) {
	return get_balance_sync(address);
}
