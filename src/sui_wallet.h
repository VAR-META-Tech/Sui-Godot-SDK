#ifndef GODOT_SUI_WALLET_H
#define GODOT_SUI_WALLET_H

#include "../header/sui_lib.h"
#include "core/variant/typed_array.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"

struct WalletStruct {
	String address;
};

class WalletWrapper : public RefCounted {
	GDCLASS(WalletWrapper, RefCounted);

public:
	String address;
	String mnemonic;
	String public_base64_key;
	String private_key;
	String key_scheme;

	void set_address(String p_address) {
		address = p_address;
	}
	String get_address() const {
		return address;
	}

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("set_address", "address"), &WalletWrapper::set_address);
		ClassDB::bind_method(D_METHOD("get_address"), &WalletWrapper::get_address);
	}
};

class SuiWallet {
public:
	TypedArray<WalletWrapper> getWallets();
	void freeWalletList(WalletList wallet_list);
	Wallet *generateWallet(const char *key_scheme, const char *word_length);
	Wallet *generateAndAddKey();
	Wallet *getWalletFromAddress(const char *address);
	void freeWallet(Wallet *wallet);
	void importFromPrivateKey(const char *key_base64);
	char *importFromMnemonic(const char *mnemonic);
};

#endif
