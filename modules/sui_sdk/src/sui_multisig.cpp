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

CStringArray makeAddressArray(TypedArray<String> addresses)
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

	return addressesArray;
};

CU8Array makeWeightArray(TypedArray<uint8_t> weights)
{
	CU8Array weightsArray;
	weightsArray.len = weights.size();
	uint8_t *weightData = new uint8_t[weights.size()];
	for (size_t i = 0; i < weights.size(); i++)
	{
		weightData[i] = weights[i];
	}
	weightsArray.data = weightData;

	return weightsArray;
}

Ref<MulSigWrapper> SuiMultisig::getOrCreateMultisig(TypedArray<String> addresses, TypedArray<uint8_t> weights, uint16_t threshold)
{
	CStringArray addressesArray = makeAddressArray(addresses);
	CU8Array weightsArray = makeWeightArray(weights);

	MultiSig multiSig = get_or_create_multisig(addressesArray, weightsArray, threshold);
	return makeMultiSigStruct(multiSig);
}

TypedArray<uint8_t> SuiMultisig::createTransaction(String from_address, String to_address, uint64_t amount)
{
	CU8Array tx = create_transaction(from_address.utf8(), to_address.utf8(), amount);
	TypedArray<uint8_t> txArray;
	for (size_t i = 0; i < tx.len; i++)
	{
		txArray.append(tx.data[i]);
	}

	return txArray;
}

CU8Array parseMultiSig(Ref<MulSigWrapper> multisigRef)
{
	CU8Array multiSigBytes;
	multiSigBytes.len = multisigRef->get_bytes().size();
	uint8_t *multiSigBytesData = new uint8_t[multisigRef->get_bytes().size()];
	for (size_t i = 0; i < multisigRef->get_bytes().size(); i++)
	{
		multiSigBytesData[i] = multisigRef->get_bytes()[i];
	}
	multiSigBytes.data = multiSigBytesData;

	return multiSigBytes;
}

CU8Array parseTx(TypedArray<uint8_t> txRef)
{
	CU8Array tx;
	tx.len = txRef.size();
	uint8_t *txData = new uint8_t[txRef.size()];
	for (size_t i = 0; i < txRef.size(); i++)
	{
		txData[i] = txRef[i];
	}
	tx.data = txData;
	return tx;
};

CStringArray parseAddress(TypedArray<String> addresses)
{
	CStringArray addressesArray;
	addressesArray.data = (const char **)memalloc(sizeof(char *) * addresses.size());
	addressesArray.len = addresses.size();

	for (int i = 0; i < addresses.size(); ++i)
	{
		CharString char_string = String(addresses[i]).utf8();
		char *str_copy = (char *)memalloc(char_string.length() + 1);
		memcpy(str_copy, char_string.get_data(), char_string.length() + 1);
		addressesArray.data[i] = str_copy;
	}

	return addressesArray;
}

String SuiMultisig::signAndExecuteTransaction(Ref<MulSigWrapper> multisigRef, TypedArray<uint8_t> txRef, TypedArray<String> addresses)
{
	CU8Array multiSigBytes = parseMultiSig(multisigRef);
	CU8Array tx = parseTx(txRef);
	CStringArray addressesArray = parseAddress(addresses);

	return sign_and_execute_transaction(multiSigBytes, tx, addressesArray);
}

void SuiMultisig::freeMultisig(MultiSig multisig)
{
	free_multisig(multisig);
}
