#include "RendererSystem2D.h"

#include "../external/entt/entt.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/SpriteComponent.hpp"
#include "buffers/IndexBuffer.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../components/CameraComponent.hpp"
#include <glad/glad.h>

namespace IE
{
	void RendererSystem2D::Render()
	{
		entt::registry Registry;
		const auto view = Registry.view<TransformComponent, SpriteComponent>();

		for (const entt::entity entity : view)
		{
			SpriteComponent& sprite = view.get<SpriteComponent>(entity);
			TransformComponent& transform = view.get<TransformComponent>(entity);
			CameraComponent& camera = Registry.ctx<CameraComponent>();

			IndexBuffer* ibo = sprite.VAO.IBuffer;
			sprite.VAO.Bind();
			ibo->Bind();

			glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), transform.Position);

			sprite.Shader.UseProgram();
			sprite.Shader.SetUniformData("model_mx", translationMatrix);
			sprite.Shader.SetUniformData("projection_mx", camera.ProjectionMatrix);
			sprite.Shader.SetUniformData("componentColor", sprite.Color);

			glDrawElements(GL_TRIANGLES, ibo->GetElementCount(), GL_UNSIGNED_INT, nullptr);

			sprite.Shader.UnbindProgram();
			ibo->Unbind();
			sprite.VAO.Unbind();
		}
	}

}