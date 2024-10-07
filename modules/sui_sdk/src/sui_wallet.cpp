#include "sui_wallet.h"
#include "iostream"

Ref<WalletWrapper> _toWalletWrapper(const WalletStruct &wallet_struct)
{
	Ref<WalletWrapper> wrapper = memnew(WalletWrapper);
	wrapper->set_address(wallet_struct.address);
	wrapper->set_mnemonic(wallet_struct.mnemonic);
	wrapper->set_public_base64_key(wallet_struct.public_base64_key);
	wrapper->set_private_key(wallet_struct.private_key);
	wrapper->set_key_scheme(wallet_struct.key_scheme);
	return wrapper;
}

Ref<WalletWrapper> _makeWalletStruct(Wallet *wallet)
{
	WalletStruct walletStructItem;
	walletStructItem.address = wallet->address;
	walletStructItem.mnemonic = wallet->mnemonic;
	walletStructItem.public_base64_key = wallet->public_base64_key;
	walletStructItem.private_key = wallet->private_key;
	walletStructItem.key_scheme = wallet->key_scheme;

	return _toWalletWrapper(walletStructItem);
}

Ref<ImportResultWrapper> _toImportResultWrapper(const ImportResultStruct &result_struct)
{
	Ref<ImportResultWrapper> wrapper = memnew(ImportResultWrapper);
	wrapper->set_status(result_struct.status);
	wrapper->set_address(result_struct.address);
	wrapper->set_error(result_struct.error);

	return wrapper;
}

Ref<ImportResultWrapper> _makeImportResultStruct(ImportResult *result)
{
	ImportResultStruct resultStructItem;

	resultStructItem.status = result->status;
	resultStructItem.address = result->address;
	resultStructItem.error = result->error;

	return _toImportResultWrapper(resultStructItem);
}

/**
 * Main function
 */

TypedArray<WalletWrapper> SuiWallet::getWallets()
{
	WalletList wallet_list = get_wallets();
	TypedArray<WalletWrapper> wallets;
	for (int i = 0; i < wallet_list.length; i++)
	{
		Wallet *wallet = &wallet_list.wallets[i];
		wallets.append(_makeWalletStruct(wallet));
	}

	free_wallet_list(wallet_list);
	return wallets;
}

void SuiWallet::freeWalletList(WalletList wallet_list)
{
	free_wallet_list(wallet_list);
}

Ref<WalletWrapper> SuiWallet::generateWallet(String key_scheme, String word_length)
{
	Wallet *wallet = generate_wallet(key_scheme.utf8().get_data(), word_length.utf8().get_data());
	return _makeWalletStruct(wallet);
}

Ref<WalletWrapper> SuiWallet::generateAndAddKey()
{
	Wallet *wallet = generate_and_add_key();
	return _makeWalletStruct(wallet);
}

Ref<WalletWrapper> SuiWallet::getWalletFromAddress(String address)
{
	Wallet *wallet = get_wallet_from_address(address.utf8().get_data());
	if (!wallet)
	{
		std::cout << "Wallet not found" << '\n';
		return NULL;
	}
	return _makeWalletStruct(wallet);
}

void SuiWallet::freeWallet(Wallet *wallet)
{
	free_wallet(wallet);
}

Ref<ImportResultWrapper> SuiWallet::importFromPrivateKey(String key_base64)
{
	ImportResult *result = import_from_private_key(key_base64.utf8().get_data());

	return _makeImportResultStruct(result);
}

Ref<ImportResultWrapper> SuiWallet::importFromMnemonic(String mnemonic, String sig_scheme, String alias)
{
	const char *mnemonic_argument = mnemonic.utf8().get_data();
	const char *sig_scheme_argument = sig_scheme.utf8().get_data();
	const char *alias_argument = alias.utf8().get_data();
	ImportResult *result = import_from_mnemonic(mnemonic_argument, sig_scheme_argument, alias_argument);

	return _makeImportResultStruct(result);
}
