#include "sui_multisig.h"

Ref<MulSigWrapper> toMultiSigWrapper(const MultiSigStruct &multi_sig_struct)
{
	Ref<MulSigWrapper> wrapper = memnew(MulSigWrapper);
	wrapper->set_address(multi_sig_struct.address);
	wrapper->set_bytes(multi_sig_struct.bytes);

	return wrapper;
}

Ref<MulSigWrapper> makeMultiSigStruct(MultiSig multisig)
{
	MultiSigStruct multiSigStructItem;
	multiSigStructItem.address = multisig.address;

	TypedArray<uint8_t> bytes;
	for (size_t i = 0; i < multisig.bytes.len; i++)
	{
		bytes.append(multisig.bytes.data[i]);
	}

	multiSigStructItem.bytes = bytes;

	return toMultiSigWrapper(multiSigStructItem);
}

Ref<MulSigWrapper> SuiMultisig::getOrCreateMultisig(TypedArray<String> addresses, TypedArray<uint8_t> weights, uint16_t threshold)
{
	CStringArray addressesArray;
	int size = addresses.size();

	addressesArray.data = (const char **)memalloc(sizeof(char *) * size);
	addressesArray.len = size;

	for (int i = 0; i < size; ++i)
	{
		CharString char_string = String(addresses[i]).utf8();
		char *str_copy = (char *)memalloc(char_string.length() + 1);
		memcpy(str_copy, char_string.get_data(), char_string.length() + 1);
		addressesArray.data[i] = str_copy;
	}

	CU8Array weightsArray;
	weightsArray.len = weights.size();
	uint8_t *weightData = new uint8_t[weights.size()];
	for (size_t i = 0; i < weights.size(); i++)
	{
		weightData[i] = weights[i];
	}
	weightsArray.data = weightData;

	MultiSig multiSig = get_or_create_multisig(addressesArray, weightsArray, threshold);
	return makeMultiSigStruct(multiSig);
}

CU8Array SuiMultisig::createTransaction(const char *from_address,
																				const char *to_address, uint64_t amount)
{
	return create_transaction(from_address, to_address, amount);
}

const char *SuiMultisig::signAndExecuteTransaction(CU8Array multisig,
																									 CU8Array tx,
																									 CStringArray addresses)
{
	return sign_and_execute_transaction(multisig, tx, addresses);
}

void SuiMultisig::freeMultisig(MultiSig multisig)
{
	free_multisig(multisig);
}
