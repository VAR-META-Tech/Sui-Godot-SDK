#include "sui_nfts.h"

CSuiObjectDataArray SuiNfts::getWalletObjects(const char *address, const char *object_type) {
	return get_wallet_objects(address, object_type);
}

void SuiNfts::freeSuiObjectDataList(CSuiObjectDataArray array) {
	free_sui_object_data_list(array);
}

char *SuiNfts::mintNft(
		const char *package_id,
		const char *sender_address,
		const char *name,
		const char *description,
		const char *uri) {
	return mint_nft(package_id, sender_address, name, description, uri);
}

char *SuiNfts::transferNft(
		const char *package_id,
		const char *sender_address,
		const char *nft_id,
		const char *recipient_address) {
	return transfer_nft(package_id, sender_address, nft_id, recipient_address);
}