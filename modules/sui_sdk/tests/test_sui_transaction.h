#ifndef TEST_SUI_TRANSACTION_SDK_H
#define TEST_SUI_TRANSACTION_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "utils.h"
#include <iostream>
#include <string>
#include "modules/sui_sdk/sui_sdk.h"
using namespace godot;
using namespace std;

namespace TestSuiTransactionSDK
{
  SuiSDK suiSDK;

  TEST_CASE("Sign transaction")
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

  TEST_CASE("Request transaction faucet")
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

  TEST_CASE("Sign transaction allow sponsor")
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

  TEST_CASE("Sign transaction builder")
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

    SuiProgrammableTransactionBuilder *builder = memnew(SuiProgrammableTransactionBuilder);
    SuiArguments *coin = memnew(SuiArguments);
    suiSDK.addArgumentGasCoin(coin);

    SuiArguments *amountArg = memnew(SuiArguments);
    SuiBSCBasic *amountBscBasic = memnew(SuiBSCBasic);

    amountBscBasic->BSCBasic("u64", String::num_uint64(amount));

    suiSDK.makePure(builder, amountArg, amountBscBasic);
    suiSDK.addSplitCoinsCommand(builder, coin, amountArg);

    SuiArguments *argument = memnew(SuiArguments);
    suiSDK.addArgumentResult(argument, 0);
    SuiArguments *recipientArg = memnew(SuiArguments);
    SuiBSCBasic *recipientBscBasic = memnew(SuiBSCBasic);
    recipientBscBasic->BSCBasic("address", recipient->address);
    suiSDK.makePure(builder, recipientArg, recipientBscBasic);
    suiSDK.addTransferObjectCommand(builder, argument, recipientArg);

    String result = suiSDK.executeTransaction(builder, sender->address, gas);
    memdelete(builder);
    memdelete(amountArg);
    memdelete(amountBscBasic);
    memdelete(argument);
    memdelete(recipientArg);
    memdelete(recipientBscBasic);

    CHECK(result != "");
  }

  TEST_CASE("Sign transaction don't have enough balance")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() < 2)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    Ref<WalletWrapper> sender = wallets[0];
    Ref<WalletWrapper> recipient = wallets[1];
    Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(sender->address);
    uint64_t amount = stoull(balance->total_balance.utf8().get_data()) + 500 * pow(10, 9);
    String result = suiSDK.signTransaction(sender->address, recipient->address, amount);
    CHECK(result == "Error: Transaction failed");
  }
  TEST_CASE("Sign transaction builder allow sponser")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() < 3)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    Ref<WalletWrapper> sender = wallets[0];
    Ref<WalletWrapper> recipient = wallets[1];
    Ref<WalletWrapper> sponser = wallets[2];
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(sponser->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(sponser->address);
      }
      sleep(5);
    } while (enoughAmount == false);

    SuiProgrammableTransactionBuilder *builder = memnew(SuiProgrammableTransactionBuilder);
    SuiArguments *coin = memnew(SuiArguments);
    suiSDK.addArgumentGasCoin(coin);

    SuiArguments *amountArg = memnew(SuiArguments);
    SuiBSCBasic *amountBscBasic = memnew(SuiBSCBasic);

    amountBscBasic->BSCBasic("u64", String::num_uint64(amount));

    suiSDK.makePure(builder, amountArg, amountBscBasic);
    suiSDK.addSplitCoinsCommand(builder, coin, amountArg);

    SuiArguments *argument = memnew(SuiArguments);
    suiSDK.addArgumentResult(argument, 0);
    SuiArguments *recipientArg = memnew(SuiArguments);
    SuiBSCBasic *recipientBscBasic = memnew(SuiBSCBasic);
    recipientBscBasic->BSCBasic("address", recipient->address);
    suiSDK.makePure(builder, recipientArg, recipientBscBasic);
    suiSDK.addTransferObjectCommand(builder, argument, recipientArg);

    String result = suiSDK.executeTransactionAllowSponser(builder, sender->address, gas, sponser->address);
    memdelete(builder);
    memdelete(amountArg);
    memdelete(amountBscBasic);
    memdelete(argument);
    memdelete(recipientArg);
    memdelete(recipientBscBasic);

    CHECK(result != "");
  }

}

#endif