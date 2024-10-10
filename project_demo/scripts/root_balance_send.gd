extends Node2D

var suiSDK = SuiSDK.new()
var wallets = []

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		var from: LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/from")
		from.text = Global.currentWallet
	getWallets()
	addWalletsToPopup()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
	
func addWalletsToPopup():
	var walletsOption: OptionButton = get_node("Control/Panel/VBoxContainer/VBoxContainer2/walletsOption")
	walletsOption.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		walletsOption.add_item(wallet.get_address(), i)
	walletsOption.select(-1)
	
func getWallets():
	wallets = suiSDK.getWallets()

func returnRoot():
	Global.changeScene(Global.SCREEN.ROOT)

func _on_cancel_pressed() -> void:
	returnRoot()


func _on_send_pressed() -> void:
	var from:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/from")
	var fromError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer/fromError")
	var receive:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/receive")
	var receiveError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/receiveError")
	var amount:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/amount")
	var amountError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/amountError")
	
	if from.text == "":
		fromError.visible = true
		fromError.text = "From address is required"
	else:
		fromError.visible = false
		fromError.text = ""
		
	if receive.text == "":
		receiveError.visible = true
		receiveError.text = "Receive address is required"
	else:
		receiveError.visible = false
		receiveError.text = ""

	if amount.text == "":
		amountError.visible = true
		amountError.text = "Amount address is required"
	else:
		amountError.visible = false
		amountError.text = ""
		
	if from.text == "" || receive.text == "" || amount.text == "":
		return
		
	var message = suiSDK.signTransaction(from.text, receive.text, float(amount.text)*10**9)
	print(message)
	Global.showToast(message)
	if message == "Transaction completed successfully":
		returnRoot()


func _on_send_with_sponsor_pressed() -> void:
	var from:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/from")
	var fromError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer/fromError")
	var receive:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/receive")
	var receiveError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/receiveError")
	var amount:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/amount")
	var amountError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/amountError")
	var walletsOption: OptionButton = get_node("Control/Panel/VBoxContainer/VBoxContainer2/walletsOption")
	var sponserError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/sponserError")
	
	if from.text == "":
		fromError.visible = true
		fromError.text = "From address is required"
	else:
		fromError.visible = false
		fromError.text = ""
		
	if receive.text == "":
		receiveError.visible = true
		receiveError.text = "Receive address is required"
	else:
		receiveError.visible = false
		receiveError.text = ""

	if amount.text == "":
		amountError.visible = true
		amountError.text = "Amount address is required"
	else:
		amountError.visible = false
		amountError.text = ""
		
	if walletsOption.text == "":
		sponserError.visible = true
		sponserError.text = "Sponsor address is required"
	else:
		sponserError.visible = false
		sponserError.text = ""
	
		
	if from.text == "" || receive.text == "" || amount.text == "" || walletsOption.text == "":
		return
		
	var message = suiSDK.programmableTransactionAllowSponser(from.text, receive.text, float(amount.text)*10**9, walletsOption.text)
	print(message)
	Global.showToast(message)
	if message == "Transaction completed successfully":
		returnRoot()


func _on_send_tx_builder_pressed() -> void:
	var from:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/from")
	var fromError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer/fromError")
	var receive:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/receive")
	var receiveError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/receiveError")
	var amount:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/amount")
	var amountError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/amountError")
	
	if from.text == "":
		fromError.visible = true
		fromError.text = "From address is required"
	else:
		fromError.visible = false
		fromError.text = ""
		
	if receive.text == "":
		receiveError.visible = true
		receiveError.text = "Receive address is required"
	else:
		receiveError.visible = false
		receiveError.text = ""

	if amount.text == "":
		amountError.visible = true
		amountError.text = "Amount address is required"
	else:
		amountError.visible = false
		amountError.text = ""
		
	if from.text == "" || receive.text == "" || amount.text == "":
		return
		
	var message = suiSDK.programmableTransactionBuilder(from.text, receive.text, float(amount.text)*10**9)
	print(message)
	Global.showToast("Executing the transaction successfully")
	returnRoot()
