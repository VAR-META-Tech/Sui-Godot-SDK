#include "sui_balance.h"
#include "header/sui_lib.h"

SuiBalance::Balance SuiBalance::getBalanceSync(const char *address) {
	return get_balance_sync(address);
}
SuiBalance::BalanceArray SuiBalance::getBalances(const char *address) {
	return get_balances(address);
}
SuiBalance::BalanceArray SuiBalance::getAllBalancesSync(const char *address) {
	return get_all_balances_sync(address);
}
void SuiBalance::freeBalanceArray(SuiBalance::BalanceArray balance_array) {
	return free_balance_array(balance_array);
}
void SuiBalance::freeBalance(SuiBalance::Balance balance) {
	return free_balance(balance);
}
uint64_t SuiBalance::getTotalSupplySync() {
	return get_total_supply_sync();
}
SuiBalance::CCoinArray SuiBalance::getCoinsSync(const char *address) {
	return get_coins_sync(address);
}
void SuiBalance::freeCoinArray(SuiBalance::CCoinArray coins) {
	return free_coin_array(coins);
}