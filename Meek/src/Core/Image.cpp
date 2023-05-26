#include "Image.h"

namespace Meek
{
	Image::Image(const std::string& path, bool flip)
	{
		int w, h, bits;

		if (flip)
			stbi_set_flip_vertically_on_load(1);
		else
			stbi_set_flip_vertically_on_load(0);

		auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb_alpha);
		assert(pixels);

		uint32_t tex_id;
		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		stbi_image_free(pixels);

		m_Width = (float)w;
		m_Height = (float)h;

		m_ID = (void*)tex_id;
	}

	Image::Image(uint32_t width, uint32_t height, const void* data)
	{
		uint32_t tex_id;
		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (int)width, (int)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		m_Width = (float)width;
		m_Height = (float)height;

		m_ID = (void*)tex_id;
	}

	Image::~Image()
	{
		glDeleteTextures(1, &(uint32_t)m_ID);
	}

	void Image::Invalidate(const void* data)
	{
		glBindTexture(GL_TEXTURE_2D, (uint32_t)m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (int)m_Width, (int)m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	ImTextureID Image::GetID()
	{
		return m_ID;
	}

	float Image::GetWidth()
	{
		return m_Width;
	}

	float Image::GetHeight()
	{
		return m_Height;
	}
}
