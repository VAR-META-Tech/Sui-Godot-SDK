extends Node

func generate_uuid_v4() -> String:
	var uuid = PackedByteArray()
	for i in range(16):
		uuid.append(randi() % 256)
	# Set the version to 4 (randomly generated UUID)
	uuid[6] = (uuid[6] & 0x0F) | 0x40
	# Set the variant to DCE 1.1, ITU-T X.667
	uuid[8] = (uuid[8] & 0x3F) | 0x80
	# Convert to string format
	var str_uuid = ""
	for i in range(16):
		str_uuid += "%02x" % uuid[i]
		if i == 3 or i == 5 or i == 7 or i == 9:
			str_uuid += "-"
	return str_uuid
