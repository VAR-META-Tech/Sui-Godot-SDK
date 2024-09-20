#include "sui_wallet.h"

Ref<WalletWrapper> toWalletWrapper(const WalletStruct &wallet_struct) {
	Ref<WalletWrapper> wrapper = memnew(WalletWrapper);
	wrapper->set_address(wallet_struct.address);
	wrapper->set_mnemonic(wallet_struct.mnemonic);
	wrapper->set_public_base64_key(wallet_struct.public_base64_key);
	wrapper->set_private_key(wallet_struct.private_key);
	wrapper->set_key_scheme(wallet_struct.key_scheme);
	return wrapper;
}

TypedArray<WalletWrapper> SuiWallet::getWallets() {
	WalletList wallet_list = get_wallets();
	TypedArray<WalletWrapper> wallets;
	for (int i = 0; i < wallet_list.length; i++) {
		WalletStruct walletStructItem;
		walletStructItem.address = wallet_list.wallets[i].address;
		walletStructItem.mnemonic = wallet_list.wallets[i].mnemonic;
		walletStructItem.public_base64_key = wallet_list.wallets[i].public_base64_key;
		walletStructItem.private_key = wallet_list.wallets[i].private_key;
		walletStructItem.key_scheme = wallet_list.wallets[i].key_scheme;

		wallets.append(toWalletWrapper(walletStructItem));
	}

	free_wallet_list(wallet_list);
	return wallets;
}

void SuiWallet::freeWalletList(WalletList wallet_list) {
	free_wallet_list(wallet_list);
}

Wallet *SuiWallet::generateWallet(const char *key_scheme, const char *word_length) {
	Wallet *wallet = generate_wallet(key_scheme, word_length);
	return wallet;
}

Wallet *SuiWallet::generateAndAddKey() {
	Wallet *wallet = generate_and_add_key();
	return wallet;
}

Wallet *SuiWallet::getWalletFromAddress(const char *address) {
	Wallet *wallet = get_wallet_from_address(address);
	return wallet;
}

void SuiWallet::freeWallet(Wallet *wallet) {
	free_wallet(wallet);
}

void SuiWallet::importFromPrivateKey(const char *key_base64) {
	import_from_private_key(key_base64);
}

char *SuiWallet::importFromMnemonic(const char *mnemonic) {
	return import_from_mnemonic(mnemonic);
}
