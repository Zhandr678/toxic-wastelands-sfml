#pragma once
#include <vector>
#include "Block.h"

class Layer 
{
private:
	bool is_collidable;
	std::vector <Block> layer;
public:
	Layer() = delete;
	Layer(std::vector <Block> layer, bool is_collidable);
	~Layer();
};

