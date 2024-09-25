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
	ClassDB::bind_method(D_METHOD("apiVersion"), &SuiSDK::apiVersion);
	ClassDB::bind_method(D_METHOD("checkApiVersion"), &SuiSDK::checkApiVersion);

	/**
	 * Multisig
	 */
	ClassDB::bind_method(D_METHOD("getOrCreateMultisig", "addresses", "weights", "threshold"), &SuiSDK::getOrCreateMultisig);
	ClassDB::bind_method(D_METHOD("createTransaction", "from_address", "to_address", "amount"), &SuiSDK::createTransaction);

	/**
	 * NFTs
	 */
	ClassDB::bind_method(D_METHOD("getWalletObjects", "address", "object_type"), &SuiSDK::getWalletObjects);
	ClassDB::bind_method(D_METHOD("mintNft", "package_id", "sender_address", "name", "description", "uri"), &SuiSDK::mintNft);
	ClassDB::bind_method(D_METHOD("transferNft", "package_id", "sender_address", "nft_id", "recipient_address"), &SuiSDK::transferNft);

	/**
	 * Transaction
	 */
	ClassDB::bind_method(D_METHOD("signTransaction", "sender_address", "recipient_address", "amount"), &SuiSDK::signTransaction);
	ClassDB::bind_method(D_METHOD("programmableTransactionAllowSponser", "sender_address", "recipient_address", "amount", "sponser_address"), &SuiSDK::programmableTransactionAllowSponser);
	ClassDB::bind_method(D_METHOD("requestTokensFromFaucet", "address"), &SuiSDK::requestTokensFromFaucet);

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