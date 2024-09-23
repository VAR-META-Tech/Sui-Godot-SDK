#ifndef GODOT_SUI_SDK_H
#define GODOT_SUI_SDK_H

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "src/sui_balance.h"
#include "src/sui_client.h"
#include "src/sui_multisig.h"
#include "src/sui_nfts.h"
#include "src/sui_transaction.h"
#include "src/sui_wallet.h"

namespace godot {

class SuiSDK : public SuiBalance, public SuiWallet, public SuiMultisig, public SuiNfts, public SuiClient, public SuiTransaction, public Object {
	GDCLASS(SuiSDK, Object);

protected:
	static void _bind_methods();

public:
	/**
	 * Balance
	 */
	TypedArray<BalanceWrapper> getBalances(String address) { return SuiBalance::getBalances(address); };
	TypedArray<BalanceWrapper> getAllBalancesSync(String address) { return SuiBalance::getAllBalancesSync(address); };
	Ref<BalanceWrapper> getBalanceSync(String address) { return SuiBalance::getBalanceSync(address); };
	unsigned long long int getTotalSupplySync(String address) { return SuiBalance::getTotalSupplySync(); };
	TypedArray<CoinWrapper> getCoinsSync(String address) { return SuiBalance::getCoinsSync(address); };

	/**
	 * Wallet
	 */
	TypedArray<WalletWrapper> getWallets() { return SuiWallet::getWallets(); };
	Ref<WalletWrapper> generateWallet(String key_scheme, String word_length) { return SuiWallet::generateWallet(key_scheme, word_length); };
	Ref<WalletWrapper> generateAndAddKey() { return SuiWallet::generateAndAddKey(); };
	Ref<WalletWrapper> getWalletFromAddress(String address) { return SuiWallet::getWalletFromAddress(address); };
	void importFromPrivateKey(String key_base64) { SuiWallet::importFromPrivateKey(key_base64); };
	String importFromMnemonic(String mnemonic) { return SuiWallet::importFromMnemonic(mnemonic); };

	SuiSDK();
};

} //namespace godot

#endif // GODOT_SUI_SDK_H