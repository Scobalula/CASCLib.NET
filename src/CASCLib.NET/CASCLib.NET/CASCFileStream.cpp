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
// File: CASCFileInfo.cpp
// Author: Philip/Scobalula
// Description: This file contains the main CASC Storage Class
#include "pch.h"
#include "CASCFileStream.h"

CASCLibNET::CASCFileStream::CASCFileStream(IntPtr handle)
{
	FileHandle = (HANDLE)handle.ToPointer();
}

void CASCLibNET::CASCFileStream::Flush()
{
	throw gcnew NotSupportedException("CASCFileStream is not flushable");
}

int CASCLibNET::CASCFileStream::Read(array<System::Byte>^ buffer, Int32 offset, Int32 count)
{
	DWORD bytesRead = 0;
	auto tempBuffer = std::make_unique<char[]>((size_t)count);
	CascReadFile(FileHandle, tempBuffer.get(), count, &bytesRead);
	Marshal::Copy(IntPtr(tempBuffer.get()), buffer, offset, count);
	return bytesRead;
}

Int64 CASCLibNET::CASCFileStream::Seek(Int64 offset, SeekOrigin origin)
{
	Int64 result = 0;
	CascSetFilePointer64(FileHandle, offset, (PULONGLONG)&result, (DWORD)origin);
	return result;
}

void CASCLibNET::CASCFileStream::SetLength(Int64 value)
{
	throw gcnew NotSupportedException("CASCFileStream does not support SetLength(...)");
}

void CASCLibNET::CASCFileStream::Write(array<System::Byte>^ buffer, Int32 offset, Int32 count)
{
	throw gcnew NotSupportedException("CASCFileStream is not writable");
}

CASCLibNET::CASCFileStream::~CASCFileStream()
{
	CascCloseFile(FileHandle);
}