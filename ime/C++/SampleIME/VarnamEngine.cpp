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
	varnam_set_symbols_dir("C:\\Users\\nkn\\Documents\\libvarnam-3.2.5\\schemes");
}

BOOL VarnamEngine::Initialize()
{	
	int rc = varnam_init("C:\\Users\\nkn\\Documents\\libvarnam-3.2.5\\schemes\\ml.vst", &_handle, &_msg);
	if (rc != VARNAM_SUCCESS)
	{		
		return FALSE;
	}
	
	return TRUE;
}

const char* VarnamEngine::GetLastError()
{
	return _msg;
}

// Convert an UTF8 string to a wide Unicode String
WCHAR* utf8_decode_to_wide(const char* str, int* size)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str, (int)strlen(str), NULL, 0);
	WCHAR* wstrTo = (WCHAR*)malloc(size_needed);
	//std::wstring* wstrTo = new std::wstring(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)strlen(str), wstrTo, size_needed);
	*size = size_needed;
	return wstrTo;
}

VOID VarnamEngine::Transliterate(_In_ CStringRange *psrgKeyCode, _Inout_ CSampleImeArray<CCandidateListItem> *pItemList)
{
	const DWORD_PTR inputLen = psrgKeyCode->GetLength();
	char* text = (char*) malloc(inputLen + 1);
	wcstombs(text, psrgKeyCode->Get(), inputLen);
	text[inputLen] = '\0';
	varray* words;		
	int rc = varnam_transliterate(_handle, text, &words);
	if (rc != VARNAM_SUCCESS)
	{
		LOGD << "Failed to transliterate: " << text << ". " << varnam_get_last_error(_handle);
	}
	else {		
		for (int i = 0; i < varray_length(words); i++) {			
			vword* word = (vword*) varray_get(words, i);
			CCandidateListItem* pLI = nullptr;
			pLI = pItemList->Append();
			if (pLI)
			{				
				//size_t wordLen = strlen(word->text);
				//WCHAR* wWord = (WCHAR*)malloc(wordLen + 1);
				int size;
				WCHAR* wWord = utf8_decode_to_wide(word->text, &size);

				pLI->_ItemString.Set(wWord, size);
				//pLI->_ItemString.Set(L"na", 2);
			}
		}		
	}	
}