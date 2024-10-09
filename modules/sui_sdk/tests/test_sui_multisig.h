#ifndef TEST_SUI_MULTISIG_SDK_H
#define TEST_SUI_MULTISIG_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "utils.h"

#include "modules/sui_sdk/sui_sdk.h"

using namespace godot;
namespace TestSuiMultisigSDK
{
  TEST_CASE("Sign multisig successfully")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 3)
    {
      suiSDK.generateWallet("ed25519", "word12");
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
    suiSDK.requestTokensFromFaucet(multisig->address);
    sleep(5);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], 1000);
    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addresses);

    CHECK(message == "Sign and execute transaction success");
  }

  TEST_CASE("Sign multisig don't enough signatures confirm")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 3)
    {
      suiSDK.generateWallet("ed25519", "word12");
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

    Ref<MulSigWrapper> multisig = suiSDK.getOrCreateMultisig(addresses, weights, threshold);
    suiSDK.requestTokensFromFaucet(multisig->address);
    sleep(5);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], 1000);
    TypedArray<String> addressesConfirm;
    Ref<WalletWrapper> wallet = wallets[0];
    addressesConfirm.append(wallet->address);

    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addressesConfirm);
    CHECK(message != "Sign and execute transaction success");
  }

  TEST_CASE("Wallet confirm is not exist in multisig")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 4)
    {
      suiSDK.generateWallet("ed25519", "word12");
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

    Ref<MulSigWrapper> multisig = suiSDK.getOrCreateMultisig(addresses, weights, threshold);
    suiSDK.requestTokensFromFaucet(multisig->address);
    sleep(5);
    TypedArray<uint8_t> tx = suiSDK.createTransaction(multisig->address, addresses[2], 1000);
    TypedArray<String> addressesConfirm;
    Ref<WalletWrapper> wallet = wallets[3];
    addressesConfirm.append(wallet->address);

    String message = suiSDK.signAndExecuteTransaction(multisig, tx, addressesConfirm);
    printf("message: %s\n", message.utf8().get_data());
    CHECK(message != "Sign and execute transaction success");
  }
}

#endif