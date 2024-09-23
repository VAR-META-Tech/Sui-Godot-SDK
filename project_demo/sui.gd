extends Node

class QWallet:
	var a : String
	var b : int
	
var sdk = SuiSDK.new()

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass
	#var buttonGetWallets = Button.new()
	#buttonGetWallets.text = "Get Wallets"
	#buttonGetWallets.pressed.connect(self.onGetWallets)
	#add_child(buttonGetWallets)
	#
	#var buttonGenWallet = Button.new()
	#buttonGenWallet.text = "Generate Wallet"
	#buttonGenWallet.pressed.connect(self.onGenerateWallet)
	#add_child(buttonGenWallet)
	#pass # Replace with function body.

func printAddress(wallet):
	print(wallet.get_address())
	print(wallet.get_mnemonic())
	print(wallet.get_public_base64_key())
	print(wallet.get_private_key())
	print(wallet.get_key_scheme())

func onGetWallets():
	#var sdk = SuiSDK.new()
	var wallets = sdk.getWallets()
	
	for wallet in wallets:
		printAddress(wallet)

func onGenerateWallet():
	#var sdk = SuiSDK.new()
	var wallet = sdk.generateWallet("ed25519", "word12")
	printAddress(wallet)

func onGenAndAddKey():
	var wallet = sdk.generateAndAddKey()
	printAddress(wallet)

func onGetWalletFromAddress():
	var address = '0xfee0108a2467a551f50f3f7c2dc77128406ae314ef4515030dc62accb0c15bcc'
	var wallet =  sdk.getWalletFromAddress(address)
	if wallet == null: print('Wallet not found')
	else: printAddress(wallet)

func onImportFromPrivateKey():
	var privateKey = 'ALxpSoPbaEhbXXwsUrpC+icfmeArLR+fm65u8j1O9i2q'
	sdk.importFromPrivateKey(privateKey)
	print('ImportFromPrivateKey OK')

func onImportFromMnemonic():
	var mnemonic = 'finish appear ghost horn text train network flag evoke symbol lesson cycle'
	var address = sdk.importFromMnemonic(mnemonic)
	print(address)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _on_button_get_wallets_pressed() -> void:
	onGetWallets()
	pass # Replace with function body.

func _on_button_gen_wallet_pressed() -> void:
	onGenerateWallet()
	pass # Replace with function body.

func _on_button_generate_and_add_key_pressed() -> void:
	onGenAndAddKey()
	pass # Replace with function body.

func _on_button_get_wallet_from_address_pressed() -> void:
	onGetWalletFromAddress()
	pass # Replace with function body.


func _on_button_import_from_private_key_pressed() -> void:
	onImportFromPrivateKey()
	pass # Replace with function body.


func _on_button_import_from_mnemonic_pressed() -> void:
	onImportFromMnemonic()
	pass # Replace with function body.
