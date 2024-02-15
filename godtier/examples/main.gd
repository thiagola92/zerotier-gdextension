extends CenterContainer


var net_id = 0x0cccb752f7bdf645
var zt = ZeroTier.get_singleton()


func _ready() -> void:
	zt.node_online.connect(_on_node_online)
	zt.network_ok.connect(_on_network_ok)
	
	zt.node_up.connect(func(): print("node_up"));
	zt.node_online.connect(func(): print("node_online"));
	zt.node_offline.connect(func(): print("node_offline"));
	zt.node_down.connect(func(): print("node_down"));
	zt.network_not_found.connect(func(): print("network_not_found"));
	zt.network_client_too_old.connect(func(): print("network_client_too_old"));
	zt.network_req_config.connect(func(): print("network_req_config"));
	zt.network_ok.connect(func(): print("network_ok"));
	zt.network_access_denied.connect(func(): print("network_access_denied"));
	zt.network_ready_ip4.connect(func(): print("network_ready_ip4"));
	zt.network_ready_ip6.connect(func(): print("network_ready_ip6"));
	zt.network_ready_ip4_ip6.connect(func(): print("network_ready_ip4_ip6"));
	zt.network_down.connect(func(): print("network_down"));
	zt.network_update.connect(func(): print("network_update"));
	zt.peer_direct.connect(func(): print("peer_direct"));
	zt.peer_relay.connect(func(): print("peer_relay"));
	zt.peer_unreachable.connect(func(): print("peer_unreachable"));
	zt.peer_path_discovered.connect(func(): print("peer_path_discovered"));
	zt.peer_path_dead.connect(func(): print("peer_path_dead"));
	zt.route_added.connect(func(): print("route_added"));
	zt.route_removed.connect(func(): print("route_removed"));
	zt.addr_added_ip4.connect(func(): print("addr_added_ip4"));
	zt.addr_removed_ip4.connect(func(): print("addr_removed_ip4"));
	zt.addr_added_ip6.connect(func(): print("addr_added_ip6"));
	zt.addr_removed_ip6.connect(func(): print("addr_removed_ip6"));
	zt.store_identity_secret.connect(func(): print("store_identity_secret"));
	zt.store_identity_public.connect(func(): print("store_identity_public"));
	zt.store_planet.connect(func(): print("store_planet"));
	zt.store_peer.connect(func(): print("store_peer"));
	zt.store_network.connect(func(): print("store_network"));


func _on_join_pressed() -> void:
	print("Starting")
	
	zt.node_start()


func _on_node_online():
	print("Node online")
	printt("ID:", zt.node_get_id())
	
	zt.net_join(net_id)


func _on_network_ok():
	printt("IPv4", zt.addr_get_ip4(net_id))
	printt("IPv6", zt.addr_get_ip6(net_id))


func _on_stop_pressed() -> void:
	print("Stopping")
	
	zt.node_stop()
