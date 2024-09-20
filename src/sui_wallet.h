#ifndef GODOT_SUI_WALLET_H
#define GODOT_SUI_WALLET_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

struct WalletStruct {
	String address;
	String mnemonic;
	String public_base64_key;
	String private_key;
	String key_scheme;
};

class WalletWrapper : public RefCounted {
	GDCLASS(WalletWrapper, RefCounted);

public:
	String address;
	String mnemonic;
	String public_base64_key;
	String private_key;
	String key_scheme;

	void set_address(String p_address) { address = p_address; }
	String get_address() { return address; }
	void set_mnemonic(String p_mnemonic) { address = p_mnemonic; }
	String get_mnemonic() { return mnemonic; }
	void set_public_base64_key(String p_public_base64_key) { public_base64_key = p_public_base64_key; }
	String get_public_base64_key() { return public_base64_key; }
	void set_private_key(String p_private_key) { private_key = p_private_key; }
	String get_private_key() { return private_key; }
	void set_key_scheme(String p_key_scheme) { key_scheme = p_key_scheme; }
	String get_key_scheme() { return key_scheme; }

	static void _bind_methods() {
		ClassDB::bind_method(D_METHOD("set_address", "address"), &WalletWrapper::set_address);
		ClassDB::bind_method(D_METHOD("get_mnemonic"), &WalletWrapper::get_mnemonic);
		ClassDB::bind_method(D_METHOD("set_mnemonic", "mnemonic"), &WalletWrapper::set_mnemonic);
		ClassDB::bind_method(D_METHOD("get_public_base64_key"), &WalletWrapper::get_public_base64_key);
		ClassDB::bind_method(D_METHOD("set_public_base64_key", "public_base64_key"), &WalletWrapper::set_public_base64_key);
		ClassDB::bind_method(D_METHOD("get_private_key"), &WalletWrapper::get_private_key);
		ClassDB::bind_method(D_METHOD("set_private_key", "private_key"), &WalletWrapper::set_private_key);
		ClassDB::bind_method(D_METHOD("get_address"), &WalletWrapper::get_address);
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
