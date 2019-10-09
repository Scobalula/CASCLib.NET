// ------------------------------------------------------------------------
// CASCLibNet - A wrapper around Ladislav Zezula's CASC Library for .NET
//
// Copyright(c) 2018 Philip/Scobalula
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ------------------------------------------------------------------------
// File: CASCStorage.cpp
// Author: Philip/Scobalula
// Description: This file contains the main CASC Storage Class
#include "pch.h"
#include "CASCStorage.h"

CASCLibNET::CASCStorage::CASCStorage(System::String^ path, System::Int32 localeMask)
{
	// Convert to Native String
#ifdef _UNICODE
	std::wstring filePathStd;
	InteropUtility::ToStdWString(path, filePathStd);
#else
	std::string filePathStd;
	InteropUtility::ToStdString(path, filePathStd);
#endif

	HANDLE handle;
	size_t fileCount;
	size_t result;
	size_t index = 0;

	if (!CascOpenStorage(filePathStd.c_str(), localeMask, &handle))
		throw gcnew System::IO::IOException("Failed to open CASC Storage");

	if(!CascGetStorageInfo(handle, CascStorageTotalFileCount, &fileCount, sizeof(size_t), &result))
		throw gcnew System::IO::IOException("Failed to get CASC Storage Info");

	_Files = gcnew array<CASCFileInfo^>((int)fileCount);

	HANDLE fileHandle;
	CASC_FIND_DATA findData;

	fileHandle = CascFindFirstFile(handle, "*", &findData, NULL);

	if (fileHandle != NULL)
	{
		do
		{
			auto cKey = gcnew array<System::Byte>(sizeof(findData.CKey));
			auto eKey = gcnew array<System::Byte>(sizeof(findData.EKey));

			Marshal::Copy(IntPtr(&findData.CKey), cKey, 0, cKey->Length);
			Marshal::Copy(IntPtr(&findData.EKey), eKey, 0, eKey->Length);

			_Files[(int)index] = gcnew CASCFileInfo(
				gcnew String(findData.szFileName),
				findData.FileSize,
				findData.bFileAvailable == 1,
				cKey,
				eKey);

			index++;
		} 
		while (CascFindNextFile(fileHandle, &findData));
	}

	_StorageHandle = handle;
}

CASCLibNET::CASCStorage::CASCStorage(System::String^ path) : CASCStorage(path, 0)
{
}

CASCLibNET::CASCFileStream^ CASCLibNET::CASCStorage::OpenFile(String^ fileName)
{
	HANDLE handle;

	// Convert to Native String
	std::string filePathStd;
	InteropUtility::ToStdString(fileName, filePathStd);

	if (!CascOpenFile(_StorageHandle, filePathStd.c_str(), 0, 0, &handle))
		throw gcnew System::IO::IOException("Failed to CASC File");

	return gcnew CASCLibNET::CASCFileStream(IntPtr(handle));
}

CASCLibNET::CASCStorage::~CASCStorage()
{
	CascCloseStorage(_StorageHandle);
}
