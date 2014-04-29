#ifndef CONTAINER_
#define CONTAINER_

#include "NLREMain\stdafx.h"
#include "RenderingDevice\NLREDeviceController.h"

struct cbPerObject
{
	NLE_FLOAT4X4  WVP;
};

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float u, float v)
		: pos(x, y, z), texCoord(u, v){}

	NLE_FLOAT3 pos;
	NLE_FLOAT2 texCoord;
};

class Container
{
public:
	Container(NLREDeviceController* _deviceController, NLRERenderingDevice* _renderingDevice, int width, int height);
	~Container();

	void render();
private:
	bool initialize();

	NLREDeviceController* _deviceController;
	NLRERenderingDevice* _renderingDevice;

	NLRE_Buffer _vertexBuffer;
	NLRE_Buffer _indexBuffer;
	NLRE_Buffer _constantBuffer;
	NLRE_APIShaderResourceView* _texture;

	NLE_FLOAT4X4* mCamView;
	NLE_FLOAT4X4* mCamProjection;
	NLE_FLOAT4X4* mObjWorld;

	cbPerObject cbPerObj;
};

#endif