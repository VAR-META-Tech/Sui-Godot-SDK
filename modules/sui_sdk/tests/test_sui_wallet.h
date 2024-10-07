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

  TEST_CASE("Gen wallet")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallets = suiSDK.generateAndAddKey();
    CHECK(wallets->address != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word12")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word12");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word12")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word12");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word12")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word12");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word15")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word15");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word15")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word15");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word15")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word15");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word18")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word18");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word18")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word18");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word18")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word18");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word21")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word21");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word21")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word21");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word21")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word21");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word24")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word24");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word24")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word24");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word24")
  {
    SuiSDK suiSDK;
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word24");
    CHECK(wallet->get_mnemonic() != "");
  }

  TEST_CASE("Import Wallet from PrivateKey")
  {
    SuiSDK suiSDK;
    String private_key = "ANP7YuU7I0NnwHMJGlRraQ7hcW3XekCecvEysqUTC8Ue";
    Ref<ImportResultWrapper> importResult = suiSDK.importFromPrivateKey(private_key);
    CHECK(importResult->status == 0);
    CHECK(importResult->address == "0x552ae47bb91c3eae96e41bfab4aea7b4ca3d1722158d11e5cc8188f8182401e3");
  }

  TEST_CASE("Import Wallet from Mnemonic")
  {
    SuiSDK suiSDK;
    String mnemonic = "naive sheriff vehicle hold latin network menu track sniff salon train moon";
    const char *scheme = "ED25519";
    const char *alias = "test";
    Ref<ImportResultWrapper> importResult = suiSDK.importFromMnemonic(mnemonic, scheme, alias);
    CHECK(importResult->status == 0);
    CHECK(importResult->address == "0xfee0108a2467a551f50f3f7c2dc77128406ae314ef4515030dc62accb0c15bcc");
  }

  TEST_CASE("Get Wallet From Address")
  {
    SuiSDK suiSDK;
    String address = "0x552ae47bb91c3eae96e41bfab4aea7b4ca3d1722158d11e5cc8188f8182401e3";
    Ref<WalletWrapper> wallet = suiSDK.getWalletFromAddress(address);
    CHECK(wallet->get_address() == address);
  }

}

#endif