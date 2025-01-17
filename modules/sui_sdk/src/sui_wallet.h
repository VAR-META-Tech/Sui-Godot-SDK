#ifndef GODOT_SUI_WALLET_H
#define GODOT_SUI_WALLET_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

struct ImportResultStruct
{
	int status;
	String address;
	String error;
};

class ImportResultWrapper : public RefCounted
{
	GDCLASS(ImportResultWrapper, RefCounted);

public:
	int status;
	String address;
	String error;

	void set_status(int p_status) { status = p_status; }
	int get_status() const { return status; }
	void set_address(String p_address) { address = p_address; }
	String get_address() { return address; }
	void set_error(String p_error) { error = p_error; }
	String get_error() { return error; }

	static void _bind_methods()
	{
		ClassDB::bind_method(D_METHOD("get_status"), &ImportResultWrapper::get_status);
		ClassDB::bind_method(D_METHOD("set_status", "status"), &ImportResultWrapper::set_status);
		ClassDB::bind_method(D_METHOD("get_address"), &ImportResultWrapper::get_address);
		ClassDB::bind_method(D_METHOD("set_address", "address"), &ImportResultWrapper::set_address);
		ClassDB::bind_method(D_METHOD("get_error"), &ImportResultWrapper::get_error);
		ClassDB::bind_method(D_METHOD("set_error", "error"), &ImportResultWrapper::set_error);
	}
};

struct WalletStruct
{
	String address;
	String mnemonic;
	String public_base64_key;
	String private_key;
	String key_scheme;
};

class WalletWrapper : public RefCounted
{
	GDCLASS(WalletWrapper, RefCounted);

public:
	String address;
	String mnemonic;
	String public_base64_key;
	String private_key;
	String key_scheme;

	void set_address(String p_address) { address = p_address; }
	String get_address() const { return address; }
	void set_mnemonic(String p_mnemonic) { mnemonic = p_mnemonic; }
	String get_mnemonic() { return mnemonic; }
	void set_public_base64_key(String p_public_base64_key) { public_base64_key = p_public_base64_key; }
	String get_public_base64_key() { return public_base64_key; }
	void set_private_key(String p_private_key) { private_key = p_private_key; }
	String get_private_key() { return private_key; }
	void set_key_scheme(String p_key_scheme) { key_scheme = p_key_scheme; }
	String get_key_scheme() { return key_scheme; }

	static void _bind_methods()
	{
		ClassDB::bind_method(D_METHOD("get_address"), &WalletWrapper::get_address);
		ClassDB::bind_method(D_METHOD("set_address", "address"), &WalletWrapper::set_address);
		ClassDB::bind_method(D_METHOD("get_mnemonic"), &WalletWrapper::get_mnemonic);
		ClassDB::bind_method(D_METHOD("set_mnemonic", "mnemonic"), &WalletWrapper::set_mnemonic);
		ClassDB::bind_method(D_METHOD("get_public_base64_key"), &WalletWrapper::get_public_base64_key);
		ClassDB::bind_method(D_METHOD("set_public_base64_key", "public_base64_key"), &WalletWrapper::set_public_base64_key);
		ClassDB::bind_method(D_METHOD("get_private_key"), &WalletWrapper::get_private_key);
		ClassDB::bind_method(D_METHOD("set_private_key", "private_key"), &WalletWrapper::set_private_key);
		ClassDB::bind_method(D_METHOD("get_key_scheme"), &WalletWrapper::get_key_scheme);
		ClassDB::bind_method(D_METHOD("set_key_scheme", "key_scheme"), &WalletWrapper::set_key_scheme);
	}
};

class SuiWallet
{
public:
	TypedArray<WalletWrapper> getWallets();
	void freeWalletList(WalletList wallet_list);
	Ref<WalletWrapper> generateWallet(String key_scheme, String word_length);
	Ref<WalletWrapper> generateAndAddKey();
	Ref<WalletWrapper> getWalletFromAddress(String address);
	void freeWallet(Wallet *wallet);
	Ref<ImportResultWrapper> importFromPrivateKey(String key_base64);
	Ref<ImportResultWrapper> importFromMnemonic(String mnemonic, String sig_scheme, String alias);
};

#endif
