#ifndef ZEROTIER_H
#define ZEROTIER_H

#include "zerotier/ZeroTierSockets.h"

#include <godot_cpp/classes/object.hpp>

namespace godot {

class ZeroTier : public Object {
	GDCLASS(ZeroTier, Object)

private:
	static ZeroTier *singleton;

	ZeroTier();
	~ZeroTier();

	static void on_event(void *msg_ptr);

protected:
	static void _bind_methods();

public:
	static ZeroTier *get_singleton();

	int init_from_storage(String path);
	int init_from_memory(String key);

	String addr_get_ip4(uint64_t networkd_id);
	String addr_get_ip6(uint64_t networkd_id);

	int net_join(uint64_t networkd_id);
	int net_leave(uint64_t networkd_id);
	bool net_transport_is_ready(uint64_t networkd_id);

	int node_start();
	bool node_is_online();
	uint64_t node_get_id();
	int node_stop();
};

} //namespace godot

#endif