#ifndef ZEROTIERNODE_H
#define ZEROTIERNODE_H

#include "zerotier/ZeroTierSockets.h"

#include <godot_cpp/classes/object.hpp>

namespace godot {

class ZeroTierNode : public Object {
	GDCLASS(ZeroTierNode, Object)

private:
	static ZeroTierNode *singleton;

	ZeroTierNode();
	~ZeroTierNode();

	static void on_event(void *msg_ptr);

protected:
	static void _bind_methods();

public:
	static ZeroTierNode *get_singleton();

	int init_from_storage(String path);
	int init_from_memory(String key);

	int start();
	int stop();
	bool is_online();
	uint64_t get_id();

	int join_network(uint64_t networkd_id);
	int leave_network(uint64_t networkd_id);
	bool network_transport_is_ready(uint64_t networkd_id);

	String get_ipv4_address(uint64_t networkd_id);
	String get_ipv6_address(uint64_t networkd_id);
};

} //namespace godot

#endif