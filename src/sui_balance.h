#ifndef SUI_BALANCE_CPP_H
#define SUI_BALANCE_CPP_H
#include "../header/sui_lib.h"

extern "C" {

class SuiBalance {
public:
	BalanceArray getBalances(const char *address);
	BalanceArray getAllBalancesSync(const char *address);
	void freeBalanceArray(BalanceArray balanceArray);
	Balance getBalanceSync(const char *address);
	void freeBalance(Balance balance);
	uint64_t getTotalSupplySync();
	CCoinArray getCoinsSync(const char *address);
	void freeCoinArray(CCoinArray coins);
};
}

#endif // SUI_BALANCE_H
