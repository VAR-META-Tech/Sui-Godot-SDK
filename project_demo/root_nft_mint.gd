extends Node2D

var suiSDK = SuiSDK.new()
var packageId = "0x48a557eb090729457000b7303796c4447abea2362b009988b3ab7445b60ed6a3"

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if Global.currentWallet not in "":
		var owner:LineEdit = get_node("Control/Panel/VBoxContainer/VBoxContainer/HBoxContainer/sender")
		owner.text = Global.currentWallet


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func returnRoot():
	get_tree().change_scene_to_file("res://root.tscn")


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
		
	suiSDK.mintNft(packageId, owner.text, name.text, description.text, uri.text)
	returnRoot()	
