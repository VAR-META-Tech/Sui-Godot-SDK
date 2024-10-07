#ifndef SUI_BALANCE_CPP_H
#define SUI_BALANCE_CPP_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

struct BalanceStruct {
	String coin_type;
	uint32_t coin_object_count;
	String total_balance;
};

struct CCoinStruct {
	String coin_type;
	String coin_object_id;
	String version;
	String digest;
	String balance;
	String previous_transaction;
};

class BalanceWrapper : public RefCounted {
	GDCLASS(BalanceWrapper, RefCounted);

public:
	String coin_type;
	uint32_t coin_object_count;
	String total_balance;

	void set_coin_type(String p_coin_type) {
		coin_type = p_coin_type;
	}
	String get_coin_type() const {
		return coin_type;
	}

	void set_coin_object_count(uint32_t p_coin_object_count) {
		coin_object_count = p_coin_object_count;
	}

	uint32_t get_coin_object_count() const {
		return coin_object_count;
	}

	void set_total_balance(String p_total_balance) {
		total_balance = p_total_balance;
	}

	String get_total_balance() const {
		return total_balance;
	}

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("set_coin_type", "coin_type"), &BalanceWrapper::set_coin_type);
		ClassDB::bind_method(D_METHOD("get_coin_type"), &BalanceWrapper::get_coin_type);
		ClassDB::bind_method(D_METHOD("set_coin_object_count", "coin_object_count"), &BalanceWrapper::set_coin_object_count);
		ClassDB::bind_method(D_METHOD("get_coin_object_count"), &BalanceWrapper::get_coin_object_count);
		ClassDB::bind_method(D_METHOD("set_total_balance", "total_balance"), &BalanceWrapper::set_total_balance);
		ClassDB::bind_method(D_METHOD("get_total_balance"), &BalanceWrapper::get_total_balance);
	}
};

class CoinWrapper : public RefCounted {
	GDCLASS(CoinWrapper, RefCounted);

public:
	String coin_type;
	String coin_object_id;
	String version;
	String digest;
	String balance;
	String previous_transaction;

	void set_coin_type(String p_coin_type) { coin_type = p_coin_type; }
	String get_coin_type() const { return coin_type; }

	void set_coin_object_id(String p_coin_object_id) { coin_object_id = p_coin_object_id; }

	String get_coin_object_id() const { return coin_object_id; }

	void set_version(String p_version) { version = p_version; }

	String get_version() const { return version; }

	void set_digest(String p_digest) { digest = p_digest; }

	String get_digest() const { return digest; }

	void set_balance(String p_balance) { balance = p_balance; }

	String get_balance() const { return balance; }

	void set_previous_transaction(String p_previous_transaction) { previous_transaction = p_previous_transaction; }

	String get_previous_transaction() const { return previous_transaction; }

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("set_coin_type", "coin_type"), &CoinWrapper::set_coin_type);
		ClassDB::bind_method(D_METHOD("get_coin_type"), &CoinWrapper::get_coin_type);
		ClassDB::bind_method(D_METHOD("set_coin_object_id", "coin_object_id"), &CoinWrapper::set_coin_object_id);
		ClassDB::bind_method(D_METHOD("get_coin_object_id"), &CoinWrapper::get_coin_object_id);
		ClassDB::bind_method(D_METHOD("set_version", "version"), &CoinWrapper::set_version);
		ClassDB::bind_method(D_METHOD("get_version"), &CoinWrapper::get_version);
		ClassDB::bind_method(D_METHOD("set_digest", "digest"), &CoinWrapper::set_digest);
		ClassDB::bind_method(D_METHOD("get_digest"), &CoinWrapper::get_digest);
		ClassDB::bind_method(D_METHOD("set_balance", "balance"), &CoinWrapper::set_balance);
		ClassDB::bind_method(D_METHOD("get_balance"), &CoinWrapper::get_balance);
		ClassDB::bind_method(D_METHOD("set_previous_transaction", "previous_transaction"), &CoinWrapper::set_previous_transaction);
		ClassDB::bind_method(D_METHOD("get_previous_transaction"), &CoinWrapper::get_previous_transaction);
	}
};

class SuiBalance {
public:
	TypedArray<BalanceWrapper> getBalances(String address);
	TypedArray<BalanceWrapper> getAllBalancesSync(String address);
	Ref<BalanceWrapper> getBalanceSync(String address);
	String getTotalSupplySync();
	TypedArray<CoinWrapper> getCoinsSync(String address);
};

#endif // SUI_BALANCE_H
