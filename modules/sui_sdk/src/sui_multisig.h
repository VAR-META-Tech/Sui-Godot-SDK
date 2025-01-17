#ifndef GODOT_SUI_MULTISIG_H
#define GODOT_SUI_MULTISIG_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

struct MultiSigStruct
{
	String address;
	TypedArray<uint8_t> bytes;
	String error;
};

class MulSigWrapper : public RefCounted
{
	GDCLASS(MulSigWrapper, RefCounted);

public:
	String address;
	TypedArray<uint8_t> bytes;
	String error;

	void set_address(String p_address) { address = p_address; }
	String get_address() const { return address; }
	void set_bytes(TypedArray<uint8_t> p_bytes) { bytes = p_bytes; }
	TypedArray<uint8_t> get_bytes() { return bytes; }
	void set_error(String p_error) { error = p_error; }
	String get_error() { return error; }

	static void _bind_methods()
	{
		ClassDB::bind_method(D_METHOD("get_address"), &MulSigWrapper::get_address);
		ClassDB::bind_method(D_METHOD("set_address", "address"), &MulSigWrapper::set_address);
		ClassDB::bind_method(D_METHOD("get_bytes"), &MulSigWrapper::get_bytes);
		ClassDB::bind_method(D_METHOD("set_bytes", "bytes"), &MulSigWrapper::set_bytes);
		ClassDB::bind_method(D_METHOD("get_error"), &MulSigWrapper::get_error);
		ClassDB::bind_method(D_METHOD("set_error", "error"), &MulSigWrapper::set_error);
	}
};

class SuiMultisig
{
protected:
	// static void _bind_methods();

public:
	Ref<MulSigWrapper> getOrCreateMultisig(TypedArray<String> addresses, TypedArray<uint8_t> weights, uint16_t threshold);
	TypedArray<uint8_t> createTransaction(String from_address, String to_address, uint64_t amount);
	String signAndExecuteTransaction(Ref<MulSigWrapper> multisig, TypedArray<uint8_t> tx, TypedArray<String> addresses);
	void freeMultisig(CMultiSig multisig);
};

#endif
