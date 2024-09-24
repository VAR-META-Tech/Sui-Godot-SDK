#ifndef GODOT_SUI_NFTS_H
#define GODOT_SUI_NFTS_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

struct WalletObjectStruct
{
	String object_id;
	int version;
	String digest;
	String type_;
	String owner;
	String previous_transaction;
	int storage_rebate;
	String display;
	String content;
	String bcs;
};

class WalletObjectWrapper : public RefCounted
{
	GDCLASS(WalletObjectWrapper, RefCounted);

public:
	String object_id;
	int version;
	String digest;
	String type_;
	String owner;
	String previous_transaction;
	int storage_rebate;
	String display;
	String content;
	String bcs;

	/** Getters and Setters Object ID */
	String get_object_id() const { return object_id; }
	void set_object_id(String p_object_id) { object_id = p_object_id; }
	/** Getters and Setters Version */
	int get_version() const { return version; }
	void set_version(int p_version) { version = p_version; }
	/** Getters and Setters Digest */
	String get_digest() const { return digest; }
	void set_digest(String p_digest) { digest = p_digest; }
	/** Getters and Setters Type */
	String get_type() const { return type_; }
	void set_type(String p_type) { type_ = p_type; }
	/** Getters and Setters Owner */
	String get_owner() const { return owner; }
	void set_owner(String p_owner) { owner = p_owner; }
	/** Getters and Setters Previous Transaction */
	String get_previous_transaction() const { return previous_transaction; }
	void set_previous_transaction(String p_previous_transaction) { previous_transaction = p_previous_transaction; }
	/** Getters and Setters Storage Rebate */
	int get_storage_rebate() const { return storage_rebate; }
	void set_storage_rebate(int p_storage_rebate) { storage_rebate = p_storage_rebate; }
	/** Getters and Setters Display */
	String get_display() const { return display; }
	void set_display(String p_display) { display = p_display; }
	/** Getters and Setters Content */
	String get_content() const { return content; }
	void set_content(String p_content) { content = p_content; }

	String get_bcs() const { return bcs; }
	void set_bcs(String p_bcs) { bcs = p_bcs; }

	static void _bind_methods()
	{
		/** Bind Methods Object ID */
		ClassDB::bind_method(D_METHOD("get_object_id"), &WalletObjectWrapper::get_object_id);
		ClassDB::bind_method(D_METHOD("set_object_id", "object_id"), &WalletObjectWrapper::set_object_id);
		/** Bind Methods Version */
		ClassDB::bind_method(D_METHOD("get_version"), &WalletObjectWrapper::get_version);
		ClassDB::bind_method(D_METHOD("set_version", "version"), &WalletObjectWrapper::set_version);
		/** Bind Methods Digest */
		ClassDB::bind_method(D_METHOD("get_digest"), &WalletObjectWrapper::get_digest);
		ClassDB::bind_method(D_METHOD("set_digest", "digest"), &WalletObjectWrapper::set_digest);
		/** Bind Methods Type */
		ClassDB::bind_method(D_METHOD("get_type"), &WalletObjectWrapper::get_type);
		ClassDB::bind_method(D_METHOD("set_type", "type"), &WalletObjectWrapper::set_type);
		/** Bind Methods Owner */
		ClassDB::bind_method(D_METHOD("get_owner"), &WalletObjectWrapper::get_owner);
		ClassDB::bind_method(D_METHOD("set_owner", "owner"), &WalletObjectWrapper::set_owner);
		/** Bind Methods Previous Transaction */
		ClassDB::bind_method(D_METHOD("get_previous_transaction"), &WalletObjectWrapper::get_previous_transaction);
		ClassDB::bind_method(D_METHOD("set_previous_transaction", "previous_transaction"), &WalletObjectWrapper::set_previous_transaction);
		/** Bind Methods Storage Rebate */
		ClassDB::bind_method(D_METHOD("get_storage_rebate"), &WalletObjectWrapper::get_storage_rebate);
		ClassDB::bind_method(D_METHOD("set_storage_rebate", "storage_rebate"), &WalletObjectWrapper::set_storage_rebate);
		/** Bind Methods Display */
		ClassDB::bind_method(D_METHOD("get_display"), &WalletObjectWrapper::get_display);
		ClassDB::bind_method(D_METHOD("set_display", "display"), &WalletObjectWrapper::set_display);
		/** Bind Methods Content */
		ClassDB::bind_method(D_METHOD("get_content"), &WalletObjectWrapper::get_content);
		ClassDB::bind_method(D_METHOD("set_content", "content"), &WalletObjectWrapper::set_content);
		/** Bind Methods BCS */
		ClassDB::bind_method(D_METHOD("get_bcs"), &WalletObjectWrapper::get_bcs);
		ClassDB::bind_method(D_METHOD("set_bcs", "bcs"), &WalletObjectWrapper::set_bcs);
	}
};

class SuiNfts
{
protected:
	// static void _bind_methods();

public:
	TypedArray<WalletObjectWrapper> getWalletObjects(String address, String object_type);
	void freeSuiObjectDataList(CSuiObjectDataArray array);
	String mintNft(
			String package_id,
			String sender_address,
			String name,
			String description,
			String uri);
	String transferNft(
			String package_id,
			String sender_address,
			String nft_id,
			String recipient_address);
};

#endif
