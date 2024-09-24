extends TabBar

var sdk = SuiSDK.new()
var wallets = []
const NFT_PACKAGE_ID = "0x43d037dda49e37c977a1e2a4ed261147659a2913867d439a101c57b41216c216";
const NFT_OBJECT_TYPE = "0x43d037dda49e37c977a1e2a4ed261147659a2913867d439a101c57b41216c216::nft::NFT";

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
		get_node("result").text = "Plase enter your address"
	else:
		var result = sdk.transferNft(NFT_PACKAGE_ID,get_node("address_box").get_item_text(address),nft,recipient)
		get_node("result").text = result

func _on_btn_load_pressed() -> void:
	pass # Replace with function body.


func _on_btn_mint_pressed() -> void:
	var name = get_node("nft_name").text
	var desc = get_node("nft_description").text
	var uri = get_node("nft_uri").text
	if name == ""  or desc == "" or uri == "":
		get_node("result").text = "Plase enter nft info"
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Plase enter your address"
	else:
		var result = sdk.mintNft(NFT_PACKAGE_ID,get_node("address_box").get_item_text(address),name,desc,uri)
		get_node("result").text = result
