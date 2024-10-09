extends Node2D

var suiSDK = SuiSDK.new()
var packageId = "0xe82276e2634220259709b827bf84828940cad87cdf061d396e6a569b9b4d9321"

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		var owner:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender")
		owner.text = Global.currentWallet


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func returnRoot():
	Global.changeScene(Global.SCREEN.ROOT)


func _on_cancel_pressed() -> void:
	returnRoot()


func _on_mint_pressed() -> void:
	var owner:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender")
	var ownerError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer/senderError")
	var name:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/name")
	var nameError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/nameError")
	var description:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/description")
	var descriptionError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/descriptionError")
	var uri:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer4/HBoxContainer/uri")
	var uriError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer4/uriError")
	
	if owner.text == "":
		ownerError.visible = true
		ownerError.text = "Owner wallet address is required"
	else:
		ownerError.visible = false
		ownerError.text = ""
		
	if name.text == "":
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
		
	if owner.text == "" || name.text == "" || description.text == "" || uri.text == "":
		return
	
	var balance = suiSDK.getBalanceSync(owner.text)
	var balanceNumber = float(balance.get_total_balance())
	if balanceNumber < 10**9:
		suiSDK.requestTokensFromFaucet(owner.text)
		OS.delay_msec(3)
		balance = suiSDK.getBalanceSync(owner.text)
		balanceNumber = float(balance.get_total_balance())
	while balanceNumber < 10**9:
		balance = suiSDK.getBalanceSync(owner.text)
		balanceNumber = float(balance.get_total_balance())
		OS.delay_msec(1)
	
	var message = suiSDK.mintNft(packageId, owner.text, name.text, description.text, uri.text)
	Global.showToast(message)
	returnRoot()	
