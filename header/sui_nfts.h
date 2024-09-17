// rust_functions.h
#ifndef SUI_NFTS_H
#define SUI_NFTS_H
#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct
{
	char *object_id;
	uint64_t version;
	char *digest;
	char *type_;
	char *owner;
	char *previous_transaction;
	uint64_t storage_rebate;
	char *display;
	char *content;
	char *bcs;
} CSuiObjectData;

typedef struct
{
	CSuiObjectData *data;
	size_t len;
} CSuiObjectDataArray;

CSuiObjectDataArray get_wallet_objects(const char *address, const char *object_type);
void free_sui_object_data_list(CSuiObjectDataArray array);

const char *mint_nft(
		const char *package_id,
		const char *sender_address,
		const char *name,
		const char *description,
		const char *uri);

const char *transfer_nft(
		const char *package_id,
		const char *sender_address,
		const char *nft_id,
		const char *recipient_address);
#ifdef __cplusplus
}
#endif

#endif // SUI_NFTS_H
