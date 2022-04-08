#include "Gl2DRendererSystem.h"
#include "../../external/entt/entt.hpp"
#include <glm.hpp>
#include <ext.hpp>
#include <glad/glad.h>
#include "../../components/TransformComponent.hpp"
#include "ShaderManager.h"
#include "../../components/SpriteComponent.h"
#include "../../Engine.h"

namespace TurtleCore
{
	void Gl2DRendererSystem::Render(float deltaTime)
	{
		const auto view = Engine::GetWorld().Registry.view<TransformComponent, SpriteComponent>();

		for (const entt::entity entity : view)
		{
			SpriteComponent& sprite = view.get<SpriteComponent>(entity);
			TransformComponent& transform = view.get<TransformComponent>(entity);
			//CameraComponent& camera = Registry.ctx<CameraComponent>();

			glBindVertexArray(sprite.VAO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sprite.IBO);

			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform.Position.x, transform.Position.y, 0.0f));

			glUseProgram(sprite.ProgramId);
			ShaderManager::SetUniformData(sprite.ProgramId, "model_mx", translationMatrix);
			ShaderManager::SetUniformData(sprite.ProgramId, "size_vec2", transform.Size);
			//ShaderManager::SetUniformData(sprite.ProgramId, "projection_mx", camera.ProjectionMatrix);
			ShaderManager::SetUniformData(sprite.ProgramId, "projection_mx", Engine::ProjectionMatrix);
			ShaderManager::SetUniformData(sprite.ProgramId, "component_color_vec4", sprite.Color);

			glDrawElements(GL_TRIANGLES, sprite.ElementCount, GL_UNSIGNED_INT, nullptr);

			glUseProgram(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}
}