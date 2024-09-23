#include "sui_balance.h"

Ref<BalanceWrapper> toBalanceWrapper(const BalanceStruct &balance_struct) {
	Ref<BalanceWrapper> wrapper = memnew(BalanceWrapper);
	wrapper->set_coin_object_count(balance_struct.coin_object_count);
	wrapper->set_coin_type(balance_struct.coin_type);
	wrapper->set_total_balance(balance_struct.total_balance);
	return wrapper;
}

Ref<CoinWrapper> toCoinWrapper(const CCoinStruct &coin_struct) {
	Ref<CoinWrapper> wrapper = memnew(CoinWrapper);
	wrapper->set_coin_object_id(coin_struct.coin_object_id);
	wrapper->set_coin_type(coin_struct.coin_type);
	wrapper->set_balance(coin_struct.balance);
	wrapper->set_previous_transaction(coin_struct.previous_transaction);
	wrapper->set_digest(coin_struct.digest);
	wrapper->set_version(coin_struct.version);
	return wrapper;
}

TypedArray<BalanceWrapper> SuiBalance::getBalances(String address) {
	BalanceArray balance_list = get_balances(address.utf8().get_data());
	TypedArray<BalanceWrapper> balances;
	for (int i = 0; i < balance_list.length; i++) {
		BalanceStruct balanceItem;
		balanceItem.total_balance = *balance_list.balances[i].total_balance;
		balanceItem.coin_type = balance_list.balances[i].coin_type;
		balanceItem.coin_object_count = balance_list.balances[i].coin_object_count;

		balances.append(toBalanceWrapper(balanceItem));
	}

	free_balance_array(balance_list);
	return balances;
}

TypedArray<BalanceWrapper> SuiBalance::getAllBalancesSync(String address) {
	BalanceArray balance_list = get_all_balances_sync(address.utf8().get_data());
	TypedArray<BalanceWrapper> balances;
	for (int i = 0; i < balance_list.length; i++) {
		BalanceStruct balanceItem;
		balanceItem.total_balance = *balance_list.balances[i].total_balance;
		balanceItem.coin_type = balance_list.balances[i].coin_type;
		balanceItem.coin_object_count = balance_list.balances[i].coin_object_count;

		balances.append(toBalanceWrapper(balanceItem));
	}

	free_balance_array(balance_list);
	return balances;
}

Ref<BalanceWrapper> SuiBalance::getBalanceSync(String address) {
	Balance balance = get_balance_sync(address.utf8().get_data());
	BalanceStruct balanceStructItem;
	balanceStructItem.coin_object_count = balance.coin_object_count;
	balanceStructItem.coin_type = balance.coin_type;
	balanceStructItem.total_balance = (unsigned long long int)balance.total_balance;
	free_balance(balance);
	return toBalanceWrapper(balanceStructItem);
}

unsigned long long int SuiBalance::getTotalSupplySync() {
	return get_total_supply_sync();
}

TypedArray<CoinWrapper> SuiBalance::getCoinsSync(String address) {
	CCoinArray coin_list = get_coins_sync(address.utf8().get_data());
	TypedArray<CoinWrapper> coins;
	for (int i = 0; i < coin_list.length; i++) {
		CCoinStruct coin;
		coin.balance = coin_list.coins[i].balance;
		coin.coin_type = coin_list.coins[i].coin_type;
		coin.coin_object_id = coin_list.coins[i].coin_object_id;
		coin.digest = coin_list.coins[i].digest;
		coin.version = coin_list.coins[i].version;
		coin.previous_transaction = coin_list.coins[i].previous_transaction;

		coins.append(toCoinWrapper(coin));
	}

	free_coin_array(coin_list);
	return coins;
}
