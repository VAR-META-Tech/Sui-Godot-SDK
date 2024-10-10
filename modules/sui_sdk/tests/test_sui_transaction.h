#ifndef TEST_SUI_TRANSACTION_SDK_H
#define TEST_SUI_TRANSACTION_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "utils.h"
#include <iostream>

#include "modules/sui_sdk/sui_sdk.h"
using namespace godot;
namespace TestSuiTransactionSDK
{
  SuiSDK suiSDK;

  TEST_CASE("Sign Transaction")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() < 2)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    Ref<WalletWrapper> sender = wallets[0];
    Ref<WalletWrapper> recipient = wallets[1];
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(sender->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(sender->address);
      }
      sleep(5);
    } while (enoughAmount == false);

    String result = suiSDK.signTransaction(sender->address, recipient->address, amount);
    CHECK(result == "Transaction completed successfully");
  }

  TEST_CASE("Request Transaction Faucet")
  {
    Ref<WalletWrapper> wallet;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    if (wallets.size() == 0)
    {
      wallet = suiSDK.generateAndAddKey();
    }
    else
    {
      wallet = wallets[0];
    }
    Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(wallet->address);
    suiSDK.requestTokensFromFaucet(wallet->address);
    sleep(5);
    Ref<BalanceWrapper> newBalance = suiSDK.getBalanceSync(wallet->address);
    CHECK(balance->total_balance != newBalance->total_balance);
  }

  TEST_CASE("Sign Transaction Allow Sponsor")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() < 3)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    Ref<WalletWrapper> sponsor = wallets[0];
    Ref<WalletWrapper> sender = wallets[1];
    Ref<WalletWrapper> recipient = wallets[2];
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(sponsor->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(sponsor->address);
      }
      sleep(5);
    } while (enoughAmount == false);

    String result = suiSDK.programmableTransactionAllowSponser(
        sender->address,
        recipient->address,
        amount,
        sponsor->address);
    CHECK(result == "Transaction completed successfully");
  }

  TEST_CASE("Sign Transaction Builder")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() < 2)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    Ref<WalletWrapper> sender = wallets[0];
    Ref<WalletWrapper> recipient = wallets[1];
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(sender->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(sender->address);
      }
      sleep(5);
    } while (enoughAmount == false);

    String result = suiSDK.programmableTransactionBuilder(sender->address, recipient->address, amount);
    CHECK(result != "");
  }
}

#endif