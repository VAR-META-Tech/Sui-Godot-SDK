extends Node2D

var suiSDK = SuiSDK.new()
var wallets = []

@onready var from:LineEdit = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer/HBoxContainer/from
@onready var fromError:Label = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer/fromError
@onready var receive:LineEdit = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer2/HBoxContainer/receive
@onready var receiveError:Label = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer2/receiveError
@onready var amount:LineEdit = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/amount
@onready var amountError:Label = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer2/VBoxContainer3/amountError
@onready var walletsOption: OptionButton = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer2/walletsOption
@onready var sponserError:Label = $Control/Panel/ScrollContainer/HBoxContainer/VBoxContainer/VBoxContainer/VBoxContainer2/sponserError

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		from.text = Global.currentWallet
	getWallets()
	addWalletsToPopup()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
	
func addWalletsToPopup():
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
	
	var gas = 0.005 * pow(10, 9);
	var builder = SuiProgrammableTransactionBuilder.new()
	var coin = SuiArguments.new()
	suiSDK.addArgumentGasCoin(coin)
	var amountArg = SuiArguments.new()
	var amountBscBasic = SuiBSCBasic.new()
	amountBscBasic.BSCBasic("u64", str(int(amount.text)*10**9))
	suiSDK.makePure(builder, amountArg, amountBscBasic)
	suiSDK.addSplitCoinsCommand(builder, coin , amountArg)
	
	var argument = SuiArguments.new()
	suiSDK.addArgumentResult(argument, 0)
	var recipient = SuiArguments.new()
	var recipientBscBasic = SuiBSCBasic.new()
	recipientBscBasic.BSCBasic("address", receive.text)
	suiSDK.makePure(builder, recipient, recipientBscBasic)
	suiSDK.addTransferObjectCommand(builder, argument, recipient)
	suiSDK.executeTransaction(builder, from.text, gas)
	
	#var message = suiSDK.programmableTransactionBuilder(from.text, receive.text, float(amount.text)*10**9)
	#print(message)
	Global.showToast("Executing the transaction successfully")
	returnRoot()


func _on_send_tx_builder_2_pressed() -> void:
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
	
	var gas = 0.005 * pow(10, 9);
	var builder = SuiProgrammableTransactionBuilder.new()
	var coin = SuiArguments.new()
	suiSDK.addArgumentGasCoin(coin)
	var amountArg = SuiArguments.new()
	var amountBscBasic = SuiBSCBasic.new()
	amountBscBasic.BSCBasic("u64", str(int(amount.text)*10**9))
	suiSDK.makePure(builder, amountArg, amountBscBasic)
	suiSDK.addSplitCoinsCommand(builder, coin , amountArg)
	
	var argument = SuiArguments.new()
	suiSDK.addArgumentResult(argument, 0)
	var recipient = SuiArguments.new()
	var recipientBscBasic = SuiBSCBasic.new()
	recipientBscBasic.BSCBasic("address", receive.text)
	suiSDK.makePure(builder, recipient, recipientBscBasic)
	suiSDK.addTransferObjectCommand(builder, argument, recipient)

	var message = suiSDK.executeTransactionAllowSponser(builder, from.text, gas, walletsOption.text)
	#var message = suiSDK.programmableTransactionBuilder(from.text, receive.text, float(amount.text)*10**9)
	print(message)
	Global.showToast("Executing the transaction successfully")
	returnRoot()
