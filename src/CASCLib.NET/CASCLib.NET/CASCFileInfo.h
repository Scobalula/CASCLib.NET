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
// File: CASCFileStream.cpp
// Author: Philip/Scobalula
// Description: This file contains the CASC File Info Class
#pragma once
#include "pch.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace CASCLibNET
{
	/// <summary>
	/// Provides a class to hold CASC File Info
	/// </summary>
	public ref class CASCFileInfo
	{
	private:
		/// <summary>
		/// File Name
		/// </summary>
		property String^ _FileName;

		/// <summary>
		/// File Size
		/// </summary>
		property Int64 _FileSize;

		/// <summary>
		/// If the File is Local
		/// </summary>
		property Boolean _IsLocal;

		/// <summary>
		/// Content Key
		/// </summary>
		property array<System::Byte>^ _CKey;

		/// <summary>
		/// Encoded Key
		/// </summary>
		property array<System::Byte>^ _EKey;
	public:
		/// <summary>
		/// Gets the File Name
		/// </summary>
		property String^ FileName
		{
			String^ get()
			{
				return _FileName;
			}
		}

		/// <summary>
		/// Gets the File Size
		/// </summary>
		property Int64 FileSize
		{
			Int64 get()
			{
				return _FileSize;
			}
		}

		/// <summary>
		/// Gets if the File is Local
		/// </summary>
		property Boolean IsLocal
		{
			Boolean get()
			{
				return _IsLocal;
			}
		}

		/// <summary>
		/// Gets the Content Key
		/// </summary>
		property array<System::Byte>^ CKey
		{
			array<System::Byte>^ get()
			{
				return _CKey;
			}
		}

		/// <summary>
		/// Gets the Encoded Key
		/// </summary>
		property array<System::Byte>^ EKey
		{
			array<System::Byte>^ get()
			{
				return _EKey;
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="CASCFileInfo"/> class
		/// </summary>
		/// <param name="fileName">Name of the CASC File.</param>
		/// <param name="fileSize">Size of the CASC File.</param>
		/// <param name="isLocal">Whether or not this file is local.</param>
		/// <param name="cKey">File's Content Key.</param>
		/// <param name="eKey">File's Encoded Key.</param>
		CASCFileInfo(
			String^ fileName, 
			Int64 fileSize, 
			Boolean isLocal, 
			array<System::Byte>^ cKey, 
			array<System::Byte>^ eKey);
	};
}

