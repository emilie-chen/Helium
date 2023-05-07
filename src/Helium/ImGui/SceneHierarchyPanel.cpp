#include "Helium/HeliumPrecompiled.h"

#include "Helium/ImGui/SceneHierarchyPanel.h"
#include "Helium/CoreGame/Scene.h"
#include "Helium/ObjectModel/RuntimeObjectRegistry.h"

#include <imgui.h>

heliumBegin

SceneHierarchyPanel::SceneHierarchyPanel(Handle<Scene> scene)
	: m_Scene(scene)
{
}

void SceneHierarchyPanel::OnGUIUpdate(F32 dt)
{
	if (ImGui::Begin("Scene Hierarchy"))
	{
		if (ImGui::TreeNode("Scene"))
		{
			std::vector<Handle<Actor>> actors = m_Scene->GetRootActors();
			for (Handle<Actor> actor : actors)
			{
				if (!actor)
					continue;
				RenderActorOnPanel(actor);
			}

			ImGui::TreePop();
		}
	}
	ImGui::End();
}

void SceneHierarchyPanel::RenderActorOnPanel(Handle<Actor> actor)
{
	if (!actor)
		return;

	String actorName = actor->GetName();
	actorName += "##"s + std::to_string(actor->GetInstanceID().instance);

	const Bool result = ImGui::TreeNode(actorName.c_str());
	ImGui::PushID((actorName + "ID").c_str());
	if (ImGui::BeginPopupContextItem((actorName + "Popup").c_str()))
	{
		if (ImGui::MenuItem("Delete"))
		{
			QueueDestroyForEndOfFrame(actor);
		}
		ImGui::EndPopup();
	}
	ImGui::PopID();
	if (result)
	{
		std::vector<Handle<Actor>> children = actor->GetChildren();
		for (Handle<Actor> child : children)
		{
			RenderActorOnPanel(child);
		}
		ImGui::TreePop();
	}
}

heliumEnd

