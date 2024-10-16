![645bca632d1c27a85cee236d_sui-logo8d3c44e](https://github.com/user-attachments/assets/5b74fbae-1a87-427d-9c57-8bc164ca09cb)

# Sui-Godot-SDK

Sui-Godot-SDK is a package to help developers integrate Sui blockchain technology into their godot projects.

- [Project Layout](#project-layout)
- [Features](#features)
- [Requirements](#requirements)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Using Sui-Godot-SDK](#using-rust2c-sui-sdk)
- [Examples](#examples)
- [License](#license)

### Project Structure

1. **`project_demo/`**: This directory contains the example use.
2. **`resources/`**: A place for various resources needed for the project, like images, data files, or other assets.
3. **`modules/`**: This directory contains the project's source code.

### Features

#### General

- [x] Compatibility with main, dev, and test networks.
- [x] Integration with Sui blockchain using native libraries.
- [x] Cross-platform support (macOS, Windows, Linux).

#### sui_nfts.cpp

- [x] Mint new NFTs.
- [x] Transfer NFTs to other addresses.
- [x] Retrieve wallet objects related to NFTs.
- [x] Conversion between raw and managed data structures for NFT objects.

#### sui_multisig.cpp

- [x] Create and manage multisig wallets.
- [x] Create transactions from multisig wallets.
- [x] Sign and execute transactions using multisig wallets.
- [x] Handling of multisig data structures and transaction results.

#### sui_builder.cpp

- [x] Basic serialization and deserialization of Sui types.
- [x] Support for various Sui types including integers, floats, booleans, strings, and addresses.
- [x] Conversion of Sui types to BCS (Binary Canonical Serialization) format.
- [x] Create and manage transaction builders.
- [x] Add various types of commands to transactions (e.g., move call, transfer object, split coins, merge coins).
- [x] Execute transactions with or without a sponsor.

#### sui_wallet.cpp

- [x] Singleton pattern for easy access to wallet functionalities.
- [x] Generate new wallets with specified key schemes and word lengths.
- [x] Import wallets from private keys.
- [x] Import wallets from mnemonics.
- [x] List all wallets.
- [x] Display wallet details.
- [x] Generate and add new keys to the wallet.

### Requirements

| Platforms             | Godot Version | Status       |
| --------------------- | ------------- | ------------ |
| Mac / Linux / Windows | Godot 4.3     | Fully Tested |

### Dependencies

- https://github.com/VAR-META-Tech/Rust2C-Sui-SDK

### Installation

# Installation Guide

This guide provides step-by-step instructions for installing and setting up on macOS / Linus / Windows platforms. Ensure you have the following prerequisites installed to build the project:

## Prerequisites

- **Visual Studio Code** with C++ development environment
- **Install Sui** Follow this guide to install Sui <https://docs.sui.io/guides/developer/getting-started/sui-install>

## Project Setup

Run follow command to setting Environment before testing:

1. Check Sui Client Environment:

   ```sh
   sui client envs
   ```

   **NOTE:If you don't have DevNet, please run CMD :**

   ```sh
   sui client new-env --alias devnet --rpc https://fullnode.devnet.sui.io:443
   ```

2. Switch to devnet network:

   ```sh
   sui client switch --env devnet
   ```

3. Check current network:

   ```sh
   sui client active-env
   ```

   **NOTE: The return should be devnet**

4. Get the active address:

   ```sh
   sui client active-address
   ```

5. Request token:

   ```sh
   sui client faucet
   ```

   **NOTE: Wait for 60s to get the tokens**

6. Check the gas coin objects for the active address:

   ```sh
   sui client gas
   ```

7. Build Project:

   - In Sui-Godot-SDK directory run CMD:

   ```sh
   git clone -b 4.3 https://github.com/godotengine/godot
   ```

   - Change working directory to godot:

   ```sh
   cd godot
   ```

   - Build project cmd:

   ```sh
   scons custom_modules=../modules
   ```

### Install Sui-Godot-SDK

- Get godot engine: In Sui-Godot-SDK directory run CMD:

  ```sh
  git clone -b 4.3 https://github.com/godotengine/godot
  ```

- Compile the engine:
  ```sh
  cd godot
  scons custom_modules=../modules
  ```

Sui-Godot-SDK can integrate into your own godot projects.

You can custom your `project_demo` and run below built file in directory to check your source code.

```sh
./godot/bin/<godot_binary>
```

**NOTE**:

- **If you are running on Windows environment, please copy file `sui_rust_sdk.dll` at `modules/sui_sdk/libs` directory into `godot/bin` directory**
- **If you are running on Linux environment, please run cmd below to set environment variable:**

  ```bash
  source ./.bashrc
  ```

### Examples

The SDK comes with several examples that show how to leverage the Rust2C-Sui-SDK to its full potential. The examples include Wallet Creation and Management, Token Transfers, NFT Minting, Account Funding, and Multi-signature.

#### Initialize the SDK

```gdscript
var suiSDK = SuiSDK.new()
```

#### Wallet

The `SuiWallet` class provides various functionalities to manage wallets in your Unity project. Below are some examples of how touse the `SuiWallet` class.

##### Generate a New Wallet

To generate a new wallet with a specified key scheme and word length:

```gdscript
var newWallet = suiSDK.generateWallet("ED25519", "12")
print(wallet.get_address())
print(wallet.get_mnemonic())
print(wallet.get_public_base64_key())
print(wallet.get_private_key())
print(wallet.get_key_scheme())
```

##### Import Wallet from Private Key

To import a wallet using a private key:

```gdscript
var importResult = suiSDK.importFromPrivateKey("your_private_key_here")
if importResult.get_status() == 0:
   print("Import wallet " + importResult.get_address() + " successfully")
else:
   print(importResult.get_error())
```

##### Import Wallet from Mnemonic

To import a wallet using a mnemonic phrase:

```gdscript
var importResult = suiSDK.importFromMnemonic("your_mnemonic_phrase_here")
if importResult.get_status() == 0:
   print("Import wallet " + importResult.get_address() + " successfully")
else:
   print(importResult.get_error())
```

##### List All Wallets

To list all wallets:

```gdscript
var wallets = suiSDK.getWallets()
for wallet in wallets:
   print(wallet.get_address())
   print(wallet.get_mnemonic())
   print(wallet.get_public_base64_key())
   print(wallet.get_private_key())
   print(wallet.get_key_scheme())
```

##### Generate and Add New Key

To generate and add a new key to the wallet:

```gdscript
var wallet = sdk.generateAndAddKey()
```

#### Transactions

The `SuiTransactionBuilder` class allows you to create and manage transactions. Below are some examples of how to use the `SuiTransactionBuilder` class.

##### Create a New Transaction

To create a new transaction:

```gdscript
var builder = SuiProgrammableTransactionBuilder.new()
```

##### Add a Move Call Command

To add a move call command to the transaction:

```gdscript
var arguments = SuiArguments.new()
var typeTag = SuiTypeTags.new()
suiSDK.addMoveCallCommand(builder, "package_id", "module_name", "function_name", typeTag, arguments)
```

##### Add a Transfer Object Command

To add a transfer object command to the transaction:

```gdscript
var agreements = SuiArguments.new()
var recipient = SuiArguments.new()
suiSDK.addTransferObjectCommand(builder, agreements, recipient)
```

##### Execute the Transaction

To execute the transaction:

```gdscript
var gas = 0.005 * 10**9
var result = suiSDK.executeTransaction(builder, "sender_address", gas)
print(result)
```

#### Basic Serialization and Deserialization

The `sui_builder` provides methods for basic serialization and deserialization of Sui types. Below are some examples of how to use the `sui_builder`.

##### Serialize Data

To serialize data of a specific Sui type:

```gdscript
var amount = 1;
var amountBscBasic = SuiBSCBasic.new()
amountBscBasic.BSCBasic("u64", str(int(amount)*10**9))
```

#### Multisig Wallets

The `sui_multisig` provides functionalities to create and manage multisig wallets. Below are some examples of how to use the `sui_multisig`.

##### Create a Multisig Wallet

To create a new multisig wallet:

```gdscript
var address1 = "wallet_address_1"
var address2 = "wallet_address_2"
var address3 = "wallet_address_3"
var addresses = [address1, address2, address3]
var weights = [1, 1, 2]
var multiSig = suiSDK.getOrCreateMultisig(addresses, weights, 3)
```

##### Create a Transaction from Multisig Wallet

To create a transaction from a multisig wallet:

```gdscript
var amount = 1 *10**9
var txBytes = suiSDK.createTransaction("wallet_address", "wallet_address", amount)
```

##### Sign and Execute a Multisig Transaction

To sign and execute a transaction using a multisig wallet:

```gdscript
string result = multisigWallet.SignAndExecuteTransaction(transactionBuilder, "signer_address");
Debug.Log(result);

var address1 = "wallet_address_1"
var address2 = "wallet_address_2"
var address3 = "wallet_address_3"
var signer_addresses = [address2, address3]
var message = suiSDK.signAndExecuteTransaction(multiSig, txBytes, signer_addresses)
print(message)
```

#### NFT Operations

The `sui_nfts` provides functionalities to mint, transfer, and retrieve NFT-related wallet objects. Below are some examples of how to use the `sui_nfts`.

##### Mint a New NFT

To mint a new NFT:

```gdscript
var message = suiSDK.mintNft("package_id", "sender_address", "NFT Name", "NFT Description", "NFT URI")
print(message)
```

##### Transfer an NFT

To transfer an NFT to another address:

```gdscript
var message = suiSDK.transferNft("package_id", "sender_address", "nft_id", "recipient_address")
print(message)
```

##### Retrieve Wallet Objects

To retrieve wallet objects related to NFTs:

```gdscript
var nfts = suiSDK.getWalletObjects("wallet_address", "object_type")
```

### License

This project is licensed under the Apache-2.0 License. Refer to the LICENSE file for details.
