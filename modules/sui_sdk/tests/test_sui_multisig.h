#ifndef TEST_SUI_MULTISIG_SDK_H
#define TEST_SUI_MULTISIG_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "utils.h"
#include <iostream>
#include "modules/sui_sdk/sui_sdk.h"

using namespace std;
using namespace godot;

namespace TestSuiMultisigSDK
{
  SuiSDK suiSDK;
  TEST_CASE("Sign multisig successfully")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 3)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    CHECK(wallets.size() > 3);

    TypedArray<String> addresses;
    for (size_t i = 0; i < 3; i++)
    {
      Ref<WalletWrapper> wallet = wallets[i];
      addresses.append(wallet->address);
    }

    TypedArray<uint8_t> weights;
    for (uint8_t i = 0; i < 3; i++)
    {
      weights.append(i + 1);
    }

    uint16_t threshold = 1;

    Ref<MulSigWrapper> multisig = suiSDK.getOrCreateMultisig(addresses, weights, threshold);
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(multisig->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(multisig->address);
      }
      sleep(5);
    } while (enoughAmount == false);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], amount);
    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addresses);

    CHECK(message == "Sign and execute transaction success");
  }

  TEST_CASE("Sign multisig don't enough signatures confirm")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 3)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }
    CHECK(wallets.size() > 3);

    TypedArray<String> addresses;
    for (size_t i = 0; i < 3; i++)
    {
      Ref<WalletWrapper> wallet = wallets[i];
      addresses.append(wallet->address);
    }

    TypedArray<uint8_t> weights;
    for (uint8_t i = 0; i < 3; i++)
    {
      weights.append(i + 1);
    }

    uint16_t threshold = 3;
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    Ref<MulSigWrapper> multisig = suiSDK.getOrCreateMultisig(addresses, weights, threshold);
    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(multisig->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(multisig->address);
      }
      sleep(5);
    } while (enoughAmount == false);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], amount);
    TypedArray<String> addressesConfirm;
    Ref<WalletWrapper> wallet = wallets[0];
    addressesConfirm.append(wallet->address);

    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addressesConfirm);
    CHECK(message != "Sign and execute transaction success");
  }

  TEST_CASE("Wallet confirm is not exist in multisig")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 4)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    CHECK(wallets.size() > 4);

    TypedArray<String> addresses;
    for (size_t i = 0; i < 3; i++)
    {
      Ref<WalletWrapper> wallet = wallets[i];
      addresses.append(wallet->address);
    }

    TypedArray<uint8_t> weights;
    for (uint8_t i = 0; i < 3; i++)
    {
      weights.append(i + 1);
    }

    uint16_t threshold = 3;
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    Ref<MulSigWrapper> multisig = suiSDK.getOrCreateMultisig(addresses, weights, threshold);
    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(multisig->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(multisig->address);
      }
      sleep(5);
    } while (enoughAmount == false);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], amount);
    TypedArray<String> addressesConfirm;
    Ref<WalletWrapper> wallet = wallets[3];
    addressesConfirm.append(wallet->address);

    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addressesConfirm);
    printf("message: %s\n", message.utf8().get_data());
    CHECK(message != "Sign and execute transaction success");
  }

  TEST_CASE("Duplicate wallet in multisig")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() < 2)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    CHECK(wallets.size() >= 2);

    TypedArray<String> addresses;
    Ref<WalletWrapper> wallet1 = wallets[0];
    Ref<WalletWrapper> wallet2 = wallets[1];

    addresses.append(wallet1->address);
    addresses.append(wallet1->address);
    addresses.append(wallet2->address);

    TypedArray<uint8_t> weights;
    weights.append(1);
    weights.append(1);
    weights.append(2);

    uint16_t threshold = 1;
    uint64_t amount = pow(10, 9);
    uint64_t gas = 0.005 * pow(10, 9);

    Ref<MulSigWrapper> multisig = suiSDK.getOrCreateMultisig(addresses, weights, threshold);
    bool enoughAmount = false;
    do
    {
      Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(multisig->address);
      enoughAmount = stoull(balance->total_balance.utf8().get_data()) >= amount + gas;
      if (!enoughAmount)
      {
        suiSDK.requestTokensFromFaucet(multisig->address);
      }
      sleep(5);
    } while (enoughAmount == false);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], amount);
    TypedArray<String> addressesConfirm;
    addressesConfirm.append(wallet1->address);
    addressesConfirm.append(wallet2->address);

    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addressesConfirm);
    printf("message: %s\n", message.utf8().get_data());
    CHECK(message != "Sign and execute transaction success");
  }

  TEST_CASE("Don't enough gas")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 3)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    CHECK(wallets.size() > 3);

    TypedArray<String> addresses;
    for (size_t i = 0; i < 3; i++)
    {
      Ref<WalletWrapper> wallet = wallets[i];
      addresses.append(wallet->address);
    }

    TypedArray<uint8_t> weights;
    for (uint8_t i = 0; i < 3; i++)
    {
      weights.append(i + 1);
    }

    uint16_t threshold = 1;
    uint64_t amount = 9999 * pow(10, 9);

    Ref<MulSigWrapper> multisig = suiSDK.getOrCreateMultisig(addresses, weights, threshold);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], amount);
    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addresses);
    CHECK(message != "Sign and execute transaction success");
  }
}

#endif