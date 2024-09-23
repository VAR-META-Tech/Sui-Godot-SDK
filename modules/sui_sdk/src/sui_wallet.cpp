#include "sui_wallet.h"
#include "iostream"

Ref<WalletWrapper> toWalletWrapper(const WalletStruct &wallet_struct) {
	Ref<WalletWrapper> wrapper = memnew(WalletWrapper);
	wrapper->set_address(wallet_struct.address);
	wrapper->set_mnemonic(wallet_struct.mnemonic);
	wrapper->set_public_base64_key(wallet_struct.public_base64_key);
	wrapper->set_private_key(wallet_struct.private_key);
	wrapper->set_key_scheme(wallet_struct.key_scheme);
	return wrapper;
}

Ref<WalletWrapper> makeWalletStruct(Wallet *wallet) {
	WalletStruct walletStructItem;
	walletStructItem.address = wallet->address;
	walletStructItem.mnemonic = wallet->mnemonic;
	walletStructItem.public_base64_key = wallet->public_base64_key;
	walletStructItem.private_key = wallet->private_key;
	walletStructItem.key_scheme = wallet->key_scheme;

	return toWalletWrapper(walletStructItem);
}

TypedArray<WalletWrapper> SuiWallet::getWallets() {
	WalletList wallet_list = get_wallets();
	TypedArray<WalletWrapper> wallets;
	for (int i = 0; i < wallet_list.length; i++) {
		Wallet *wallet = &wallet_list.wallets[i];
		wallets.append(makeWalletStruct(wallet));
	}

	free_wallet_list(wallet_list);
	return wallets;
}

void SuiWallet::freeWalletList(WalletList wallet_list) {
	free_wallet_list(wallet_list);
}

Ref<WalletWrapper> SuiWallet::generateWallet(String key_scheme, String word_length) {
	Wallet *wallet = generate_wallet(key_scheme.utf8().get_data(), word_length.utf8().get_data());
	return makeWalletStruct(wallet);
}

Ref<WalletWrapper> SuiWallet::generateAndAddKey() {
	Wallet *wallet = generate_and_add_key();
	return makeWalletStruct(wallet);
}

Ref<WalletWrapper> SuiWallet::getWalletFromAddress(String address) {
	Wallet *wallet = get_wallet_from_address(address.utf8().get_data());
	if (!wallet) {
		std::cout << "Wallet not found" << '\n';
		return NULL;
	}
	return makeWalletStruct(wallet);
}

void SuiWallet::freeWallet(Wallet *wallet) {
	free_wallet(wallet);
}

void SuiWallet::importFromPrivateKey(String key_base64) {
	import_from_private_key(key_base64.utf8().get_data());
}

String SuiWallet::importFromMnemonic(String mnemonic) {
	char *address = import_from_mnemonic(mnemonic.utf8().get_data());
	return address;
}
