#ifndef TEST_SUI_WALLET_SDK_H
#define TEST_SUI_WALLET_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"

#include "modules/sui_sdk/sui_sdk.h"

using namespace godot;
namespace TestSuiWalletSDK
{

  TEST_CASE("Get Wallets")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    CHECK(wallets.size() != (const int)0);
  }

  TEST_CASE("Gen Wallet")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word12");
    CHECK(wallet->get_mnemonic() != "");
  }

} // namespace TestSuiWalletSDK

#endif