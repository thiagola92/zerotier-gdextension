#include "zerotier.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// https://refactoring.guru/design-patterns/singleton/cpp/example
ZeroTier *ZeroTier::singleton = nullptr;

void ZeroTier::on_event(void *msg_ptr) {
	zts_event_msg_t *msg = (zts_event_msg_t *)msg_ptr;

	switch (msg->event_code) {
		case ZTS_EVENT_NODE_UP:
			singleton->emit_signal("node_up");
			break;
		case ZTS_EVENT_NODE_ONLINE:
			singleton->emit_signal("node_online");
			break;
		case ZTS_EVENT_NODE_OFFLINE:
			singleton->emit_signal("node_offline");
			break;
		case ZTS_EVENT_NODE_DOWN:
			singleton->emit_signal("node_down");
			break;
		case ZTS_EVENT_NETWORK_NOT_FOUND:
			singleton->emit_signal("network_not_found");
			break;
		case ZTS_EVENT_NETWORK_CLIENT_TOO_OLD:
			singleton->emit_signal("network_client_too_old");
			break;
		case ZTS_EVENT_NETWORK_REQ_CONFIG:
			singleton->emit_signal("network_req_config");
			break;
		case ZTS_EVENT_NETWORK_OK:
			singleton->emit_signal("network_ok");
			break;
		case ZTS_EVENT_NETWORK_ACCESS_DENIED:
			singleton->emit_signal("network_access_denied");
			break;
		case ZTS_EVENT_NETWORK_READY_IP4:
			singleton->emit_signal("network_ready_ip4");
			break;
		case ZTS_EVENT_NETWORK_READY_IP6:
			singleton->emit_signal("network_ready_ip6");
			break;
		case ZTS_EVENT_NETWORK_READY_IP4_IP6:
			singleton->emit_signal("network_ready_ip4_ip6");
			break;
		case ZTS_EVENT_NETWORK_DOWN:
			singleton->emit_signal("network_down");
			break;
		case ZTS_EVENT_NETWORK_UPDATE:
			singleton->emit_signal("network_update");
			break;
		case ZTS_EVENT_PEER_DIRECT:
			singleton->emit_signal("peer_direct");
			break;
		case ZTS_EVENT_PEER_RELAY:
			singleton->emit_signal("peer_relay");
			break;
		case ZTS_EVENT_PEER_UNREACHABLE:
			singleton->emit_signal("peer_unreachable");
			break;
		case ZTS_EVENT_PEER_PATH_DISCOVERED:
			singleton->emit_signal("peer_path_discovered");
			break;
		case ZTS_EVENT_PEER_PATH_DEAD:
			singleton->emit_signal("peer_path_dead");
			break;
		case ZTS_EVENT_ROUTE_ADDED:
			singleton->emit_signal("route_added");
			break;
		case ZTS_EVENT_ROUTE_REMOVED:
			singleton->emit_signal("route_removed");
			break;
		case ZTS_EVENT_ADDR_ADDED_IP4:
			singleton->emit_signal("addr_added_ip4");
			break;
		case ZTS_EVENT_ADDR_REMOVED_IP4:
			singleton->emit_signal("addr_removed_ip4");
			break;
		case ZTS_EVENT_ADDR_ADDED_IP6:
			singleton->emit_signal("addr_added_ip6");
			break;
		case ZTS_EVENT_ADDR_REMOVED_IP6:
			singleton->emit_signal("addr_removed_ip6");
			break;
		case ZTS_EVENT_STORE_IDENTITY_SECRET:
			singleton->emit_signal("store_identity_secret");
			break;
		case ZTS_EVENT_STORE_IDENTITY_PUBLIC:
			singleton->emit_signal("store_identity_public");
			break;
		case ZTS_EVENT_STORE_PLANET:
			singleton->emit_signal("store_planet");
			break;
		case ZTS_EVENT_STORE_PEER:
			singleton->emit_signal("store_peer");
			break;
		case ZTS_EVENT_STORE_NETWORK:
			singleton->emit_signal("store_network");
			break;
	}
}

ZeroTier *ZeroTier::get_singleton() {
	if (singleton == nullptr) {
		singleton = memnew(ZeroTier);
		zts_init_set_event_handler((void (*)(void *)) & on_event);
	}

	return singleton;
}

int ZeroTier::init_from_storage(String path) {
	return zts_init_from_storage((char *)&path);
}

int ZeroTier::init_from_memory(String key) {
	return zts_init_from_memory((char *)&key, key.length());
}

int ZeroTier::node_start() {
	return zts_node_start();
}

int ZeroTier::node_stop() {
	return zts_node_stop();
}

bool ZeroTier::node_is_online() {
	return zts_node_is_online();
}

uint64_t ZeroTier::node_get_id() {
	return zts_node_get_id();
}

int ZeroTier::net_join(uint64_t net_id) {
	return zts_net_join(net_id);
}

int ZeroTier::net_leave(uint64_t net_id) {
	return zts_net_leave(net_id);
}

bool ZeroTier::net_transport_is_ready(uint64_t net_id) {
	return zts_net_transport_is_ready(net_id);
}

String ZeroTier::addr_get_ip4(uint64_t net_id) {
	char addr_str[ZTS_IP_MAX_STR_LEN] = { 0 };
	zts_addr_get_str(net_id, ZTS_AF_INET, addr_str, ZTS_IP_MAX_STR_LEN);
	return String(addr_str);
}

String ZeroTier::addr_get_ip6(uint64_t net_id) {
	char addr_str[ZTS_IP_MAX_STR_LEN] = { 0 };
	zts_addr_get_str(net_id, ZTS_AF_INET6, addr_str, ZTS_IP_MAX_STR_LEN);
	return String(addr_str);
}

void ZeroTier::_bind_methods() {
	ClassDB::bind_static_method("ZeroTier", D_METHOD("get_singleton"), &ZeroTier::get_singleton);

	ClassDB::bind_method(D_METHOD("init_from_storage"), &ZeroTier::init_from_storage);
	ClassDB::bind_method(D_METHOD("init_from_memory"), &ZeroTier::init_from_memory);
	ClassDB::bind_method(D_METHOD("node_start"), &ZeroTier::node_start);
	ClassDB::bind_method(D_METHOD("node_stop"), &ZeroTier::node_stop);
	ClassDB::bind_method(D_METHOD("node_is_online"), &ZeroTier::node_is_online);
	ClassDB::bind_method(D_METHOD("node_get_id"), &ZeroTier::node_get_id);
	ClassDB::bind_method(D_METHOD("net_join"), &ZeroTier::net_join);
	ClassDB::bind_method(D_METHOD("net_leave"), &ZeroTier::net_leave);
	ClassDB::bind_method(D_METHOD("net_transport_is_ready"), &ZeroTier::net_transport_is_ready);
	ClassDB::bind_method(D_METHOD("addr_get_ip4"), &ZeroTier::addr_get_ip4);
	ClassDB::bind_method(D_METHOD("addr_get_ip6"), &ZeroTier::addr_get_ip6);

	ADD_SIGNAL(MethodInfo("node_up"));
	ADD_SIGNAL(MethodInfo("node_online"));
	ADD_SIGNAL(MethodInfo("node_offline"));
	ADD_SIGNAL(MethodInfo("node_down"));
	ADD_SIGNAL(MethodInfo("network_not_found"));
	ADD_SIGNAL(MethodInfo("network_client_too_old"));
	ADD_SIGNAL(MethodInfo("network_req_config"));
	ADD_SIGNAL(MethodInfo("network_ok"));
	ADD_SIGNAL(MethodInfo("network_access_denied"));
	ADD_SIGNAL(MethodInfo("network_ready_ip4"));
	ADD_SIGNAL(MethodInfo("network_ready_ip6"));
	ADD_SIGNAL(MethodInfo("network_ready_ip4_ip6"));
	ADD_SIGNAL(MethodInfo("network_down"));
	ADD_SIGNAL(MethodInfo("network_update"));
	ADD_SIGNAL(MethodInfo("peer_direct"));
	ADD_SIGNAL(MethodInfo("peer_relay"));
	ADD_SIGNAL(MethodInfo("peer_unreachable"));
	ADD_SIGNAL(MethodInfo("peer_path_discovered"));
	ADD_SIGNAL(MethodInfo("peer_path_dead"));
	ADD_SIGNAL(MethodInfo("route_added"));
	ADD_SIGNAL(MethodInfo("route_removed"));
	ADD_SIGNAL(MethodInfo("addr_added_ip4"));
	ADD_SIGNAL(MethodInfo("addr_removed_ip4"));
	ADD_SIGNAL(MethodInfo("addr_added_ip6"));
	ADD_SIGNAL(MethodInfo("addr_removed_ip6"));
	ADD_SIGNAL(MethodInfo("store_identity_secret"));
	ADD_SIGNAL(MethodInfo("store_identity_public"));
	ADD_SIGNAL(MethodInfo("store_planet"));
	ADD_SIGNAL(MethodInfo("store_peer"));
	ADD_SIGNAL(MethodInfo("store_network"));
}

ZeroTier::ZeroTier() {
}

ZeroTier::~ZeroTier() {
}