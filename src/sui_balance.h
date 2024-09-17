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
	static BalanceArray getBalances(const char *address);
	static BalanceArray getAllBalancesSync(const char *address);
	static void freeBalanceArray(BalanceArray balanceArray);
	static Balance getBalanceSync(const char *address);
	static void freeBalance(Balance balance);
	static uint64_t getTotalSupplySync();
	static CCoinArray getCoinsSync(const char *address);
	static void freeCoinArray(CCoinArray coins);
};
}

#endif // SUI_BALANCE_H
