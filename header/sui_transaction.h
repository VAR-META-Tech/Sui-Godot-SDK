// rust_functions.h
#ifndef SUI_TRANSACTION_H
#define SUI_TRANSACTION_H
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif
class SuiTransaction {
public:
	static char *programmable_transaction(const char *sender_address, const char *recipient_address, uint64_t amount);
	static char *programmable_transaction_allow_sponser(const char *sender_address, const char *recipient_address, uint64_t amount, const char *sponser_address);
	static const char *request_tokens_from_faucet_(const char *address_str);
};
#ifdef __cplusplus
}
#endif

#endif // SUI_TRANSACTION_H
