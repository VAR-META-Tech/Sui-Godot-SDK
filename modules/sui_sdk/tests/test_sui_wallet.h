#ifndef TEST_SUI_WALLET_SDK_H
#define TEST_SUI_WALLET_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"

#include "modules/sui_sdk/sui_sdk.h"

namespace TestSuiWalletSDK {

TEST_CASE("Get Wallets") {
	SuiSDK suiSDK;
	WalletList wallets = suiSDK.getWallets();
	CHECK(wallets.wallets != NULL);
}

TEST_CASE("Gen Wallet") {
	SuiSDK suiSDK;
	Wallet *wallet = suiSDK.generateWallet("ed25519", "word12");
	CHECK(wallet->mnemonic != NULL);
}

} //namespace TestSuiWalletSDK

#endif