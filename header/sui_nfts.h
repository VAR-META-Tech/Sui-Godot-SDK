#ifndef SUI_NFTS_H
#define SUI_NFTS_H

#include <inttypes.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>

extern "C" {
struct CSuiObjectData {
	std::string object_id;
	uint64_t version;
	std::string digest;
	std::string type_;
	std::string owner;
	std::string previous_transaction;
	uint64_t storage_rebate;
	std::string display;
	std::string content;
	std::string bcs;
};

struct CSuiObjectDataArray {
	CSuiObjectData *data;
	size_t len;
};

class SuiNFTs {
public:
	static CSuiObjectDataArray get_wallet_objects(const char *address, const char *object_type);
	static void free_sui_object_data_list(CSuiObjectDataArray array);

	static const char *mint_nft(
			const char *package_id,
			const char *sender_address,
			const char *name,
			const char *description,
			const char *uri);

	static const char *transfer_nft(
			const char *package_id,
			const char *sender_address,
			const char *nft_id,
			const char *recipient_address);
};
}
#endif // SUI_NFTS_H
