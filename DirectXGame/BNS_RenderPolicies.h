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
	BNS_Camera* _camera;
public:
	void SetCamera(BNS_Camera* camera)
	{
		_camera = camera;
	}
	// ignore Opaque pass
	bool ShouldRender(BNS_AGameObject* object)
	{
		if (object->GetAlpha() >= 1.0f)
			return false;
		return true;
	}
};

struct BNS_OpaqueFilterPolicy
{
private:
	BNS_Camera* _camera;
public:
	void SetCamera(BNS_Camera* camera)
	{
		_camera = camera;
	}
	// ignore Transparent pass
	bool ShouldRender(BNS_AGameObject* object)
	{
		if (object->GetAlpha() < 1.0f)
			return false;
		return true;
	}
};

struct BNS_BackToFrontPolicy
{
private:
	BNS_Camera* _camera;
public:
	void SetCamera(BNS_Camera* camera)
	{
		_camera = camera;
	}
	std::vector<BNS_AGameObject*> sort(std::vector<BNS_AGameObject*> inputArray)
	{
		std::sort(inputArray.begin(), inputArray.end(), [&](BNS_AGameObject* lhs, BNS_AGameObject* rhs)
			{
				return lhs->GetLocalPosition().GetMagnitude(_camera->GetLocalPosition()) >
					rhs->GetLocalPosition().GetMagnitude(_camera->GetLocalPosition());
			});
		return inputArray;
		
	}
};

struct BNS_FrontToBackPolicy
{
private:
	BNS_Camera* _camera;
public:
	void SetCamera(BNS_Camera* camera)
	{
		_camera = camera;
	}
	std::vector<BNS_AGameObject*> sort(std::vector<BNS_AGameObject*> inputArray)
	{
		std::sort(inputArray.begin(), inputArray.end(), [&](BNS_AGameObject* lhs, BNS_AGameObject* rhs)
			{
				return lhs->GetLocalPosition().GetMagnitude(_camera->GetLocalPosition()) <
					rhs->GetLocalPosition().GetMagnitude(_camera->GetLocalPosition());
			});

		return inputArray;

	}
};

class RenderPolicies
{
	
};