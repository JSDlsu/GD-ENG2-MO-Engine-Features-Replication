#include "BNS_Hierarchy_UI.h"

#include "BNS_AGameObject.h"
#include "BNS_GameObjectManager.h"

BNS_Hierarchy_UI::BNS_Hierarchy_UI(std::string name) : BNS_AUIScreen(name)
{

}

BNS_Hierarchy_UI::~BNS_Hierarchy_UI()
{
}

void BNS_Hierarchy_UI::DrawUI()
{
    ImGui::Begin("Hierarchy");
    if (ImGui::TreeNode("SceneName"))
    {
        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_SpanAvailWidth;
        static bool test_drag_and_drop = true;
        
        static int selection_mask = (1 << 2);
        int node_clicked = -1;

        // Call each object's in the scene
        std::vector<AGameObjectPtr> objects = BNS_GameObjectManager::get()->GetObjectList();
        for (int i = 0; i < objects.size(); i++)
        {
            ImGuiTreeNodeFlags node_flags = base_flags;
            const bool is_selected = (selection_mask & (1 << i)) != 0;
            if (is_selected)
            {
	            node_flags |= ImGuiTreeNodeFlags_Selected;
                selectedGameObject = objects[i];
            }

            bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, objects[i]->GetName().c_str(), i);
            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                node_clicked = i;
            if (test_drag_and_drop && ImGui::BeginDragDropSource())
            {
                ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                ImGui::Text("This is a drag and drop source");
                ImGui::EndDragDropSource();
            }
            if (node_open)
            {
                ImGui::BulletText("Child");
                ImGui::TreePop();
            }
        }
        // Leaf Nodes
        /*
                // Items 3..5 are Tree Leaves
                // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                    node_clicked = i;
                if (test_drag_and_drop && ImGui::BeginDragDropSource())
                {
                    ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                    ImGui::Text("This is a drag and drop source");
                    ImGui::EndDragDropSource();
                }*/
        if (node_clicked != -1)
        {
            // Update selection state
            // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
            if (ImGui::GetIO().KeyCtrl)
                selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
            else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                selection_mask = (1 << node_clicked);           // Click to single-select
        }
        ImGui::TreePop();
    }
    ImGui::End();
}
