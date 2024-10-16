#ifndef TEST_SUI_NFTS_SDK_H
#define TEST_SUI_NFTS_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "modules/sui_sdk/sui_sdk.h"
#include <iostream>
#include <string>
#include "utils.h"
using namespace std;
using namespace godot;

namespace TestSuiWalletSDK
{
  TEST_CASE("Mint & Transfer NFT")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 1)
    {
      suiSDK.generateAndAddKey();
      wallets = suiSDK.getWallets();
    }
    CHECK(wallets.size() > 1);

    Ref<WalletWrapper> walletSender = wallets[0];
    Ref<WalletWrapper> walletReceipt = wallets[0];

    String package_id = "0x99ebcdef6e51e1021eeaded8d3c7c7eb672c1b000d5ef3408d103b805b93a0a0";
    String object_type = "0x99ebcdef6e51e1021eeaded8d3c7c7eb672c1b000d5ef3408d103b805b93a0a0::nft::NFT";
    String sender_address = walletSender->address;
    String recipient_address = walletReceipt->address;
    String name = "Unit test mint nft";
    String description = "This is a unit test mint nft";
    String uri = "https://i.ibb.co/SN2bQ5P/hand-drawn-nft-style-ape-illustration-23-2149622021.jpg";

    Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(sender_address);
    int oneCoin = pow(10, 9);
    while (stoull(balance->total_balance.utf8().get_data()) < oneCoin)
    {
      suiSDK.requestTokensFromFaucet(sender_address);
      sleep(3);
      balance = suiSDK.getBalanceSync(sender_address);
    }

    String messageMint = suiSDK.mintNft(package_id, sender_address, name, description, uri);
    CHECK(messageMint == "Mint NFT to sender success");

    TypedArray<WalletObjectWrapper> walletNFTObjects = suiSDK.getWalletObjects(sender_address, object_type);
    CHECK(walletNFTObjects.size() > 0);

    Ref<WalletObjectWrapper> nft = walletNFTObjects[0];
    String nft_id = nft->get_object_id();

    String messageTransfer = suiSDK.transferNft(package_id, sender_address, nft_id, recipient_address);
    CHECK(messageTransfer == "Transfer NFT success");
  }

}

#endif