#pragma once

#include "imgui.h"
#include "GL\glew.h"
#include "std_image.h"
#include <iostream>
#include <string>

namespace Meek
{

	class Image 
	{
	public:
		Image(const std::string& path, bool flip = false);
		Image(uint32_t width, uint32_t height, const void* data = nullptr);
		~Image();

		void Invalidate(const void* data);

		ImTextureID GetID();
		float GetWidth();
		float GetHeight();
	private:
		ImTextureID m_ID;

		float m_Width;
		float m_Height;
	};

}