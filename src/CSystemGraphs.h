#pragma once

#include "CGraphControl.h"

class CGraphCPU : public CGraphControl {
public:
	CGraphCPU(int xpos, int ypos, int width, int height );

	virtual float VUpdateGraph();
};