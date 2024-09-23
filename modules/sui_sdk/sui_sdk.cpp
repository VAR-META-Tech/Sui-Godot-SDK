#include "modules/sui_sdk/sui_sdk.h"

#include "modules/sui_sdk/src/sui_balance.cpp"
#include "modules/sui_sdk/src/sui_client.cpp"
#include "modules/sui_sdk/src/sui_multisig.cpp"
#include "modules/sui_sdk/src/sui_nfts.cpp"
#include "modules/sui_sdk/src/sui_transaction.cpp"
#include "modules/sui_sdk/src/sui_wallet.cpp"

using namespace godot;

SuiSDK::SuiSDK()
{
}

void print_wallet(const Wallet *wallet)
{
	printf("Wallet Address: %s\n", wallet->address ? wallet->address : "Not set");
	printf("Mnemonic: %s\n", wallet->mnemonic ? wallet->mnemonic : "Not set");
	printf("Public Base64 Key: %s\n", wallet->public_base64_key ? wallet->public_base64_key : "Not set");
	printf("Private Key: %s\n", wallet->private_key ? wallet->private_key : "Not set");
	printf("Key Scheme: %s\n", wallet->key_scheme ? wallet->key_scheme : "Not set");
	printf("\n");
}

void SuiSDK::_bind_methods()
{
	/**
	 * Balance
	 */
	ClassDB::bind_method(D_METHOD("getBalances", "address"), &SuiSDK::getBalances);
	ClassDB::bind_method(D_METHOD("getAllBalancesSync", "address"), &SuiSDK::getAllBalancesSync);
	ClassDB::bind_method(D_METHOD("getBalanceSync", "address"), &SuiSDK::getBalanceSync);
	ClassDB::bind_method(D_METHOD("getTotalSupplySync"), &SuiSDK::getTotalSupplySync);
	ClassDB::bind_method(D_METHOD("getCoinsSync", "address"), &SuiSDK::getCoinsSync);

	/**
	 * Client
	 */

	/**
	 * Multisig
	 */

	/**
	 * NFTs
	 */

	/**
	 * Transaction
	 */

	/**
	 * Wallet
	 */
	ClassDB::bind_method(D_METHOD("getWallets"), &SuiSDK::getWallets);
	ClassDB::bind_method(D_METHOD("generateWallet", "key_scheme", "word_length"), &SuiSDK::generateWallet);
	ClassDB::bind_method(D_METHOD("generateAndAddKey"), &SuiSDK::generateAndAddKey);
	ClassDB::bind_method(D_METHOD("getWalletFromAddress", "address"), &SuiSDK::getWalletFromAddress);
	ClassDB::bind_method(D_METHOD("importFromPrivateKey", "key_base64"), &SuiSDK::importFromPrivateKey);
	ClassDB::bind_method(D_METHOD("importFromMnemonic", "mnemonic"), &SuiSDK::importFromMnemonic);

	// ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &GDExample::set_amplitude);
	// ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");
}