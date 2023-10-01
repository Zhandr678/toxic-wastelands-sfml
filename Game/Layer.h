#pragma once
#include <vector>
#include "Block.h"

template <bool b>
class Layer 
{
private:
	bool is_collidable = b;
	std::vector <Block> layer;
public:
	Layer() = delete;
	Layer();
};

