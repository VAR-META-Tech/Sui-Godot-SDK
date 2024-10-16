#ifndef TEST_SUI_BUILDER_SDK_H
#define TEST_SUI_BUILDER_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "utils.h"
#include <iostream>
#include <string>
#include "modules/sui_sdk/sui_sdk.h"
using namespace godot;
using namespace std;

namespace TestSuiBuilderSDK
{
  SuiSDK suiSDK;
  String package_id = "0x99ebcdef6e51e1021eeaded8d3c7c7eb672c1b000d5ef3408d103b805b93a0a0";
  String object_type = "0x99ebcdef6e51e1021eeaded8d3c7c7eb672c1b000d5ef3408d103b805b93a0a0::nft::NFT";

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

  TEST_CASE("Sign transaction builder mint & transfer NFT")
  {
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() < 2)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }

    /** Test Mint NFT */
    Ref<WalletWrapper> sender = wallets[0];
    Ref<WalletWrapper> recipient = wallets[1];
    String nftName = "Unit test mint nft";
    String nftDescription = "This is a unit test mint nft";
    String nftUri = "https://i.ibb.co/SN2bQ5P/hand-drawn-nft-style-ape-illustration-23-2149622021.jpg";

    Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(sender->address);
    uint64_t gas = 0.005 * pow(10, 9);
    int oneCoin = pow(10, 9);
    while (stoull(balance->total_balance.utf8().get_data()) < oneCoin)
    {
      suiSDK.requestTokensFromFaucet(sender->address);
      sleep(3);
      balance = suiSDK.getBalanceSync(sender->address);
    }

    SuiProgrammableTransactionBuilder *builderMintNFT = memnew(SuiProgrammableTransactionBuilder);
    SuiArguments *argumentMintNFT = memnew(SuiArguments);
    SuiBSCBasic *nameBscBasic = memnew(SuiBSCBasic);
    SuiBSCBasic *descriptionBscBasic = memnew(SuiBSCBasic);
    SuiBSCBasic *uriBscBasic = memnew(SuiBSCBasic);

    nameBscBasic->BSCBasic("string", nftName);
    descriptionBscBasic->BSCBasic("string", nftDescription);
    uriBscBasic->BSCBasic("string", nftUri);

    suiSDK.makePure(builderMintNFT, argumentMintNFT, nameBscBasic);
    suiSDK.makePure(builderMintNFT, argumentMintNFT, descriptionBscBasic);
    suiSDK.makePure(builderMintNFT, argumentMintNFT, uriBscBasic);

    SuiTypeTags *typeTag = memnew(SuiTypeTags);
    suiSDK.addMoveCallCommand(builderMintNFT, package_id, "nft", "mint_to_sender", typeTag, argumentMintNFT);
    String minNFTResult = suiSDK.executeTransaction(builderMintNFT, sender->address, gas);
    memdelete(builderMintNFT);
    memdelete(argumentMintNFT);

    CHECK(minNFTResult != "");

    SuiProgrammableTransactionBuilder *builderTransferNFT = memnew(SuiProgrammableTransactionBuilder);
    /** Test transfer NFT */
    TypedArray<WalletObjectWrapper> walletNFTObjects = suiSDK.getWalletObjects(sender->address, object_type);
    CHECK(walletNFTObjects.size() > 0);

    Ref<WalletObjectWrapper> nft = walletNFTObjects[0];
    SuiArguments *argumentTransferNFT = memnew(SuiArguments);
    SuiBSCBasic *recipientBscBasic = memnew(SuiBSCBasic);

    recipientBscBasic->BSCBasic("string", recipient->address);

    suiSDK.makeObjectImmOrOwned(builderTransferNFT, argumentTransferNFT, nft->get_object_id(), sender->address);
    suiSDK.makePure(builderTransferNFT, argumentTransferNFT, recipientBscBasic);

    suiSDK.addMoveCallCommand(builderTransferNFT, package_id, "nft", "transfer", typeTag, argumentTransferNFT);
    String transferNFTResult = suiSDK.executeTransaction(builderTransferNFT, sender->address, gas);
    memdelete(builderTransferNFT);
    memdelete(argumentTransferNFT);
    memdelete(recipientBscBasic);

    CHECK(transferNFTResult != "");
  }
}

#endif