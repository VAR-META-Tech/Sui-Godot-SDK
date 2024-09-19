#include "sui_wallet.h"

WalletList SuiWallet::getWallets()
{
	WalletList wallet_list = get_wallets();

	if (wallet_list.wallets == NULL)
	{
		printf("Error retrieving wallets\n");
		// return;
	}

	return wallet_list;
}

void SuiWallet::freeWalletList(WalletList wallet_list)
{
	free_wallet_list(wallet_list);
}

Wallet *SuiWallet::generateWallet(const char *key_scheme, const char *word_length)
{
	Wallet *wallet = generate_wallet(key_scheme, word_length);
	return wallet;
}

Wallet *SuiWallet::generateAndAddKey()
{
	Wallet *wallet = generate_and_add_key();
	return wallet;
}

Wallet *SuiWallet::getWalletFromAddress(const char *address)
{
	Wallet *wallet = get_wallet_from_address(address);
	return wallet;
}

void SuiWallet::freeWallet(Wallet *wallet)
{
	free_wallet(wallet);
}

void SuiWallet::importFromPrivateKey(const char *key_base64)
{
	import_from_private_key(key_base64);
}

char *SuiWallet::importFromMnemonic(const char *mnemonic)
{
	return import_from_mnemonic(mnemonic);
}
