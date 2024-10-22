#pragma once

#include <string>
#include <glm.hpp>

struct TagComponent {
	std::string Tag = "Unknown tag";

	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag)
		: Tag(tag) {}

};

struct TransformComponent
{
	glm::vec3 Transform;

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::vec3& transform)
		: Transform(transform) {}

	operator glm::vec3& () { return Transform; }
	operator const glm::vec3& () const { return Transform; }
};

struct MeshRendererComponent
{
	glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	MeshRendererComponent() = default;
	MeshRendererComponent(const MeshRendererComponent&) = default;
	MeshRendererComponent(const glm::vec4& color)
		: Color(color) {}
};