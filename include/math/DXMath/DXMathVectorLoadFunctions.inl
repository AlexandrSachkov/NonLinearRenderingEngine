/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

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

#ifdef DX_MATH_VECTOR_LOAD_FUNCTIONS_

inline NLE_VECTOR	NLEMath::NLELoadFloat3		(const NLE_FLOAT3* source)
{
	return DirectX::XMLoadFloat3(source);
}

inline NLE_VECTOR	NLEMath::NLELoadFloat3A(const NLE_FLOAT3A* source)
{
	return DirectX::XMLoadFloat3A(source);
}

inline NLE_MATRIX	NLEMath::NLELoadFloat3x3(const NLE_FLOAT3X3* source)
{
	return DirectX::XMLoadFloat3x3(source);
}

inline NLE_VECTOR	NLEMath::NLELoadFloat4(const NLE_FLOAT4* source)
{
	return DirectX::XMLoadFloat4(source);
}

inline NLE_VECTOR	NLEMath::NLELoadFloat4A(const NLE_FLOAT4A* source)
{
	return DirectX::XMLoadFloat4A(source);
}

inline NLE_MATRIX	NLEMath::NLELoadFloat4x4(const NLE_FLOAT4X4* source)
{
	return XMLoadFloat4x4(source);
}

inline NLE_MATRIX	NLEMath::NLELoadFloat4x4A(const NLE_FLOAT4X4A* source)
{
	return DirectX::XMLoadFloat4x4A(source);
}

#endif
