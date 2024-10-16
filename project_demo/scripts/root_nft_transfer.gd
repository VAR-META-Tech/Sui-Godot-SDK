extends Node2D

var suiSDK = SuiSDK.new()
var packageId = "0x99ebcdef6e51e1021eeaded8d3c7c7eb672c1b000d5ef3408d103b805b93a0a0"

@onready var from:LineEdit = $Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender
@onready var fromError:Label = $Control/Panel/VBoxContainer/VBoxContainer/senderError
@onready var to:LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/to
@onready var toError:Label = $Control/Panel/VBoxContainer/VBoxContainer2/toError
@onready var nftId:LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/nftId
@onready var nftIdError:Label = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/nftIdError

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		from.text = Global.currentWallet


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
	
func returnRoot():
	Global.changeScene(Global.SCREEN.ROOT)
	
func validateForm():
	if from.text == "":
		fromError.visible = true
		fromError.text = "From wallet address is required"
	else:
		fromError.visible = false
		fromError.text = ""
		
	if to.text == "":
		toError.visible = true
		toError.text = "To wallet address is required"
	else:
		toError.visible = false
		toError.text = ""

	if nftId.text == "":
		nftIdError.visible = true
		nftIdError.text = "Description NFT is required"
	else:
		nftIdError.visible = false
		nftIdError.text = ""

	if from.text == "" || to.text == "" || nftId.text == "":
		return false
	return true

func checkBalance():
	var balance = suiSDK.getBalanceSync(from.text)
	var balanceNumber = float(balance.get_total_balance())
	if balanceNumber < 10**9:
		suiSDK.requestTokensFromFaucet(from.text)
		OS.delay_msec(3)
		balance = suiSDK.getBalanceSync(from.text)
		balanceNumber = float(balance.get_total_balance())
	while balanceNumber < 10**9:
		balance = suiSDK.getBalanceSync(from.text)
		balanceNumber = float(balance.get_total_balance())
		OS.delay_msec(1)

func _on_transfer_pressed() -> void:
	var validateResult = validateForm()
	if validateResult == false:
		return
		
	checkBalance()

	var message = suiSDK.transferNft(packageId, from.text, nftId.text, to.text)
	Global.showToast(message)
	returnRoot()


func _on_cancel_pressed() -> void:
	returnRoot()


func _on_transfer_2_pressed() -> void:
	var validateResult = validateForm()
	if validateResult == false:
		return

	checkBalance()

	var builder = SuiProgrammableTransactionBuilder.new()
	var argument = SuiArguments.new()
	var nftIdBscBasic = SuiBSCBasic.new()
	var recipientBscBasic = SuiBSCBasic.new()
	var gas = 0.005 * 10**9

	nftIdBscBasic.BSCBasic("address", nftId.text)
	recipientBscBasic.BSCBasic("address", to.text)

	suiSDK.makeObjectImmOrOwned(builder, argument, nftId.text, from.text)
	suiSDK.makePure(builder, argument, recipientBscBasic)

	var typeTag = SuiTypeTags.new()
	suiSDK.addMoveCallCommand(builder, packageId, "nft", "transfer", typeTag, argument)
	var result = suiSDK.executeTransaction(builder, from.text, gas)
	print(result)
	Global.showToast("Transfer NFT successfully")
	returnRoot()
	pass
