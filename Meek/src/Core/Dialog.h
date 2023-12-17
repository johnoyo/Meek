#pragma once

#include "portable-file-dialogs.h"

#include <string>
#include <vector>

namespace Meek
{
	class SelectFolder
	{
	public:
		SelectFolder(const std::string& title, const std::string& defaultPath)
			: m_Folder(pfd::select_folder(title, defaultPath))
		{
		}

		inline bool Kill() { return m_Folder.kill(); }
		inline bool Ready() { return m_Folder.ready(); }
		inline std::string Result() { return m_Folder.result(); }

	private:
		pfd::select_folder m_Folder;
	};

	class OpenFile
	{
	public:
		OpenFile(const std::string& title, const std::string& defaultPath, const std::vector<std::string>& filters)
			: m_OpenFile(pfd::open_file(title, defaultPath, filters))
		{
		}

		inline bool Kill() { return m_OpenFile.kill(); }
		inline bool Ready() { return m_OpenFile.ready(); }
		inline std::vector<std::string> Result() { return m_OpenFile.result(); }

	private:
		pfd::open_file m_OpenFile;
	};

	class SaveFile
	{
	public:
		SaveFile(const std::string& title, const std::string& defaultPath, const std::vector<std::string>& filters)
			: m_SaveFile(pfd::save_file(title, defaultPath, filters))
		{
		}

		inline bool Kill() { return m_SaveFile.kill(); }
		inline bool Ready() { return m_SaveFile.ready(); }
		inline std::string Result() { return m_SaveFile.result(); }

	private:
		pfd::save_file m_SaveFile;
	};

	class Dialog
	{
	public:
		inline static SaveFile SaveFile(const std::string& title, const std::string& defaultPath = "", const std::vector<std::string>& filters = { "All Files", "*" })
		{ 
			return Meek::SaveFile(title, defaultPath, filters);
		}

		inline static OpenFile OpenFile(const std::string& title, const std::string& defaultPath = "", const std::vector<std::string>& filters = { "All Files", "*" })
		{
			return Meek::OpenFile(title, defaultPath, filters);
		}

		inline static SelectFolder SelectFolder(const std::string& title, const std::string& defaultPath = "")
		{
			return Meek::SelectFolder(title, defaultPath);
		}
	};
}