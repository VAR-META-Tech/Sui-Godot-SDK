#ifndef GODOT_SUI_NFTS_H
#define GODOT_SUI_NFTS_H

#include "../header/sui_lib.h"

class SuiNfts {
protected:
	// static void _bind_methods();

public:
	CSuiObjectDataArray getWalletObjects(const char *address, const char *object_type);
	void freeSuiObjectDataList(CSuiObjectDataArray array);
	char *mintNft(
			const char *package_id,
			const char *sender_address,
			const char *name,
			const char *description,
			const char *uri);
	char *transferNft(
			const char *package_id,
			const char *sender_address,
			const char *nft_id,
			const char *recipient_address);
};

#endif
