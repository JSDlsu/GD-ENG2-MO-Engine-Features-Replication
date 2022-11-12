#pragma once
#include <algorithm>
#include <vector>

#include "Matrix4x4.h"
#include "BNS_AGameObject.h"
#include "BNS_Cube.h"
#include "BNS_Plane.h"
#include "BNS_Prerequisites.h"

class Matrix4x4;

/*
 * contains the different function implementations for the different
 * policies in ‘SortingPolicy’ and ‘RenderPolicy’.
 */
struct BNS_TransparencyFilterPolicy
{
private:
	CameraPtr _camera;
public:
	void SetCamera(const CameraPtr& camera)
	{
		_camera = camera;
	}
	// ignore Opaque pass
	bool ShouldRender(AGameObjectPtr object)
	{
		if (object.get()->GetAlpha() >= 1.0f)
			return false;
		return true;
	}
};

struct BNS_OpaqueFilterPolicy
{
private:
	CameraPtr _camera;
public:
	void SetCamera(const CameraPtr& camera)
	{
		_camera = camera;
	}
	// ignore Transparent pass
	bool ShouldRender(AGameObjectPtr object)
	{
		if (object.get()->GetAlpha() < 1.0f)
			return false;
		return true;
	}
};

struct BNS_BackToFrontPolicy
{
private:
	CameraPtr _camera;
public:
	void SetCamera(const CameraPtr& camera)
	{
		_camera = camera;
	}
	std::vector<AGameObjectPtr> sort(std::vector<AGameObjectPtr> inputArray)
	{
		std::sort(inputArray.begin(), inputArray.end(), [&](AGameObjectPtr& lhs, AGameObjectPtr& rhs)
			{
				return lhs->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition()) >
					rhs->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition());
			});
		return inputArray;
		
	}
private:
	void swap(AGameObjectPtr& xp, AGameObjectPtr& yp)
	{
		AGameObjectPtr temp = xp;
		xp = yp;
		yp = temp;
	}
};

struct BNS_FrontToBackPolicy
{
private:
	CameraPtr _camera;
public:
	void SetCamera(const CameraPtr& camera)
	{
		_camera = camera;
	}
	std::vector<AGameObjectPtr> sort(std::vector<AGameObjectPtr> inputArray)
	{
		std::sort(inputArray.begin(), inputArray.end(), [&](AGameObjectPtr& lhs, AGameObjectPtr& rhs)
			{
				return lhs->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition()) <
					rhs->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition());
			});

		return inputArray;

	}
private:
	void swap(AGameObjectPtr& xp, AGameObjectPtr& yp)
	{
		AGameObjectPtr temp = xp;
		xp = yp;
		yp = temp;
	}
};

class RenderPolicies
{
	
};