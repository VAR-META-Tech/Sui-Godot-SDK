extends Node2D

var suiSDK = SuiSDK.new()
var packageId = "0x48a557eb090729457000b7303796c4447abea2362b009988b3ab7445b60ed6a3"

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		var from:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender")
		from.text = Global.currentWallet


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
	
func returnRoot():
	Global.changeScene(Global.SCREEN.ROOT)

func _on_mint_pressed() -> void:
	var from:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender")
	var fromError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer/senderError")
	var to:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/HBoxContainer/to")
	var toError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/toError")
	var nftId:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/HBoxContainer/nftId")
	var nftIdError:Label = get_node("Control/Panel/VBoxContainer/VBoxContainer2/VBoxContainer3/nftIdError")
	
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
		return
		
	var message = suiSDK.transferNft(packageId, from.text, nftId.text, to.text)
	Global.showToast(message)
	returnRoot()	


func _on_cancel_pressed() -> void:
	returnRoot()
