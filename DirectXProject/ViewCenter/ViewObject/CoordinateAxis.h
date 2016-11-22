#ifndef COORDINATE_AXIS_H
#define COORDINATE_AXIS_H

#include "../ViewObjectMgr.h"
#include <d3d9.h>
#include "Common/CommonCode.h"

class HCoordinateAxis /*: public HIViewObject */{
private:
	IDirect3DVertexBuffer9 *m_vertexBuffer;

public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void Update();
};

#endif //COORDINATE_AXIS_H