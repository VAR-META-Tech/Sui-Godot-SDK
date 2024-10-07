#include "sui_balance.h"

Ref<BalanceWrapper> _toBalanceWrapper(const BalanceStruct &balance_struct)
{
	Ref<BalanceWrapper> wrapper = memnew(BalanceWrapper);
	wrapper->set_coin_object_count(balance_struct.coin_object_count);
	wrapper->set_coin_type(balance_struct.coin_type);
	wrapper->set_total_balance(balance_struct.total_balance);
	return wrapper;
}

Ref<CoinWrapper> _toCoinWrapper(const CCoinStruct &coin_struct)
{
	Ref<CoinWrapper> wrapper = memnew(CoinWrapper);
	wrapper->set_coin_object_id(coin_struct.coin_object_id);
	wrapper->set_coin_type(coin_struct.coin_type);
	wrapper->set_balance(coin_struct.balance);
	wrapper->set_previous_transaction(coin_struct.previous_transaction);
	wrapper->set_digest(coin_struct.digest);
	wrapper->set_version(coin_struct.version);
	return wrapper;
}

/**
 * Main function
 */

TypedArray<BalanceWrapper> SuiBalance::getBalances(String address)
{
	CBalanceArray balance_list = get_balances(address.utf8().get_data());
	TypedArray<BalanceWrapper> balances;
	for (int i = 0; i < balance_list.length; i++)
	{
		BalanceStruct balanceItem;
		balanceItem.total_balance = String::num_uint64(balance_list.balances[i].total_balance[0]);
		balanceItem.coin_type = balance_list.balances[i].coin_type;
		balanceItem.coin_object_count = balance_list.balances[i].coin_object_count;

		balances.append(_toBalanceWrapper(balanceItem));
	}

	free_balance_array(balance_list);
	return balances;
}

TypedArray<BalanceWrapper> SuiBalance::getAllBalancesSync(String address)
{
	CBalanceArray balance_list = get_all_balances_sync(address.utf8().get_data());
	TypedArray<BalanceWrapper> balances;
	for (int i = 0; i < balance_list.length; i++)
	{
		BalanceStruct balanceItem;
		balanceItem.total_balance = String::num_uint64(balance_list.balances[i].total_balance[0]);
		balanceItem.coin_type = balance_list.balances[i].coin_type;
		balanceItem.coin_object_count = balance_list.balances[i].coin_object_count;

		balances.append(_toBalanceWrapper(balanceItem));
	}

	free_balance_array(balance_list);
	return balances;
}

Ref<BalanceWrapper> SuiBalance::getBalanceSync(String address)
{
	CBalance balance = get_balance_sync(address.utf8().get_data());
	BalanceStruct balanceStructItem;
	balanceStructItem.coin_object_count = balance.coin_object_count;
	balanceStructItem.coin_type = balance.coin_type;
	balanceStructItem.total_balance = String::num_uint64(balance.total_balance[0]);
	free_balance(balance);
	return _toBalanceWrapper(balanceStructItem);
}

String SuiBalance::getTotalSupplySync()
{
	uint64_t total_supply = get_total_supply_sync();
	return String::num_uint64(total_supply);
}

TypedArray<CoinWrapper> SuiBalance::getCoinsSync(String address)
{
	CCoinArray coin_list = get_coins_sync(address.utf8().get_data());
	TypedArray<CoinWrapper> coins;
	for (int i = 0; i < coin_list.length; i++)
	{
		CCoinStruct coin;
		coin.balance = String::num_uint64(coin_list.coins[i].balance);
		coin.coin_type = coin_list.coins[i].coin_type;
		coin.coin_object_id = coin_list.coins[i].coin_object_id;
		coin.digest = coin_list.coins[i].digest;
		coin.version = String::num_uint64(coin_list.coins[i].version);
		coin.previous_transaction = coin_list.coins[i].previous_transaction;

		coins.append(_toCoinWrapper(coin));
	}

	free_coin_array(coin_list);
	return coins;
}
