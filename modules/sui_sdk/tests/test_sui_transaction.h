#ifndef TEST_SUI_TRANSACTION_SDK_H
#define TEST_SUI_TRANSACTION_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#ifdef _WIN32
#include <windows.h>
#define SLEEP(milliseconds) Sleep(milliseconds * 1000)
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
#endif

#include "modules/sui_sdk/sui_sdk.h"
using namespace godot;
namespace TestSuiTransactionSDK
{

  TEST_CASE("Sign Transaction")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    if (wallets.size() < 2)
    {
      CHECK(false);
    }

    Ref<WalletWrapper> sender = wallets[0];
    Ref<WalletWrapper> recipient = wallets[1];
    unsigned long long amount = 10000000;

    String result = suiSDK.signTransaction(sender->get_address(), recipient->get_address(), amount);
    CHECK(result == "Transaction completed successfully");
  }

  TEST_CASE("Sign Transaction Faucet")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    if (wallets.size() < 1)
    {
      CHECK(false);
    }
    Ref<WalletWrapper> sponser = wallets[0];
    suiSDK.requestTokensFromFaucet(sponser->get_address());
    SLEEP(5);
  }

  TEST_CASE("Sign Transaction Allow Sponser")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    if (wallets.size() < 3)
    {
      CHECK(false);
    }

    Ref<WalletWrapper> sponser = wallets[0];
    Ref<WalletWrapper> sender = wallets[1];
    Ref<WalletWrapper> recipient = wallets[2];
    unsigned long long amount = 10000000;

    String result = suiSDK.programmableTransactionAllowSponser(
        sender->get_address(),
        recipient->get_address(),
        amount,
        sponser->get_address());
    CHECK(result == "Transaction completed successfully");
  }

}

#endif