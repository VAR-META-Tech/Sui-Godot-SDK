extends TabBar

var sdk = SuiSDK.new()
var wallets = []
func _ready():
	self.load_wallets()

func  load_wallets():
	wallets = sdk.getWallets()
	var box= get_node("address_box")
	box.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		box.add_item(wallet.get_address(),i)

func _on_import_private_key_pressed() -> void:
	var privateKey = get_node("box_key").text
	if privateKey != "":
		sdk.importFromPrivateKey(privateKey)
		print('ImportFromPrivateKey OK')
		self.load_wallets()


func _on_import_mnemonic_pressed() -> void:
	var privateKey = get_node("box_key").text
	if privateKey != "":
		sdk.importFromMnemonic(privateKey)
		print('import mnemonic OK')
		self.load_wallets()


func _on_create_custom_pressed() -> void:
	var scheme = get_node("scheme").get_selected_id()
	var word = get_node("word").get_selected_id()
	if scheme == -1 or word == -1:
		return
	else:
		print(get_node("scheme").get_item_text(scheme),get_node("word").get_item_text(word))
		sdk.generateWallet(get_node("scheme").get_item_text(scheme),get_node("word").get_item_text(word))
		self.load_wallets()
		get_node("result").text = "generate success"


func _on_generate_pressed() -> void:
	var wallet = sdk.generateAndAddKey()
	var res = ""
	res = res +  "Address: " + wallet.get_address() + "\n"
	res = res +  "Mnemonic: " + wallet.get_mnemonic() + "\n"
	res = res +  "public key: " + wallet.get_public_base64_key() + "\n"
	res = res +  "private key: " + wallet.get_private_key() + "\n"
	res = res +  "scheme key: " + wallet.get_key_scheme() + "\n\n"
	get_node("result").text = res
	self.load_wallets()


func _on_load_pressed() -> void:
	wallets = sdk.getWallets()
	var res = ""
	for wallet in wallets:
		res = res +  "Address: " + wallet.get_address() + "\n"
		res = res +  "Mnemonic: " + wallet.get_mnemonic() + "\n"
		res = res +  "public key: " + wallet.get_public_base64_key() + "\n"
		res = res +  "private key: " + wallet.get_private_key() + "\n"
		res = res +  "scheme key: " + wallet.get_key_scheme() + "\n\n"
	get_node("result").text = res
