#pragma once
#include <windef.h>
//
//using HINSTANCE_ptr		= std::shared_ptr<std::remove_pointer_t<HINSTANCE>>;
//using HWND_ptr			= std::shared_ptr<std::remove_pointer_t<HWND>>;
//using HBITMAP_ptr		= std::shared_ptr<std::remove_pointer_t<HBITMAP>>;
//using HDC_ptr			= std::shared_ptr<std::remove_pointer_t<HDC>>;
using HINSTANCE_ptr = std::shared_ptr<HINSTANCE__>;
using HWND_ptr = std::shared_ptr<HWND__>;
using HBITMAP_ptr = std::shared_ptr<HBITMAP__>;
using HDC_ptr = std::shared_ptr<HDC__>;
using HFONT_ptr = std::shared_ptr<HFONT__>;
using HBRUSH_ptr = std::shared_ptr<HBRUSH__>;

using ReadType = std::wstring;
using Key_Type = std::wstring; 

