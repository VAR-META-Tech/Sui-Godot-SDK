extends Node2D

var suiSDK = SuiSDK.new()
var packageId = "0x99ebcdef6e51e1021eeaded8d3c7c7eb672c1b000d5ef3408d103b805b93a0a0"

@onready var ownerNftMint: LineEdit = $Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender
@onready var ownerError: Label = $Control/Panel/VBoxContainer/VBoxContainer/senderError
@onready var nftName: LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/name
@onready var nameError: Label = $Control/Panel/VBoxContainer/VBoxContainer2/nameError
@onready var description: LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/description
@onready var descriptionError: Label = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/descriptionError
@onready var uri: LineEdit = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer4/HBoxContainer/uri
@onready var uriError: Label = $Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer4/uriError

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		ownerNftMint.text = Global.currentWallet


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func returnRoot():
	Global.changeScene(Global.SCREEN.ROOT)


func _on_cancel_pressed() -> void:
	returnRoot()

func validateForm() -> bool:
	if ownerNftMint.text == "":
		ownerError.visible = true
		ownerError.text = "Owner wallet address is required"
	else:
		ownerError.visible = false
		ownerError.text = ""
		
	if nftName.text == "":
		nameError.visible = true
		nameError.text = "Name NFT is required"
	else:
		nameError.visible = false
		nameError.text = ""

	if description.text == "":
		descriptionError.visible = true
		descriptionError.text = "Description NFT is required"
	else:
		descriptionError.visible = false
		descriptionError.text = ""

	if uri.text == "":
		uriError.visible = true
		uriError.text = "URI NFT is required"
	else:
		uriError.visible = false
		uriError.text = ""
		
	if ownerNftMint.text == "" || nftName.text == "" || description.text == "" || uri.text == "":
		return false
	return true
	
func checkBalance():
	var balance = suiSDK.getBalanceSync(ownerNftMint.text)
	var balanceNumber = float(balance.get_total_balance())
	if balanceNumber < 10**9:
		suiSDK.requestTokensFromFaucet(ownerNftMint.text)
		OS.delay_msec(3)
		balance = suiSDK.getBalanceSync(ownerNftMint.text)
		balanceNumber = float(balance.get_total_balance())
	while balanceNumber < 10**9:
		balance = suiSDK.getBalanceSync(ownerNftMint.text)
		balanceNumber = float(balance.get_total_balance())
		OS.delay_msec(1)
	

func _on_mint_pressed() -> void:
	var validateResult = validateForm()
	if validateResult == false:
		return
	checkBalance()
	
	var message = suiSDK.mintNft(packageId, ownerNftMint.text, nftName.text, description.text, uri.text)
	print(message)
	Global.showToast("Mint NFT successfully")
	returnRoot()


func _on_mint_2_pressed() -> void:
	var validateResult = validateForm()
	if validateResult == false:
		return

	checkBalance()

	var builder = SuiProgrammableTransactionBuilder.new()
	var argument = SuiArguments.new()
	var nameBscBasic = SuiBSCBasic.new()
	var descriptionBscBasic = SuiBSCBasic.new()
	var uriBscBasic = SuiBSCBasic.new()
	var gas = 0.005 * 10**9

	nameBscBasic.BSCBasic("string", nftName.text)
	descriptionBscBasic.BSCBasic("string", description.text)
	uriBscBasic.BSCBasic("string", uri.text)

	suiSDK.makePure(builder, argument, nameBscBasic)
	suiSDK.makePure(builder, argument, descriptionBscBasic)
	suiSDK.makePure(builder, argument, uriBscBasic)
	#suiSDK.addArgumentInput(argument, 0)
	#suiSDK.addArgumentInput(argument, 1)
	#suiSDK.addArgumentInput(argument, 2)

	var typeTag = SuiTypeTags.new()
	suiSDK.addMoveCallCommand(builder, packageId, "nft", "mint_to_sender", typeTag, argument)
	var result = suiSDK.executeTransaction(builder, ownerNftMint.text, gas)
	print(result)
	Global.showToast("Mint NFT successfully")
	returnRoot()
