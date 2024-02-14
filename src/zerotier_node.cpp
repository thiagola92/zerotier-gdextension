#include "zerotier_node.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// https://refactoring.guru/design-patterns/singleton/cpp/example
ZeroTierNode *ZeroTierNode::singleton = nullptr;

void ZeroTierNode::on_event(void *msg_ptr) {
	zts_event_msg_t *msg = (zts_event_msg_t *)msg_ptr;

	switch (msg->event_code) {
		case ZTS_EVENT_NODE_ONLINE:
			singleton->emit_signal("online");
			break;
		case ZTS_EVENT_NODE_OFFLINE:
			singleton->emit_signal("offline");
			break;
		case ZTS_EVENT_NODE_DOWN:
			singleton->emit_signal("down");
			break;
		case ZTS_EVENT_NETWORK_NOT_FOUND:
			break;
		case ZTS_EVENT_NETWORK_CLIENT_TOO_OLD:
			break;
		case ZTS_EVENT_NETWORK_REQ_CONFIG:
			break;
		case ZTS_EVENT_NETWORK_OK:
			singleton->emit_signal("joined_network");
			break;
		case ZTS_EVENT_NETWORK_ACCESS_DENIED:
			singleton->emit_signal("denied_network_access");
			break;
		case ZTS_EVENT_NETWORK_READY_IP4:
			singleton->emit_signal("received_ipv4");
			break;
		case ZTS_EVENT_NETWORK_READY_IP6:
			singleton->emit_signal("received_ipv6");
			break;
		case ZTS_EVENT_NETWORK_DOWN:
			singleton->emit_signal("network_down");
			break;
		case ZTS_EVENT_NETWORK_UPDATE:
			singleton->emit_signal("network_updated");
			break;
		case ZTS_EVENT_PEER_DIRECT:
			singleton->emit_signal("directed_p2p");
			break;
		case ZTS_EVENT_PEER_RELAY:
			singleton->emit_signal("relayed_p2p");
			break;
		case ZTS_EVENT_PEER_UNREACHABLE:
			singleton->emit_signal("unreachable_p2p");
			break;
		case ZTS_EVENT_PEER_PATH_DISCOVERED:
			singleton->emit_signal("discovered_p2p");
			break;
		case ZTS_EVENT_PEER_PATH_DEAD:
			singleton->emit_signal("dead_p2p");
			break;
		case ZTS_EVENT_ROUTE_ADDED:
			singleton->emit_signal("added_route");
			break;
		case ZTS_EVENT_ROUTE_REMOVED:
			singleton->emit_signal("removed_route");
			break;
		case ZTS_EVENT_ADDR_ADDED_IP4:
			singleton->emit_signal("received_new_ipv4");
			break;
		case ZTS_EVENT_ADDR_REMOVED_IP4:
			singleton->emit_signal("removed_ipv4");
			break;
		case ZTS_EVENT_ADDR_ADDED_IP6:
			singleton->emit_signal("received_new_ipv6");
			break;
		case ZTS_EVENT_ADDR_REMOVED_IP6:
			singleton->emit_signal("removed_ipv6");
			break;
		case ZTS_EVENT_STORE_IDENTITY_SECRET:
			singleton->emit_signal("secret_key_stored");
			break;
		case ZTS_EVENT_STORE_IDENTITY_PUBLIC:
			singleton->emit_signal("public_key_stored");
			break;
		case ZTS_EVENT_STORE_PLANET:
			singleton->emit_signal("planet_stored");
			break;
		case ZTS_EVENT_STORE_PEER:
			singleton->emit_signal("peer_stored");
			break;
		case ZTS_EVENT_STORE_NETWORK:
			singleton->emit_signal("network_stored");
			break;
	}
}

ZeroTierNode *ZeroTierNode::get_singleton() {
	if (singleton == nullptr) {
		singleton = memnew(ZeroTierNode);
		zts_init_set_event_handler((void (*)(void *)) & on_event);
	}

	return singleton;
}

int ZeroTierNode::init_from_storage(String path) {
	return zts_init_from_storage((char *)&path);
}

int ZeroTierNode::init_from_memory(String key) {
	return zts_init_from_memory((char *)&key, key.length());
}

int ZeroTierNode::start() {
	return zts_node_start();
}

int ZeroTierNode::stop() {
	return zts_node_stop();
}

bool ZeroTierNode::is_online() {
	return zts_node_is_online();
}

uint64_t ZeroTierNode::get_id() {
	return zts_node_get_id();
}

int ZeroTierNode::join_network(uint64_t networkd_id) {
	return zts_net_join(networkd_id);
}

int ZeroTierNode::leave_network(uint64_t networkd_id) {
	return zts_net_leave(networkd_id);
}

bool ZeroTierNode::network_transport_is_ready(uint64_t networkd_id) {
	return zts_net_transport_is_ready(networkd_id);
}

String ZeroTierNode::get_ipv4_address(uint64_t networkd_id) {
	char addr_str[ZTS_IP_MAX_STR_LEN] = { 0 };
	zts_addr_get_str(networkd_id, ZTS_AF_INET, addr_str, ZTS_IP_MAX_STR_LEN);
	return String(addr_str);
}

String ZeroTierNode::get_ipv6_address(uint64_t networkd_id) {
	char addr_str[ZTS_IP_MAX_STR_LEN] = { 0 };
	zts_addr_get_str(networkd_id, ZTS_AF_INET6, addr_str, ZTS_IP_MAX_STR_LEN);
	return String(addr_str);
}

void ZeroTierNode::_bind_methods() {
	ClassDB::bind_static_method("ZeroTierNode", D_METHOD("get_singleton"), &ZeroTierNode::get_singleton);

	ClassDB::bind_method(D_METHOD("init_from_storage"), &ZeroTierNode::init_from_storage);
	ClassDB::bind_method(D_METHOD("init_from_memory"), &ZeroTierNode::init_from_memory);
	ClassDB::bind_method(D_METHOD("start"), &ZeroTierNode::start);
	ClassDB::bind_method(D_METHOD("stop"), &ZeroTierNode::stop);
	ClassDB::bind_method(D_METHOD("is_online"), &ZeroTierNode::is_online);
	ClassDB::bind_method(D_METHOD("get_id"), &ZeroTierNode::get_id);
	ClassDB::bind_method(D_METHOD("join_network"), &ZeroTierNode::join_network);
	ClassDB::bind_method(D_METHOD("leave_network"), &ZeroTierNode::leave_network);
	ClassDB::bind_method(D_METHOD("network_transport_is_ready"), &ZeroTierNode::network_transport_is_ready);
	ClassDB::bind_method(D_METHOD("get_ipv4_address"), &ZeroTierNode::get_ipv4_address);
	ClassDB::bind_method(D_METHOD("get_ipv6_address"), &ZeroTierNode::get_ipv6_address);

	ADD_SIGNAL(MethodInfo("online"));
	ADD_SIGNAL(MethodInfo("offline"));
	ADD_SIGNAL(MethodInfo("down"));
	ADD_SIGNAL(MethodInfo("joined_network"));
	ADD_SIGNAL(MethodInfo("denied_network_access"));
	ADD_SIGNAL(MethodInfo("received_ipv4"));
	ADD_SIGNAL(MethodInfo("received_ipv6"));
	ADD_SIGNAL(MethodInfo("network_down"));
	ADD_SIGNAL(MethodInfo("network_updated"));
	ADD_SIGNAL(MethodInfo("directed_p2p"));
	ADD_SIGNAL(MethodInfo("relayed_p2p"));
	ADD_SIGNAL(MethodInfo("unreachable_p2p"));
	ADD_SIGNAL(MethodInfo("discovered_p2p"));
	ADD_SIGNAL(MethodInfo("dead_p2p"));
	ADD_SIGNAL(MethodInfo("added_route"));
	ADD_SIGNAL(MethodInfo("removed_route"));
	ADD_SIGNAL(MethodInfo("received_new_ipv4"));
	ADD_SIGNAL(MethodInfo("removed_ipv4"));
	ADD_SIGNAL(MethodInfo("received_new_ipv6"));
	ADD_SIGNAL(MethodInfo("removed_ipv6"));
	ADD_SIGNAL(MethodInfo("secret_key_stored"));
	ADD_SIGNAL(MethodInfo("public_key_stored"));
	ADD_SIGNAL(MethodInfo("planet_stored"));
	ADD_SIGNAL(MethodInfo("peer_stored"));
	ADD_SIGNAL(MethodInfo("network_stored"));
}

ZeroTierNode::ZeroTierNode() {
}

ZeroTierNode::~ZeroTierNode() {
}