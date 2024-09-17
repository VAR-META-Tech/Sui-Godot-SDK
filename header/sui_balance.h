// rust_functions.h
#ifndef SUI_BALANCE_H
#define SUI_BALANCE_H
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include "src/sui_balance.h"
extern "C" {
extern SuiBalance::BalanceArray get_balances(const char *address);
extern SuiBalance::BalanceArray get_all_balances_sync(const char *address);
extern void free_balance_array(SuiBalance::BalanceArray balance_array);
extern SuiBalance::Balance get_balance_sync(const char *address);
extern void free_balance(SuiBalance::Balance balance);
extern uint64_t get_total_supply_sync();
extern SuiBalance::CCoinArray get_coins_sync(const char *address);
extern void free_coin_array(SuiBalance::CCoinArray coins);
}

#endif // SUI_BALANCE_H