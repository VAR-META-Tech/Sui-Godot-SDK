#include "sui_balance.h"
#include "header/sui_lib.h"

Balance SuiBalance::getBalanceSync(const char *address) {
	return get_balance_sync(address);
}
BalanceArray SuiBalance::getBalances(const char *address) {
	return get_balances(address);
}
BalanceArray SuiBalance::getAllBalancesSync(const char *address) {
	return get_all_balances_sync(address);
}
void SuiBalance::freeBalanceArray(BalanceArray balance_array) {
	return free_balance_array(balance_array);
}
void SuiBalance::freeBalance(Balance balance) {
	return free_balance(balance);
}
uint64_t SuiBalance::getTotalSupplySync() {
	return get_total_supply_sync();
}
CCoinArray SuiBalance::getCoinsSync(const char *address) {
	return get_coins_sync(address);
}
void SuiBalance::freeCoinArray(CCoinArray coins) {
	return free_coin_array(coins);
}