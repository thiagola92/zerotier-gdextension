#include "zerotier_node.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void ZeroTierNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("start"), &ZeroTierNode::start);
}

ZeroTierNode::ZeroTierNode() {
}

ZeroTierNode::~ZeroTierNode() {
}

void ZeroTierNode::start() {
	zts_node_start();
}