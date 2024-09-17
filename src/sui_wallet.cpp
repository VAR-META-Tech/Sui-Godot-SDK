#include "sui_wallet.h"

WalletList SuiWallet::getWallets() {
	// Retrieve the list of wallets
	WalletList wallet_list = get_wallets();

	// Check if the retrieval was successful
	if (wallet_list.wallets == NULL) {
		printf("Error retrieving wallets\n");
		// return;
	}

	return wallet_list;
}

void SuiWallet::freeWalletList(WalletList wallet_list) {
	// Free the list of wallets
	free_wallet_list(wallet_list);
}

Wallet *SuiWallet::generateWallet(const char *key_scheme, const char *word_length) {
	// Retrieve the list of wallets
	Wallet *wallet = generate_wallet(key_scheme, word_length);
	return wallet;
}

Wallet *SuiWallet::generateAndAddKey() {
	// Retrieve the list of wallets
	Wallet *wallet = generate_and_add_key();
	return wallet;
}

Wallet *SuiWallet::getWalletFromAddress(const char *address) {
	// Retrieve the list of wallets
	Wallet *wallet = get_wallet_from_address(address);
	return wallet;
}

void SuiWallet::freeWallet(Wallet *wallet) {
	// Free the wallet
	free_wallet(wallet);
}

void SuiWallet::importFromPrivateKey(const char *key_base64) {
	import_from_private_key(key_base64);
}

char *SuiWallet::importFromMnemonic(const char *mnemonic) {
	return import_from_mnemonic(mnemonic);
}
