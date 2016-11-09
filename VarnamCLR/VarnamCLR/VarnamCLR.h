// VarnamCLR.h

#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

#include "varnam.h"

namespace VarnamCLR {

	public ref class Varnam
	{
	public:
		Varnam(String^ scheme)
		{
			varnam_set_symbols_dir("C:\\Users\\Yash\\Documents\\libvarnam-3.2.5\\schemes");
			varnam* h;
			char *errorMessage;
			IntPtr p = Marshal::StringToHGlobalAnsi(scheme);
			const char* _scheme = static_cast<const char*>(p.ToPointer());
			int rc = varnam_init_from_id(_scheme, &h, &errorMessage);
			if (rc != VARNAM_SUCCESS)
			{
				throw gcnew Exception(gcnew String(errorMessage));
			}
			handle = h;
		}

		List<String^>^ Transliterate(String^ input)
		{
			IntPtr p = Marshal::StringToHGlobalAnsi(input);
			const char* _input = static_cast<const char*>(p.ToPointer());
			
			// Words will be initialized into a valid instance after transliteration
			varray *words;
			int rc = varnam_transliterate(handle, _input, &words);
			if (rc != VARNAM_SUCCESS)
			{
				throw gcnew Exception("Failed to transliterate");
			}

			List<String^>^ result = gcnew List<String^>();
			for (int i = 0; i < varray_length(words); i++)
			{
				vword* word = static_cast<vword*>(varray_get(words, i));
				result->Add(ToManagedString(word->text));
			}

			return result;
		}

	private:
		String^ ToManagedString(const char* native)
		{
			int native_len = strlen(native);			
			return gcnew String(native, 0, native_len, System::Text::Encoding::UTF8);
		}

 		varnam* handle;
	};
}
