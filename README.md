<p align="center">
	<img src="./resources/sui_logo.png" alt="Unreal-Sui-SDKLogo" width="256" height="128" />
</p>

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

### Project Layout

1. **`project_demo/`**: This directory contains the example use.
2. **`resources/`**: A place for various resources needed for the project, like images, data files, or other assets.
3. **`modules/`**: This directory contains the project's source code.

### Features

- [x] Compatibility with main, dev, and test networks.
- [x] Comprehensive Unit and Integration Test coverage.

### Requirements

| Platforms             | Status       |
| --------------------- | ------------ |
| Mac / Linux / Windows | Fully Tested |

### Dependencies

- https://github.com/VAR-META-Tech/Rust2C-Sui-SDK

### Installation

# Installation Guide

This guide provides step-by-step instructions for installing and setting up on macOS platforms. Ensure you have the following prerequisites installed to build the project:

## Prerequisites

- **Visual Studio Code** with C++ development environment
- **Install Sui** Follow this guide to install Sui https://docs.sui.io/guides/developer/getting-started/sui-install

## Project Setup

Run follow command to setting Envỉroment befor testing:

1. Check Sui Client Environment:
   ```sh
   Sui client envs
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
   - In Sui-Godot-SDK directory run cmd:
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

### Using Sui-Godot-SDK

Sui-Godot-SDK can integrate into your own godot projects.

You can custom your `project_demo` and run below built file in directory to check your source code.

```sh
  ./godot/bin/godot.${your system name}
```

**NOTE**: 
- **If you are running on Windows system, please copy file `sui_rust_sdk.dll` at folder `modules/sui_sdk/libs` into folder `godot/bin`**
- **If you are running on Lunix system, please run cmd below to set environment variable:**
```bash 
source ./.bashrc
```

### License

This project is licensed under the Apache-2.0 License. Refer to the LICENSE file for details.
