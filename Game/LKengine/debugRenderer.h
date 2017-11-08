#pragma once

#include "shaderProgram.h"
#include "vertex.h"
#include <glm\glm.hpp>
#include <vector>

namespace LKengine {

	class DebugRenderer
	{
	public:
		DebugRenderer();
		~DebugRenderer();

		void init();
		void end();
		void drawBox(glm::vec4& destRect, const ColorRGBA8& color, float angle);
		void drawCircle(const glm::vec2& centre, const ColorRGBA8& color, float radius);
		void render(const glm::mat4& projectionMatrix, float lineWidth);
		void dispose();

		struct DebugVertex {
			glm::vec2 position;
			LKengine::ColorRGBA8 color;
		};

	private:
		LKengine::ShaderProgram m_program;
		std::vector<DebugVertex> m_verts;
		std::vector<GLuint> m_indices;
		GLuint m_vbo = 0, m_vao = 0, m_ibo = 0;

		int m_numElements = 0;
	};

}

