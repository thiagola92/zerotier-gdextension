#ifndef ZEROTIERNODE_H
#define ZEROTIERNODE_H

#include <godot_cpp/classes/ref_counted.hpp>

namespace godot {

class ZeroTierNode : public RefCounted {
	GDCLASS(ZeroTierNode, RefCounted)

private:
protected:
	static void _bind_methods();

public:
	ZeroTierNode();
	~ZeroTierNode();
};

} //namespace godot

#endif