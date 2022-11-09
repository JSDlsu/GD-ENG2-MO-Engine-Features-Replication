#pragma once
#include <vector>
#include "BNS_GameObjectManager.h"
#include "BNS_RenderPolicies.h"
#include "BNS_AGameObject.h"
#include "BNS_Prerequisites.h"
#include "Matrix4x4.h"

/*
 * performs the draw principle to have a perfect blending of
 * objects in the scene. Two different pass(Opaque or Transparent).
 * Opaque pass:
 * Sorting - nearest -> farthest distance
 * Rendering -> only opaque objects
 * Transparent pass:
 * Sorting - farthest -> nearest distance
 * Rendering -> only transparent objects
 */
template<typename FilteringPolicy, typename SortingPolicy>
class BNS_PassRender
{
public:
	void Render(const BlenderPtr& m_blender, const CameraPtr& camera)
	{
		m_sortingPolicy.SetCamera(camera);
		m_filterPolicy.SetCamera(camera);
		
		std::vector<AGameObjectPtr>& sortedObjects = m_sortingPolicy.sort(BNS_GameObjectManager::get()->GetRenderObjectList());

		for (auto object : sortedObjects)
		{
			if (m_filterPolicy.ShouldRender(object))
				object->Draw(m_blender);
		}
	}
private:
	SortingPolicy m_sortingPolicy;
	FilteringPolicy m_filterPolicy;
};

