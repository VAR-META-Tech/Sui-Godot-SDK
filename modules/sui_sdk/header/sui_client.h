// rust_functions.h
#ifndef SUI_CLIENT_H
#define SUI_CLIENT_H
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#ifdef __cplusplus
extern "C"
{
#endif

    // Struct to hold C-compatible string array
    typedef struct
    {
        const char **data;
        int len;
    } CStringArray;

    // Struct to hold the result, either CStringArray or error message
    typedef struct
    {
        CStringArray strings;
        const char *error;
    } ResultCStringArray;

    void free_strings(CStringArray array);
    void free_error_string(const char *error);

    // SuiClient functions
    char *api_version();
    int check_api_version(void);
    ResultCStringArray available_rpc_methods();
    ResultCStringArray available_subscriptions();

    int buildDevnet(void);
    int buildTestnet(void);

#ifdef __cplusplus
}
#endif

#endif // SUI_CLIENT_H
