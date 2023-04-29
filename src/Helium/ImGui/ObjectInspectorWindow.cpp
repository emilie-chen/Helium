#include "Helium/HeliumPrecompiled.h"

#include "ObjectInspectorWindow.h"
#include "Helium/Serialization/Serializer.h"
#include "Helium/Reflection/ManagedPropertyDescriptor.h"

#include <utility>
#include <imgui.h>
#include <imgui_internal.h>

heliumBegin

ObjectInspectorWindow::ObjectInspectorWindow(Handle<ManagedObject> objectToView)
    : m_ObjectToView(objectToView)
{
}

String LabelPrefix(const char* const label)
{
	float width = ImGui::CalcItemWidth();

	float x = ImGui::GetCursorPosX();
	ImGui::Text(label);
	ImGui::SameLine();
	ImGui::SetCursorPosX(x + width * 0.5f + ImGui::GetStyle().ItemInnerSpacing.x);
	ImGui::SetNextItemWidth(-1);

	std::string labelID = "##";
	labelID += label;

	return labelID;
}

void ObjectInspectorWindow::OnGUIUpdate(float deltaTime)
{
    if (!m_IsOpen)
    {
        return;
    }

    ImGui::Begin(("Inspector: "s + m_ObjectToView->ToString()).c_str(), &m_IsOpen);

    if (m_ObjectToView)
    {
        UnsafeHandle<ManagedClassDescriptor> classDescriptor = m_ObjectToView->GetDescriptor();
        ImGui::Text(classDescriptor->GetClassName().c_str());
        const std::vector<UnsafeHandle<ManagedPropertyDescriptor>>& properties = classDescriptor->GetProperties();
        for (const UnsafeHandle<ManagedPropertyDescriptor> property : properties)
        {
            const Bool propertyIsReadOnly = property->IsReadOnly();

            switch (property->GetType())
            {
            case PropertyType::Enum:
            {
                UnsafeHandle<ManagedEnumDescriptor> enumDescriptor = property->GetEnumDescriptor();
                String currentValue = enumDescriptor->GetEnumValueString<U64>(property->GetValue<U64>(m_ObjectToView));
                std::vector<std::pair<String, U64>> enumValues = enumDescriptor->GetEnumPairs();
                if (ImGui::BeginCombo(LabelPrefix(property->GetName().c_str()).c_str(), currentValue.c_str()))
                {
                    for (const std::pair<String, U64>& enumValue : enumValues)
                    {
                        if (ImGui::Selectable(enumValue.first.c_str()))
                        {
                            if (!propertyIsReadOnly)
                            {
								const U64 value = enumValue.second;
								property->SetValue(m_ObjectToView, value);
                            }
						}
					}
                    ImGui::EndCombo();
                }
                break;
            }
            case PropertyType::Bool:
            {
				bool currentValue = property->GetValue<bool>(m_ObjectToView);
                if (ImGui::Checkbox(LabelPrefix(property->GetName().c_str()).c_str(), &currentValue))
                {
                    if (!propertyIsReadOnly)
                    {
						property->SetValue(m_ObjectToView, currentValue);
                    }
				}
				break;
            }
            case PropertyType::Vec3:
            {
                vec3 currentValue = property->GetValue<vec3>(m_ObjectToView);
                if (ImGui::DragFloat3(LabelPrefix(property->GetName().c_str()).c_str(), &currentValue.x, 0.1f, 0.0f, 0.0f, "%.3f", propertyIsReadOnly ? ImGuiSliderFlags_ReadOnly : 0))
                {
                    if (!propertyIsReadOnly)
                    {
                        property->SetValue(m_ObjectToView, currentValue);
                    }
				}
                break;
            }
            case PropertyType::Quat:
            {
                quat currentValue = property->GetValue<quat>(m_ObjectToView);
                // convert to euler angles
                vec3 euler = glm::degrees(glm::eulerAngles(currentValue));
                if (ImGui::DragFloat3(LabelPrefix(property->GetName().c_str()).c_str(), &euler.x, 0.1f, 0.0f, 0.0f, "%.3f", propertyIsReadOnly ? ImGuiSliderFlags_ReadOnly : 0))
                {
                    if (!propertyIsReadOnly)
                    {
						// convert back to quaternion
						currentValue = glm::quat(glm::radians(euler));
						property->SetValue(m_ObjectToView, currentValue);
					}
                }
                break;
            }
            default:
            {
                ImGui::Text(LabelPrefix(property->GetName().c_str()).c_str());
                break;
            }
            }
        }
	}

    ImGui::End();
}

heliumEnd


