#include "VarnamEngine.h"
#include "varnam.h"
#include "Private.h"
#include "SampleIMEBaseStructure.h"
#include <stdlib.h>
#include <plog/Log.h>

VarnamEngine::VarnamEngine()
{
	_handle = nullptr;
	_msg = nullptr;
}

BOOL VarnamEngine::Initialize()
{
	std::string program_data(std::getenv("ALLUSERSPROFILE"));
	std::string symbols_dir = program_data + "\\" + "varnam\\schemes";
	varnam_set_symbols_dir(symbols_dir.c_str());
	int rc = varnam_init_from_id("ml", &_handle, &_msg);
	if (rc != VARNAM_SUCCESS) {
		return FALSE;
	}
	return TRUE;
}

const char* VarnamEngine::GetLastError()
{
	return _msg;
}

WCHAR* convert_to_wstring(const char* str)
{
	int str_len = (int)strlen(str);
	int num_chars = MultiByteToWideChar(CP_UTF8, 0, str, str_len, NULL, 0);
	WCHAR* wstrTo = (WCHAR*)malloc((num_chars + 1) * sizeof(WCHAR));
	if (wstrTo)
	{
		MultiByteToWideChar(CP_UTF8, 0, str, str_len, wstrTo, num_chars);
		wstrTo[num_chars] = L'\0';
	}
	return wstrTo;
}

CHAR* convert_from_wstring(const WCHAR* wstr)
{
	int wstr_len = (int)wcslen(wstr);
	int num_chars = WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, NULL, 0, NULL, NULL);
	CHAR* strTo = (CHAR*)malloc((num_chars + 1) * sizeof(CHAR));
	if (strTo)
	{
		WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, strTo, num_chars, NULL, NULL);
		strTo[num_chars] = '\0';
	}
	return strTo;
}

VOID VarnamEngine::Transliterate(_In_ CStringRange *psrgKeyCode, _Inout_ CSampleImeArray<CCandidateListItem> *pItemList)
{
	char* input_text = convert_from_wstring(psrgKeyCode->Get());
	varray* words;
	int rc = varnam_transliterate(_handle, input_text, &words);
	if (rc != VARNAM_SUCCESS) {
		LOGD << "Failed to transliterate: " << input_text << ". " << varnam_get_last_error(_handle);
	}
	else {
		for (int i = 0; i < varray_length(words); i++) {
			CCandidateListItem* pLI = nullptr;
			pLI = pItemList->Append();
			if (pLI) {
				vword* word = (vword*)varray_get(words, i);
				WCHAR* word_text = convert_to_wstring(word->text);
				pLI->_ItemString.Set(word_text, wcslen(word_text));
			}
		}
	}

	free(input_text);
}