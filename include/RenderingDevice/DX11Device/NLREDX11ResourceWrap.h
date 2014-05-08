/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 NonLinear Rendering Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef NLRE_DX11_RESOURCE_WRAP_
#define NLRE_DX11_RESOURCE_WRAP_

#include <d3d11.h>

typedef ID3D11Buffer				NLRE_APIBuffer;
typedef ID3D11VertexShader			NLRE_APIVertexShader;
typedef ID3D11PixelShader			NLRE_APIPixelShader;
typedef D3D11_INPUT_ELEMENT_DESC	NLRE_APIInputLayoutDecs;
typedef ID3D11InputLayout			NLRE_APIInputLayout;
typedef ID3D11ShaderResourceView	NLRE_APIShaderResourceView;
typedef ID3D11RenderTargetView		NLRE_APIRenderTargetView;
typedef ID3D11DepthStencilView		NLRE_APIDepthStencilView;
typedef ID3D11Resource				NLRE_APIResource;
typedef ID3D11Texture2D				NLRE_APITexture2D;
typedef ID3D11RasterizerState		NLRE_APIRasterizerState;
typedef ID3D11SamplerState			NLRE_APISamplerState;
typedef ID3D11BlendState			NLRE_APIBlendState;
typedef ID3DBlob					NLRE_ShaderBlob;

typedef enum NLRE_USAGE
{
	NLRE_USAGE_DEFAULT		= D3D11_USAGE_DEFAULT,
	NLRE_USAGE_IMMUTABLE	= D3D11_USAGE_IMMUTABLE,
	NLRE_USAGE_DYNAMIC		= D3D11_USAGE_DYNAMIC,
	NLRE_USAGE_STAGING		= D3D11_USAGE_STAGING
};

typedef enum NLRE_BIND_FLAG
{
	NLRE_BIND_VERTEX_BUFFER		= D3D11_BIND_VERTEX_BUFFER,
	NLRE_BIND_INDEX_BUFFER		= D3D11_BIND_INDEX_BUFFER,
	NLRE_BIND_CONSTANT_BUFFER	= D3D11_BIND_CONSTANT_BUFFER,
	NLRE_BIND_SHADER_RESOURCE	= D3D11_BIND_SHADER_RESOURCE,
	NLRE_BIND_STREAM_OUTPUT		= D3D11_BIND_STREAM_OUTPUT,
	NLRE_BIND_RENDER_TARGET		= D3D11_BIND_RENDER_TARGET,
	NLRE_BIND_DEPTH_STENCIL		= D3D11_BIND_DEPTH_STENCIL,
	NLRE_BIND_UNORDERED_ACCESS	= D3D11_BIND_UNORDERED_ACCESS,
	NLRE_BIND_DECODER			= D3D11_BIND_DECODER,
	NLRE_BIND_VIDEO_ENCODER		= D3D11_BIND_VIDEO_ENCODER
};

typedef enum NLRE_CULL_MODE
{
	NLRE_CULL_NONE		= D3D11_CULL_NONE,
	NLRE_CULL_FRONT		= D3D11_CULL_FRONT,
	NLRE_CULL_BACK		= D3D11_CULL_BACK
};

typedef enum NLRE_FILL_MODE
{
	NLRE_FILL_WIREFRAME		= D3D11_FILL_WIREFRAME,
	NLRE_FILL_SOLID			= D3D11_FILL_SOLID
};

typedef enum NLRE_PRIMITIVE_TOPOLOGY
{
	NLRE_PRIMITIVE_TOPOLOGY_UNDEFINED			= D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,
	NLRE_PRIMITIVE_TOPOLOGY_POINTLIST			= D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	NLRE_PRIMITIVE_TOPOLOGY_LINELIST			= D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	NLRE_PRIMITIVE_TOPOLOGY_LINESTRIP			= D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	NLRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST		= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	NLRE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP		= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	NLRE_PRIMITIVE_TOPOLOGY_LINELIST_ADJ		= D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
	NLRE_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ		= D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
	NLRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
	NLRE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ	= D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ
};

typedef enum NLRE_TEXTURE_MAP_MODE
{
	NLRE_TEXTURE_MAP_MODE_WRAP			= D3D11_TEXTURE_ADDRESS_WRAP,
	NLRE_TEXTURE_MAP_MODE_CLAMP			= D3D11_TEXTURE_ADDRESS_CLAMP,
	NLRE_TEXTURE_MAP_MODE_DECAL			= D3D11_TEXTURE_ADDRESS_BORDER,
	NLRE_TEXTURE_MAP_MODE_MIRROR		= D3D11_TEXTURE_ADDRESS_MIRROR,
	NLRE_TEXTURE_MAP_MODE_MIRROR_ONCE	= D3D11_TEXTURE_ADDRESS_MIRROR_ONCE
};

#endif