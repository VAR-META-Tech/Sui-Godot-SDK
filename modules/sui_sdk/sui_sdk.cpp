#include "modules/sui_sdk/sui_sdk.h"

#include "modules/sui_sdk/src/sui_balance.cpp"
#include "modules/sui_sdk/src/sui_client.cpp"
#include "modules/sui_sdk/src/sui_multisig.cpp"
#include "modules/sui_sdk/src/sui_nfts.cpp"
#include "modules/sui_sdk/src/sui_transaction.cpp"
#include "modules/sui_sdk/src/sui_wallet.cpp"
#include "modules/sui_sdk/src/sui_builder.cpp"
#include "modules/sui_sdk/src/sui_utility.cpp"

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
	ClassDB::bind_method(D_METHOD("buildDevNetwork"), &SuiSDK::buildDevNetwork);
	ClassDB::bind_method(D_METHOD("buildTestNetwork"), &SuiSDK::buildTestNetwork);
	ClassDB::bind_method(D_METHOD("buildMainNetNetwork"), &SuiSDK::buildMainNetNetwork);

	/**
	 * Multisig
	 */
	ClassDB::bind_method(D_METHOD("getOrCreateMultisig", "addresses", "weights", "threshold"), &SuiSDK::getOrCreateMultisig);
	ClassDB::bind_method(D_METHOD("createTransaction", "from_address", "to_address", "amount"), &SuiSDK::createTransaction);
	ClassDB::bind_method(D_METHOD("signAndExecuteTransaction", "multisig", "tx", "addresses"), &SuiSDK::signAndExecuteTransaction);

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
	ClassDB::bind_method(D_METHOD("importFromMnemonic", "mnemonic", "scheme", "alias"), &SuiSDK::importFromMnemonic);

	/**
	 * Transaction builder
	 */
	ClassDB::bind_method(D_METHOD("makePure", "builder", "arguments", "value"), &SuiSDK::makePure);
	ClassDB::bind_method(D_METHOD("makeObjectImmOrOwned", "builder", "arguments", "nft_id", "sender_address"), &SuiSDK::makeObjectImmOrOwned);
	ClassDB::bind_method(D_METHOD("addSplitCoinsCommand", "builder", "coin", "amount"), &SuiSDK::addSplitCoinsCommand);
	ClassDB::bind_method(D_METHOD("addTransferObjectCommand", "builder", "arguments", "recipient"), &SuiSDK::addTransferObjectCommand);
	ClassDB::bind_method(D_METHOD("addMoveCallCommand", "builder", "package", "module", "function", "type_arguments", "arguments"), &SuiSDK::addMoveCallCommand);
	ClassDB::bind_method(D_METHOD("executeTransaction", "builder", "sender_address", "gas_limit"), &SuiSDK::executeTransaction);
	ClassDB::bind_method(D_METHOD("addTypeTag", "type_tags", "tag"), &SuiSDK::addTypeTag);

	ClassDB::bind_method(D_METHOD("addArgumentGasCoin", "arguments"), &SuiSDK::addArgumentGasCoin);
	ClassDB::bind_method(D_METHOD("addArgumentResult", "arguments", "value"), &SuiSDK::addArgumentResult);
	ClassDB::bind_method(D_METHOD("addArgumentInput", "arguments", "value"), &SuiSDK::addArgumentInput);
	ClassDB::bind_method(D_METHOD("addArgumentNestedResult", "arguments", "value1", "value2"), &SuiSDK::addArgumentNestedResult);
	ClassDB::bind_method(D_METHOD("addMergeCoinsCommand", "builder", "coin", "agreements"), &SuiSDK::addMergeCoinsCommand);
	ClassDB::bind_method(D_METHOD("executeTransactionAllowSponser", "builder", "sender", "gas_budget", "sponser"), &SuiSDK::executeTransactionAllowSponser);

	/**
	 * Utility
	 */
	ClassDB::bind_method(D_METHOD("connectLocalnet"), &SuiSDK::connectLocalnet);
	ClassDB::bind_method(D_METHOD("connectDevnet"), &SuiSDK::connectDevnet);
	ClassDB::bind_method(D_METHOD("connectTestnet"), &SuiSDK::connectTestnet);
	ClassDB::bind_method(D_METHOD("availableSubscription"), &SuiSDK::availableSubscription);
	ClassDB::bind_method(D_METHOD("availableRPCMethods"), &SuiSDK::availableRPCMethods);
}