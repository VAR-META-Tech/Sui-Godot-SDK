extends TabBar

var sdk = SuiSDK.new()
var wallets = []
const NFT_PACKAGE_ID = "0x48a557eb090729457000b7303796c4447abea2362b009988b3ab7445b60ed6a3";
const NFT_OBJECT_TYPE = "0x48a557eb090729457000b7303796c4447abea2362b009988b3ab7445b60ed6a3::nft::NFT";

func _ready():
	self.load_wallets()

func  load_wallets():
	wallets = sdk.getWallets()
	var box= get_node("address_box")
	box.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		box.add_item(wallet.get_address(),i)
		
func _on_btn_send_pressed() -> void:
	var nft = get_node("nft_id").text
	var recipient = get_node("address").text
	var uri = get_node("nft_uri").text
	if recipient == ""  or nft == "":
		get_node("result").text = "enter nft and recipient info"
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please enter your address"
	else:
		var result = sdk.transferNft(NFT_PACKAGE_ID,get_node("address_box").get_item_text(address),nft,recipient)
		get_node("result").text = result

func _on_btn_load_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please enter your address"
	else:
		var sender = get_node("address_box").get_item_text(address)
		var objects = sdk.getWalletObjects(sender,NFT_OBJECT_TYPE)
		var res = ""
		print(objects.size())
		for object in objects:
			res = res + "object id: " + object.get_object_id() + "\n"
			res = res + "version: " + str(object.get_version()) + "\n"
			res = res + "digest: " + object.get_digest() + "\n"
			res = res + "type: " + object.get_type() + "\n"
			res = res + "owner: " + object.get_owner() + "\n"
			res = res + "previous transaction: " + object.get_previous_transaction() + "\n"
			res = res + "storage rebate: " + str(object.get_storage_rebate()) + "\n"
			res = res + "display: " + object.get_display() + "\n"
			res = res + "bcs: " + object.get_bcs() + "\n"
			res = res + "content: " + object.get_content() + "\n\n"
		get_node("result").text = res
			


func _on_btn_mint_pressed() -> void:
	var name = get_node("nft_name").text
	var desc = get_node("nft_description").text
	var uri = get_node("nft_uri").text
	if name == ""  or desc == "" or uri == "":
		get_node("result").text = "Please enter nft info"
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please enter your address"
	else:
		var result = sdk.mintNft(NFT_PACKAGE_ID,get_node("address_box").get_item_text(address),name,desc,uri)
		get_node("result").text = result
