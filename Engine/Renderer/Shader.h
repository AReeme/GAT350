#pragma once
#include "Resource/Resource.h"
#include "Renderer.h"

namespace neu
{
	class Shader : public Resource
	{
	public:
		~Shader();

		virtual bool Create(std::string name, ...) override;

	public:
		GLuint m_shader = 0;
	};
}
