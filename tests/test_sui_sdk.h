#ifndef TEST_SUI_SDK_H
#define TEST_SUI_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "thirdparty/doctest/doctest.h"

#include "modules/sui_sdk/sui_sdk.h"

namespace TestSDK {

TEST_CASE("Get Wallets") {
	SuiSDK suiSdk;
	WalletList wallets = suiSdk.getWallets();
	CHECK(wallets.wallets != NULL);
}

} //namespace TestSDK

#endif // TEST_SUI_SDK_H