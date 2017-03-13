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
				size_t wordLen = strlen(word->text);
				WCHAR* wWord = (WCHAR*)malloc(wordLen + 1);
				int rc = MultiByteToWideChar(
					CP_UTF8,
					0,
					word->text,
					-1,
					wWord,
					wordLen
				);				
				pLI->_ItemString.Set(wWord, rc);				
			}
		}		
	}	
}