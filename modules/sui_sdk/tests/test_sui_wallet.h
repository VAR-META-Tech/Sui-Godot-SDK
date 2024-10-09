#ifndef TEST_SUI_WALLET_SDK_H
#define TEST_SUI_WALLET_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"

#include "modules/sui_sdk/sui_sdk.h"

using namespace godot;
namespace TestSuiWalletSDK
{
  SuiSDK suiSDK;

  TEST_CASE("Get Wallets")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    CHECK(wallets.size() != (const int)0);
  }

  TEST_CASE("Gen wallet")
  {
    Ref<WalletWrapper> wallets = suiSDK.generateAndAddKey();
    CHECK(wallets->address != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word12")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word12");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word12")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word12");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word12")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word12");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word15")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word15");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word15")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word15");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word15")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word15");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word18")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word18");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word18")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word18");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word18")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word18");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word21")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word21");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word21")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word21");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word21")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word21");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Ed25519-Word24")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word24");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-word24")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256k1", "word24");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Gen Wallet Custom Secp256k1-Word24")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("Secp256r1", "word24");
    CHECK(wallet->mnemonic != "");
  }

  TEST_CASE("Import Wallet from PrivateKey")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word12");
    String private_key = wallet->private_key;
    Ref<ImportResultWrapper> importResult = suiSDK.importFromPrivateKey(private_key);
    CHECK(importResult->status == 0);
    CHECK(importResult->address == wallet->address);
  }

  TEST_CASE("Import Wallet from Mnemonic")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word12");
    String mnemonic = wallet->mnemonic;
    String scheme = wallet->key_scheme;
    String alias = "test";
    Ref<ImportResultWrapper> importResult = suiSDK.importFromMnemonic(mnemonic, scheme, alias);
    CHECK(importResult->status == 0);
    CHECK(importResult->address == wallet->address);
  }

  TEST_CASE("Get Wallet From Address")
  {
    Ref<WalletWrapper> wallet = suiSDK.generateWallet("ed25519", "word12");
    String address = wallet->address;
    Ref<WalletWrapper> walletResult = suiSDK.getWalletFromAddress(address);
    CHECK(walletResult->address == address);
  }

}

#endif