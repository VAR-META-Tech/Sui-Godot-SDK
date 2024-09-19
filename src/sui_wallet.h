#ifndef GODOT_SUI_WALLET_H
#define GODOT_SUI_WALLET_H

#include "../header/sui_lib.h"

class SuiWallet
{
protected:
	static void _bind_methods();

public:
	WalletList getWallets();
	void freeWalletList(WalletList wallet_list);
	Wallet *generateWallet(const char *key_scheme, const char *word_length);
	Wallet *generateAndAddKey();
	Wallet *getWalletFromAddress(const char *address);
	void freeWallet(Wallet *wallet);
	void importFromPrivateKey(const char *key_base64);
	char *importFromMnemonic(const char *mnemonic);
};

#endif
