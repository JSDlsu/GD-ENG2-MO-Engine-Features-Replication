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
	std::vector<AGameObjectPtr>& sort(std::vector<AGameObjectPtr>& inputArray)
	{
		
		int i, j, max_idx;
		int n = inputArray.size();
		// selection sort
		for (i = 0; i < n - 1; i++)
		{
			// Find the maximum element in
			// unsorted array
			max_idx = i;
			for (j = i + 1; j < n; j++)
			{
				if (inputArray[j]->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition()) >
					inputArray[max_idx]->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition()))
					max_idx = j;
			}

			// Swap the found minimum element
			// with the first element
			if (max_idx != i)
				swap(inputArray[max_idx], inputArray[i]);
		}

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
	std::vector<AGameObjectPtr>& sort(std::vector<AGameObjectPtr>& inputArray)
	{
		int i, j, min_idx;
		int n = inputArray.size();
		// selection sort
		for (i = 0; i < n - 1; i++)
		{
			// Find the maximum element in
			// unsorted array
			min_idx = i;
			for (j = i + 1; j < n; j++)
			{
				if (inputArray[j]->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition()) <
					inputArray[min_idx]->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition()))
					min_idx = j;
			}

			// Swap the found minimum element
			// with the first element
			if (min_idx != i)
				swap(inputArray[min_idx], inputArray[i]);
		}

		return inputArray;
		/*
		std::sort(inputArray.begin(), inputArray.end(), [&](AGameObjectPtr& lhs, AGameObjectPtr& rhs)
			{
				return lhs->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition()) <
					rhs->GetLocalPosition().GetMagnitude(_camera.get()->GetLocalPosition());
			});
		std::cout << "First Object: " << inputArray[0].get()->GetName() << std::endl;
		return inputArray;
		*/

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