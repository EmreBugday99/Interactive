#include "RendererSystem2D.h"
#include <sstream>
#include "../external/entt/entt.hpp"
#include <glm.hpp>
#include <ext.hpp>
#include <glad/glad.h>
#include "../components/TransformComponent.hpp"
#include "ShaderManager.h"
#include "../components/SpriteComponent.h"
#include "../Engine.h"
#include "../external/imgui/imgui.h"

namespace TurtleEngine
{
	void RendererSystem2D::Render(float deltaTime)
	{
		const auto view = Engine::GetWorld().Registry.view<TransformComponent, SpriteComponent>();

		int i = 0;

		for (const entt::entity entity : view)
		{
			i++;
			SpriteComponent& sprite = view.get<SpriteComponent>(entity);
			TransformComponent& transform = view.get<TransformComponent>(entity);
			//CameraComponent& camera = Registry.ctx<CameraComponent>();

			std::stringstream ssX;
			ssX << "Entity ";
			ssX << std::to_string(i);
			ssX << "Position X";

			std::stringstream ssY;
			ssY << "Entity ";
			ssY << std::to_string(i);
			ssY << "Position Y";

			ImGui::Begin("Entity");
			ImGui::SliderFloat(ssX.str().c_str(), &transform.Position.x, 0, 2);
			ImGui::SliderFloat(ssY.str().c_str(), &transform.Position.y, 0, 2);
			ImGui::End();

			glBindVertexArray(sprite.VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.IBO);

			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform.Position.x, transform.Position.y, 0.0f));

			glUseProgram(sprite.ProgramId);
			ShaderManager::SetUniformData(sprite.ProgramId, "model_mx", translationMatrix);
			ShaderManager::SetUniformData(sprite.ProgramId, "model_mx", translationMatrix);
			//ShaderManager::SetUniformData(sprite.ProgramId, "projection_mx", camera.ProjectionMatrix);
			ShaderManager::SetUniformData(sprite.ProgramId, "projection_mx", Engine::ProjectionMatrix);
			ShaderManager::SetUniformData(sprite.ProgramId, "componentColor", sprite.Color);

			glDrawElements(GL_TRIANGLES, sprite.ElementCount, GL_UNSIGNED_INT, nullptr);

			glUseProgram(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}
}