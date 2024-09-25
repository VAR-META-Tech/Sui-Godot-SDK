#include "sui_nfts.h"

Ref<WalletObjectWrapper> toWalletObjectWrapper(const WalletObjectStruct &wallet_struct)
{
	Ref<WalletObjectWrapper> wrapper = memnew(WalletObjectWrapper);
	wrapper->set_object_id(wallet_struct.object_id);
	wrapper->set_version(wallet_struct.version);
	wrapper->set_digest(wallet_struct.digest);
	wrapper->set_type(wallet_struct.type_);
	wrapper->set_owner(wallet_struct.owner);
	wrapper->set_previous_transaction(wallet_struct.previous_transaction);
	wrapper->set_storage_rebate(wallet_struct.storage_rebate);
	wrapper->set_display(wallet_struct.display);
	wrapper->set_content(wallet_struct.content);
	wrapper->set_bcs(wallet_struct.bcs);

	return wrapper;
}

Ref<WalletObjectWrapper> makeWalletObjectStruct(CSuiObjectData *walletObject)
{
	WalletObjectStruct walletStructItem;
	walletStructItem.object_id = walletObject->object_id;
	walletStructItem.version = walletObject->version;
	walletStructItem.digest = walletObject->digest;
	walletStructItem.type_ = walletObject->type_;
	walletStructItem.owner = walletObject->owner;
	walletStructItem.previous_transaction = walletObject->previous_transaction;
	walletStructItem.storage_rebate = walletObject->storage_rebate;
	walletStructItem.display = walletObject->display;
	walletStructItem.content = walletObject->content;
	walletStructItem.bcs = walletObject->bcs;

	return toWalletObjectWrapper(walletStructItem);
}

TypedArray<WalletObjectWrapper> SuiNfts::getWalletObjects(String address, String object_type)
{
	TypedArray<WalletObjectWrapper> walletObjects;
	CSuiObjectDataArray wallet_objects = get_wallet_objects(address.utf8().get_data(), object_type.utf8().get_data());
	if (wallet_objects.len == 0)
	{
		return walletObjects;
	}

	for (int i = 0; i < wallet_objects.len; i++)
	{
		CSuiObjectData *walletObject = &wallet_objects.data[i];
		walletObjects.append(makeWalletObjectStruct(walletObject));
	}

	freeSuiObjectDataList(wallet_objects);
	return walletObjects;
}

void SuiNfts::freeSuiObjectDataList(CSuiObjectDataArray array)
{
	free_sui_object_data_list(array);
}

String SuiNfts::mintNft(
		String package_id,
		String sender_address,
		String name,
		String description,
		String uri)
{
	char *message = mint_nft(
			package_id.utf8().get_data(),
			sender_address.utf8().get_data(),
			name.utf8().get_data(),
			description.utf8().get_data(),
			uri.utf8().get_data());
	return message;
}

String SuiNfts::transferNft(
		String package_id,
		String sender_address,
		String nft_id,
		String recipient_address)
{
	char *message = transfer_nft(
			package_id.utf8().get_data(),
			sender_address.utf8().get_data(),
			nft_id.utf8().get_data(),
			recipient_address.utf8().get_data());
	return message;
}