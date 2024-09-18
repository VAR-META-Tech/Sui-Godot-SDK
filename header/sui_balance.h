// rust_functions.h
#ifndef SUI_BALANCE_H
#define SUI_BALANCE_H
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#ifdef __cplusplus
extern "C"
{
#endif
    // Define the Balance struct
    typedef struct
    {
        char *coin_type;
        size_t coin_object_count;
        uint64_t total_balance[2];
    } Balance;

    // Define the BalanceArray struct
    typedef struct
    {
        Balance *balances;
        size_t length;
    } BalanceArray;

    // Define the C struct for Coin
    typedef struct
    {
        char *coin_type;
        char *coin_object_id;
        uint64_t version;
        char *digest;
        uint64_t balance;
        char *previous_transaction;
    } CCoin;

    // Define the C struct for an array of CCoin
    typedef struct
    {
        CCoin *coins;
        size_t length;
    } CCoinArray;
    // Declare the C functions
    extern BalanceArray get_balances(const char *address);
    extern BalanceArray get_all_balances_sync(const char *address);
    extern void free_balance_array(BalanceArray balance_array);
    extern Balance get_balance_sync(const char *address);
    extern void free_balance(Balance balance);
    extern uint64_t get_total_supply_sync();
    extern CCoinArray get_coins_sync(const char *address);
    extern void free_coin_array(CCoinArray coins);

#ifdef __cplusplus
}
#endif

#endif // SUI_BALANCE_H
