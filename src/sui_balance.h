#ifndef SUI_BALANCE_CPP_H
#define SUI_BALANCE_CPP_H

#include <inttypes.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>

extern "C" {

class SuiBalance {
public:
	struct Balance {
		std::string coin_type;
		size_t coin_object_count;
		uint64_t total_balance[2];
	};

	struct BalanceArray {
		Balance *balances;
		size_t length;
	};

	struct CCoin {
		std::string coin_type;
		std::string coin_object_id;
		uint64_t version;
		std::string digest;
		uint64_t balance;
		std::string previous_transaction;
	};

	struct CCoinArray {
		CCoin *coins;
		size_t length;
	};
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
