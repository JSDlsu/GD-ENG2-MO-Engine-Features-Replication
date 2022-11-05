#pragma once
#include <vector>

#include "Matrix4x4.h"
#include "BNS_AGameObject.h"
#include "BNS_Cube.h"
#include "BNS_Plane.h"
#include "BNS_Mesh.h"
#include "BNS_Prerequisites.h"

class Matrix4x4;

/*
 * contains the different function implementations for the different
 * policies in ‘SortingPolicy’ and ‘RenderPolicy’.
 */
struct BNS_TransparencyFilterPolicy
{
private:
	Matrix4x4 _camera;
public:
	void SetCamera(const Matrix4x4& camera)
	{
		_camera = camera;
	}
	// ignore Opaque pass
	bool ShouldRender(AGameObjectPtr object)
	{
		BNS_AGameObject* raw_obj = object.get();
		switch (raw_obj->ObjectType)
		{
		case BNS_ObjectTypes::CUBE:
		{
			if (dynamic_cast<BNS_Cube*>(raw_obj)->GetAlpha() >= 1.0f)
				return false;
		}
		break;
		case BNS_ObjectTypes::PLANE:
		{
			if (dynamic_cast<BNS_Plane*>(raw_obj)->GetAlpha() >= 1.0f)
				return false;
		}
		break;
		}
		return true;
	}
};

struct BNS_OpaqueFilterPolicy
{
private:
	Matrix4x4 _camera;
public:
	void SetCamera(const Matrix4x4& camera)
	{
		_camera = camera;
	}
	// ignore Transparent pass
	bool ShouldRender(AGameObjectPtr object)
	{
		BNS_AGameObject* raw_obj = object.get();
		switch (raw_obj->ObjectType)
		{
		case BNS_ObjectTypes::CUBE:
		{
			if (dynamic_cast<BNS_Cube*>(raw_obj)->GetAlpha() < 1.0f)
				return false;
		}
		break;
		case BNS_ObjectTypes::PLANE:
		{
			if (dynamic_cast<BNS_Plane*>(raw_obj)->GetAlpha() < 1.0f)
				return false;
		}
		break;
		}
		return true;
	}
};

struct BNS_BackToFrontPolicy
{
private:
	Matrix4x4 _camera;
public:
	void SetCamera(const Matrix4x4& camera)
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
				if (inputArray[j]->GetDistance(_camera) > inputArray[max_idx]->GetDistance(_camera))
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
	Matrix4x4 _camera;
public:
	void SetCamera(const Matrix4x4& camera)
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

			// Find the minimum element in
			// unsorted array
			min_idx = i;
			for (j = i + 1; j < n; j++)
			{
				if (inputArray[j]->GetDistance(_camera) < inputArray[min_idx]->GetDistance(_camera))
					min_idx = j;
			}

			// Swap the found minimum element
			// with the first element
			if (min_idx != i)
				swap(inputArray[min_idx], inputArray[i]);
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

class RenderPolicies
{
	
};