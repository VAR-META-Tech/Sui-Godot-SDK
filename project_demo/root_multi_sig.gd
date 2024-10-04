extends TabBar

var uuid_generator = preload("res://utils/uuid_generator.gd").new()

class WalletSig:
	var id: int
	var address: String
	

var suiSDK = SuiSDK.new()
var wallets: Array[WalletWrapper] = []
var walletsSelected: Dictionary = {}
var weightSelected: Dictionary = {}
var multiSig
var multiSigAddress = ""
var multiSigBytes = []
var txBytes = []
var addressConfirm = []

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	setWalletAddress()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func getWallets():
	wallets = suiSDK.getWallets()
	
	return wallets
	
func addWalletsToOptionButton(walletsOption: OptionButton):
	for i in wallets.size():
		var wallet = wallets[i]
		var walletAddress: String = wallet.get_address()
		var trimWallet = walletAddress.substr(0, 8) + "..." + walletAddress.substr(walletAddress.length() - 8, walletAddress.length())
		walletsOption.add_item(trimWallet, i)
	walletsOption.select(-1)

func newOptionWallet(id: String):
	var stylesAddressOption = StyleBoxFlat.new()
	var walletsOption = OptionButton.new()
	walletsOption.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	addWalletsToOptionButton(walletsOption)
	walletsOption.connect("item_selected", func(index):
		var getWallet = wallets[index]
		var getAddress = getWallet.get_address()
		handleAddressChange(id, getAddress)
	)
	stylesAddressOption.bg_color.r8 = 43
	stylesAddressOption.bg_color.g8 = 59
	stylesAddressOption.bg_color.b8 = 90
	stylesAddressOption.content_margin_left = 8

	walletsOption.custom_minimum_size = Vector2(0, 40)
	walletsOption.add_theme_stylebox_override("normal", stylesAddressOption)
	
	return walletsOption
	
func newWeight(id: String):
	var stylesWeight = StyleBoxFlat.new()
	var weightLineEdit = LineEdit.new()
	weightLineEdit.placeholder_text = "Enter the weight of wallet"
	weightLineEdit.custom_minimum_size = Vector2(0, 40)
	stylesWeight.bg_color.r8 = 43
	stylesWeight.bg_color.g8 = 59
	stylesWeight.bg_color.b8 = 90
	stylesWeight.content_margin_left = 8
	weightLineEdit.add_theme_stylebox_override("normal", stylesWeight)
	weightLineEdit.connect("text_changed", func(textValue): handleWeightChange(id, textValue))
	
	return weightLineEdit

func deleteWallet(uuid:String,addressBoxContainer):
	var addresssesVBoxContainer = get_node("HBoxContainer/VBoxContainer/ScrollContainer/AddresssesVBoxContainer")
	walletsSelected.erase(uuid)
	weightSelected.erase(uuid)
	addresssesVBoxContainer.remove_child(addressBoxContainer)
	renderListAddress()

func newDeleteBtn(id: String,addressBoxContainer):
	var hbox= HBoxContainer.new()
	hbox.alignment = BoxContainer.ALIGNMENT_END
	hbox.size_flags_vertical = Control.SIZE_SHRINK_CENTER
	
	var delTextureButton = TextureButton.new()
	var buttonCopy: Texture2D = load("res://icons/trash.svg")
	delTextureButton.texture_normal = buttonCopy
	delTextureButton.connect("pressed", func(): deleteWallet(id,addressBoxContainer))

	hbox.add_child(delTextureButton)
	
	return hbox

func addMoreWallet():
	var uuid = uuid_generator.generate_uuid_v4()
	var addresssesVBoxContainer = get_node("HBoxContainer/VBoxContainer/ScrollContainer/AddresssesVBoxContainer")
	var addressBoxContainer = VBoxContainer.new()

	var walletLabel = Label.new()
	walletLabel.text = "Address"
	walletLabel.add_theme_font_size_override("font_size", 12)
	
	var walletsOption = newOptionWallet(uuid)

	var weightLabel = Label.new()
	weightLabel.text = "Weight"
	weightLabel.add_theme_font_size_override("font_size", 12)

	var weightLineEdit = newWeight(uuid)
	var deleteBtn = newDeleteBtn(uuid,addressBoxContainer)

	addressBoxContainer.add_child(walletLabel)
	addressBoxContainer.add_child(walletsOption)
	addressBoxContainer.add_child(weightLabel)
	addressBoxContainer.add_child(weightLineEdit)
	addressBoxContainer.add_child(deleteBtn)
	
	addresssesVBoxContainer.add_child(addressBoxContainer)
	walletsSelected[uuid] = ""
	weightSelected[uuid] = ""

func setWalletAddress():
	getWallets()
	addMoreWallet()

func checkRequireWallet():
	var addressesError: Label = get_node("HBoxContainer/VBoxContainer/addressesError")
	for wallet in walletsSelected:
		if walletsSelected[wallet] == "":
			addressesError.text = "Wallet address is required"
			addressesError.visible = true
			return false
	
	addressesError.visible = false
	addressesError.text = ""
	return true

func checkRequireWeight():
	var addressesError: Label = get_node("HBoxContainer/VBoxContainer/addressesError")
	for weight in weightSelected:
		if weightSelected[weight] == "":
			addressesError.text = "Weight is required"
			addressesError.visible = true
			return false
	
	addressesError.visible = false
	addressesError.text = ""
	return true

func checkRequireThreshold():
	var thresholdError: Label = get_node("HBoxContainer/VBoxContainer/HBoxContainer2/VBoxContainer/thresholdError")
	var thresholdLineEdit: LineEdit = get_node("HBoxContainer/VBoxContainer/HBoxContainer2/VBoxContainer/thresholdLineEdit")
	if thresholdLineEdit.text == "":
		thresholdError.text = "Threshold is required"
		thresholdError.visible = true
		return false
	else:
		thresholdError.visible = false
		thresholdError.text = ""
		return true
		
func parseAddresses():
	var addresses = []
	for id in walletsSelected:
		addresses.append(walletsSelected[id])
	return addresses

func parseWeight():
	var weights = []
	for id in weightSelected:
		weights.append(int(weightSelected[id]))
	return weights

func _on_get_sig_pressed() -> void:
	var passCheckWallet = checkRequireWallet()
	if passCheckWallet == false: return
	var passCheckWeight = checkRequireWeight()
	if passCheckWeight == false: return
	var passThreshold = checkRequireThreshold()
	if passThreshold == false: return
	
	var thresholdLineEdit: LineEdit = get_node("HBoxContainer/VBoxContainer/HBoxContainer2/VBoxContainer/thresholdLineEdit")

	var addresses = parseAddresses()
	var weights = parseWeight()
	var threshold = int(thresholdLineEdit.text)

	multiSig = suiSDK.getOrCreateMultisig(addresses, weights, threshold)
	multiSigAddress = multiSig.get_address()
	multiSigBytes = multiSig.get_bytes()
	
	var multiSigAddressText: Label = get_node("HBoxContainer/VBoxContainer2/VBoxContainer/HBoxContainer/multiSigAddress")
	var multiSigBytesText: Label = get_node("HBoxContainer/VBoxContainer2/VBoxContainer/HBoxContainer2/multiSigBytes")
	multiSigAddressText.text = multiSigAddress
	multiSigBytesText.text = "".join(multiSigBytes)
	
	Global.showToast("Get multi-sig successfully")

func _on_add_wallet_pressed() -> void:
	addMoreWallet()
	
func handleSelectAddressConfirm(isChecked: bool, address: String):
	if isChecked == true:
		addressConfirm.append(address)
	else:
		var index = addressConfirm.find(address, 0)
		if index > -1: addressConfirm.remove_at(index)

func clearListAddress():
	var listAddress: VBoxContainer = get_node("HBoxContainer/VBoxContainer2/ScrollContainerListAddress/VBoxContainerListAddress")
	for child in listAddress.get_children():
		listAddress.remove_child(child)

func renderListAddress():
	var listAddress = get_node("HBoxContainer/VBoxContainer2/ScrollContainerListAddress/VBoxContainerListAddress")
	clearListAddress()
	for address in walletsSelected:
		if walletsSelected[address] != "":
			var checkbox = CheckBox.new()
			checkbox.text = walletsSelected[address]
			checkbox.connect("toggled", func(checked): handleSelectAddressConfirm(checked, walletsSelected[address]))
			listAddress.add_child(checkbox)

func handleAddressChange(id: String, value: String):
	walletsSelected[id] = value
	renderListAddress()

func handleWeightChange(id: String, value: String):
	weightSelected[id] = value
	renderListAddress()

func _on_copy_sig_address_pressed() -> void:
	var multiSigAddressText: Label = get_node("HBoxContainer/VBoxContainer2/VBoxContainer/HBoxContainer/multiSigAddress")
	DisplayServer.clipboard_set(multiSigAddressText.text)
	Global.showToast("Copied")


func _on_copy_sig_bytes_pressed() -> void:
	var multiSigBytesText: Label = get_node("HBoxContainer/VBoxContainer2/VBoxContainer/HBoxContainer2/multiSigBytes")
	DisplayServer.clipboard_set(multiSigBytesText.text)
	Global.showToast("Copied")

func _on_button_pressed() -> void:
	var fromWallet: LineEdit = get_node("HBoxContainer/VBoxContainer2/HBoxContainer3/HBoxContainer/VBoxContainer/fromWallet")
	var fromWalletError: Label = get_node("HBoxContainer/VBoxContainer2/HBoxContainer3/HBoxContainer/VBoxContainer/fromWalletError")
	var toWallet: LineEdit = get_node("HBoxContainer/VBoxContainer2/HBoxContainer3/HBoxContainer/VBoxContainer2/toWallet")
	var toWalletError: Label = get_node("HBoxContainer/VBoxContainer2/HBoxContainer3/HBoxContainer/VBoxContainer2/toWalletError")
	var amount: LineEdit = get_node("HBoxContainer/VBoxContainer2/HBoxContainer3/HBoxContainer2/VBoxContainer/amount")
	var amountError: Label = get_node("HBoxContainer/VBoxContainer2/HBoxContainer3/HBoxContainer2/VBoxContainer/amountError")
	var txBytesText: Label = get_node("HBoxContainer/VBoxContainer2/HBoxContainer4/txBytes")
	
	if fromWallet.text == "":
		fromWalletError.text = "From wallet is required"
		fromWalletError.visible = true
	else:
		fromWalletError.visible = false
		fromWalletError.text = ""
	if toWallet.text == "":
		toWalletError.text = "From wallet is required"
		toWalletError.visible = true
	else:
		toWalletError.visible = false
		toWalletError.text = ""
	if amount.text == "":
		amountError.text = "From wallet is required"
		amountError.visible = true
	else:
		amountError.visible = false
		amountError.text = ""
	
	if fromWallet.text == "" || toWallet.text == "" || amount.text == "":
		return
		
	txBytes = suiSDK.createTransaction(fromWallet.text, toWallet.text, int(amount.text)*10**9)
	txBytesText.text = "".join(txBytes)
	Global.showToast("Create transaction successfully")


func _on_copy_tx_bytes_pressed() -> void:
	var txBytesText: Label = get_node("HBoxContainer/VBoxContainer2/HBoxContainer4/txBytes")
	DisplayServer.clipboard_set(txBytesText.text)
	Global.showToast("Copied")

func _on_sign_and_execute_tx_pressed() -> void:
	var multiSigError = get_node("HBoxContainer/VBoxContainer2/VBoxContainer/multiSigError")
	var txError = get_node("HBoxContainer/VBoxContainer2/txError")
	var confirmAddressError = get_node("HBoxContainer/VBoxContainer2/confirmAddressError")
	var notHaveMultiSig = multiSigBytes.size() == 0
	var notHaveTx = txBytes.size() == 0
	var notHaveAddressConfirm = addressConfirm.size() == 0

	if notHaveMultiSig:
		multiSigError.text = "Multi signature is required"
		multiSigError.visible = true
	else:
		multiSigError.visible = false
		multiSigError.text = ""

	if notHaveTx:
		txError.text = "Transaction is required"
		txError.visible = true
	else:
		txError.visible = false
		txError.text = ""

	if notHaveAddressConfirm:
		confirmAddressError.text = "Address confirm is required"
		confirmAddressError.visible = true
	else:
		confirmAddressError.visible = false
		confirmAddressError.text = ""

	if notHaveMultiSig == true || notHaveTx == true || notHaveAddressConfirm == true:
		return

	#var multiSig = MulSigWrapper.new()
	#multiSig.set_address(multiSigAddress)
	#multiSig.set_bytes(multiSigBytes)
	
	var message = suiSDK.signAndExecuteTransaction(multiSig, txBytes, addressConfirm)
	Global.showToast(message)


func _on_faucet_pressed() -> void:
	var multiSigError = get_node("HBoxContainer/VBoxContainer2/VBoxContainer/multiSigError")
	if multiSigAddress == "":
		multiSigError.text = "Multi signature is required"
		multiSigError.visible = true
		return
	else:
		multiSigError.visible = false
		multiSigError.text = ""
	var message = suiSDK.requestTokensFromFaucet(multiSigAddress)
	Global.showToast(message)
