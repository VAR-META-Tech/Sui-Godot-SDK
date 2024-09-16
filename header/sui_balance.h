#ifndef SUI_BALANCE_H
#define SUI_BALANCE_H

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
	static BalanceArray get_balances(const char *address);
	static BalanceArray get_all_balances_sync(const char *address);
	static void free_balance_array(BalanceArray balance_array);
	static Balance get_balance_sync(const char *address);
	static void free_balance(Balance balance);
	static uint64_t get_total_supply_sync();
	static CCoinArray get_coins_sync(const char *address);
	static void free_coin_array(CCoinArray coins);
};
}

#endif // SUI_BALANCE_H
