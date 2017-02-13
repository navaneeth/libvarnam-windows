#pragma once

#include "Private.h"
#include "varnam.h"
#include "SampleIMEBaseStructure.h"

class VarnamEngine
{
public:
	// Initializes the varnam Engine
	VarnamEngine();
	BOOL Initialize();
	const char* GetLastError();
	VOID Transliterate(_In_ CStringRange *psrgKeyCode, _Inout_ CSampleImeArray<CCandidateListItem> *pItemList);

private:
	varnam* _handle;
	char* _msg;
};