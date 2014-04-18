#include "stdafx.h"
#include "math\DXMath\DXMathMatrixFunctions.h"

inline NLE_MATRIX	NLEMatrixAffineTransformation(NLE_VECTOR scaling, NLE_VECTOR rotationOrigin,
	NLE_VECTOR rotationQuaternion, NLE_VECTOR translation)
{
	return XMMatrixAffineTransformation(scaling, rotationOrigin, rotationQuaternion, translation);
}

inline NLE_MATRIX	NLEMatrixAffineTransformation2D(NLE_VECTOR scaling, NLE_VECTOR rotationOrigin,
	float rotation, NLE_VECTOR translation)
{
	return XMMatrixAffineTransformation2D(scaling, rotationOrigin, rotation, translation);
}

inline bool NLEMatrixDecompose(NLE_VECTOR* outScale, NLE_VECTOR* outRotQuat, NLE_VECTOR* outTrans, NLE_MATRIX m)
{
	return XMMatrixDecompose(outScale, outRotQuat, outTrans, m);
}

inline NLE_VECTOR	NLEMatrixDeterminant(NLE_MATRIX m)
{
	return XMMatrixDeterminant(m);
}

inline NLE_MATRIX	NLEMatrixIdentity			()
{
	return XMMatrixIdentity();
}

inline NLE_MATRIX	NLEMatrixInverse			(NLE_VECTOR* pDeterminant, NLE_MATRIX m)
{
	return XMMatrixInverse(pDeterminant, m);
}

inline bool			NLEMatrixIsIdentity			(NLE_MATRIX m)
{
	return XMMatrixIsIdentity(m);
}

inline bool			NLEMatrixIsInfinite			(NLE_MATRIX m)
{
	return XMMatrixIsInfinite(m);
}

inline bool			NLEMatrixIsNaN				(NLE_MATRIX m)
{
	return XMMatrixIsNaN(m);
}

inline NLE_MATRIX	NLEMatrixLookAtLH			(NLE_VECTOR eyePosition, NLE_VECTOR focusPosition, NLE_VECTOR upDirection)
{
	return XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
}

inline NLE_MATRIX	NLEMatrixLookAtRH			(NLE_VECTOR eyePosition, NLE_VECTOR focusPosition, NLE_VECTOR upDirection)
{
	return XMMatrixLookAtRH(eyePosition, focusPosition, upDirection);
}

inline NLE_MATRIX	NLEMatrixMultiply			(NLE_MATRIX m1, NLE_MATRIX m2)
{
	return XMMatrixMultiply(m1, m2);
}

inline NLE_MATRIX	NLEMatrixMultiplyTranspose	(NLE_MATRIX m1, NLE_MATRIX m2)
{
	return XMMatrixMultiplyTranspose(m1, m2);
}

inline NLE_MATRIX	NLEMatrixOrthographicLH				(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixOrthographicOffCenterLH	(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return XMMatrixOrthographicOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixOrthographicOffCenterRH	(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return XMMatrixOrthographicOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixOrthographicRH				(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return XMMatrixOrthographicRH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixPerspectiveFovLH			(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return XMMatrixPerspectiveFovLH(fovAngleY, aspectRatio, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixPerspectiveFovRH			(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
	return XMMatrixPerspectiveFovRH(fovAngleY, aspectRatio, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixPerspectiveLH				(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return XMMatrixPerspectiveLH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixPerspectiveOffCenterLH		(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return XMMatrixPerspectiveOffCenterLH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixPerspectiveOffCenterRH		(float viewLeft, float viewRight, float viewBottom, float viewTop, float nearZ, float farZ)
{
	return XMMatrixPerspectiveOffCenterRH(viewLeft, viewRight, viewBottom, viewTop, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixPerspectiveRH				(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	return XMMatrixPerspectiveRH(viewWidth, viewHeight, nearZ, farZ);
}

inline NLE_MATRIX	NLEMatrixReflect				(NLE_VECTOR reflectionPlane)
{
	return XMMatrixReflect(reflectionPlane);
}

inline NLE_MATRIX	NLEMatrixRotationAxis			(NLE_VECTOR axis, float angle)
{
	return XMMatrixRotationAxis(axis, angle);
}

inline NLE_MATRIX	NLEMatrixRotationNormal			(NLE_VECTOR normalAxis, float angle)
{
	return XMMatrixRotationNormal(normalAxis, angle);
}

inline NLE_MATRIX	NLEMatrixRotationQuaternion		(NLE_VECTOR quaternion)
{
	return XMMatrixRotationQuaternion(quaternion);
}

inline NLE_MATRIX	NLEMatrixRotationRollPitchYaw	(float pitch, float yaw, float roll)
{
	return XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
}

inline NLE_MATRIX	NLEMatrixRotationRollPitchYawFromVector	(NLE_VECTOR angles)
{
	return XMMatrixRotationRollPitchYawFromVector(angles);
}

inline NLE_MATRIX	NLEMatrixRotationX		(float angle)
{
	return NLEMatrixRotationX(angle);
}

inline NLE_MATRIX	NLEMatrixRotationY		(float angle)
{
	return NLEMatrixRotationY(angle);
}

inline NLE_MATRIX	NLEMatrixRotationZ		(float angle)
{
	return NLEMatrixRotationZ(angle);
}

inline NLE_MATRIX	NLEMatrixScaling		(float scaleX, float scaleY, float scaleZ)
{
	return XMMatrixScaling(scaleX, scaleY, scaleZ);
}

inline NLE_MATRIX	NLEMatrixScalingFromVector(NLE_VECTOR scale)
{
	return XMMatrixScalingFromVector(scale);
}

inline NLE_MATRIX	NLEMatrixSet(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	return XMMatrixSet(m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33);
}

inline NLE_MATRIX	NLEMatrixShadow(NLE_VECTOR shadowPlane, NLE_VECTOR lightPosition)
{
	return XMMatrixShadow(shadowPlane, lightPosition);
}

inline NLE_MATRIX	NLEMatrixTransformation(NLE_VECTOR scalingOrigin, NLE_VECTOR scalingOrientationQuaternion,
	NLE_VECTOR scaling, NLE_VECTOR rotaionOrigin,
	NLE_VECTOR rotationQuaternion, NLE_VECTOR translation)
{
	return XMMatrixTransformation(scalingOrigin, scalingOrientationQuaternion,
		scaling, rotaionOrigin,
		rotationQuaternion, translation);
}

inline NLE_MATRIX	NLEMatrixTransformation2D(NLE_VECTOR scalingOrigin, float scalingOrientation,
	NLE_VECTOR scaling, NLE_VECTOR rotaionOrigin,
	float rotation, NLE_VECTOR translation)
{
	return XMMatrixTransformation2D(scalingOrigin, scalingOrientation,
		scaling, rotaionOrigin,
		rotation, translation);
}

inline NLE_MATRIX	NLEMatrixTranslation(float offsetX, float offsetY, float offsetZ)
{
	return XMMatrixTranslation(offsetX, offsetY, offsetZ);
}

inline NLE_MATRIX	NLEMatrixTranslationFromVector(NLE_VECTOR offset)
{
	return XMMatrixTranslationFromVector(offset);
}

inline NLE_MATRIX	NLEMatrixTranspose(NLE_MATRIX m)
{
	return XMMatrixTranspose(m);
}