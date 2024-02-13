#include "zerotier_node.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void ZeroTierNode::_bind_methods() {
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
}

ZeroTierNode::ZeroTierNode() {
}

ZeroTierNode::~ZeroTierNode() {
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