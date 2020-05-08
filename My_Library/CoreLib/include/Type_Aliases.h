#pragma once
#include <windef.h>

using ReadType = std::wstring;
using Key_Type = std::wstring;

namespace [[deprecated]] Deprecated 
{
	using HINSTANCE = std::shared_ptr<std::remove_pointer_t<HINSTANCE>>;
	using HWND = std::shared_ptr<std::remove_pointer_t<HWND>>;
	using HBITMAP = std::shared_ptr<std::remove_pointer_t<HBITMAP>>;
	using HDC = std::shared_ptr<std::remove_pointer_t<HDC>>;
	using HINSTANCE = std::shared_ptr<HINSTANCE__>;
	using HWND = std::shared_ptr<HWND__>;
	using HBITMAP = std::shared_ptr<HBITMAP__>;
	using HDC = std::shared_ptr<HDC__>;
	using HFONT = std::shared_ptr<HFONT__>;
	using HBRUSH = std::shared_ptr<HBRUSH__>;
};

