#include "CSystemGraphs.h"

CGraphCPU::CGraphCPU(int xpos, int ypos, int width, int height ) :
	CGraphControl(xpos, ypos, width, height, 50, 100, 0.3 ) { }

float CGraphCPU::VUpdateGraph() {
	return rand()%100;
}