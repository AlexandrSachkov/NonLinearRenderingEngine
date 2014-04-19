#ifndef DX_MATH_VECTOR_STORE_FUNCTIONS_
#define DX_MATH_VECTOR_STORE_FUNCTIONS_

static void NLEStoreFloat3(NLE_FLOAT3* destination, const NLE_VECTOR& v);
static void NLEStoreFloat3A(NLE_FLOAT3A* destination, const NLE_VECTOR& v);
static void NLEStoreFloat4(NLE_FLOAT4* destination, const NLE_VECTOR& v);
static void NLEStoreFloat4A(NLE_FLOAT4A* destination, const NLE_VECTOR& v);
static void NLEStoreFloat3x3(NLE_FLOAT3X3* destination, const NLE_MATRIX& v);
static void NLEStoreFloat4x4(NLE_FLOAT4X4* destination, const NLE_MATRIX& v);
static void NLEStoreFloat4x4A(NLE_FLOAT4X4A* destination, const NLE_MATRIX& v);

#endif