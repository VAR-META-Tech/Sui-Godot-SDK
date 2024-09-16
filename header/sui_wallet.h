// rust_functions.h
#ifndef SUI_WALLET_H
#define SUI_WALLET_H
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // Wallet

    // Define the Wallet struct matching the Rust struct
    typedef struct
    {
        char *address;
        char *mnemonic;
        char *public_base64_key;
        char *private_key;
        char *key_scheme;
    } Wallet;

    typedef struct WalletList
    {
        Wallet *wallets;
        size_t length;
    } WalletList;

    // Declare the functions from the Rust library
    extern WalletList get_wallets();
    extern void free_wallet_list(WalletList wallet_list);
    extern Wallet *generate_wallet(const char *key_scheme, const char *word_length);
    extern Wallet *generate_and_add_key();
    extern Wallet *get_wallet_from_address(const char *address);
    extern void free_wallet(Wallet *wallet);
    extern void import_from_private_key(const char *key_base64);
    extern char *import_from_mnemonic(const char *mnemonic);

#ifdef __cplusplus
}
#endif

#endif // SUI_WALLET_H
