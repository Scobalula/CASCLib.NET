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
// File: CASCStorage.h
// Author: Philip/Scobalula
// Description: This file contains the main CASC Storage Class
#pragma once
#include "pch.h"
#include "InteropUtility.h"
#include "CASCFileStream.h"
#include "CASCFileInfo.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace CASCLibNET 
{
	/// <summary>
	/// Provides a wrapper around CASCLib
	/// </summary>
	public ref class CASCStorage
	{
	private:
		/// <summary>
		/// The Native Storage Handle
		/// </summary>
		HANDLE _StorageHandle;

		/// <summary>
		/// Storage Path
		/// </summary>
		String^ _FilePath;

		/// <summary>
		/// Files within the CASC Storage
		/// </summary>
		array<CASCFileInfo^>^ _Files;
	public:
		/// <summary>
		/// Gets the CASC File Path
		/// </summary>
		property String^ FilePath
		{
			String^ get()
			{
				return _FilePath;
			}
		}

		/// <summary>
		/// Gets the Files within the Storage
		/// </summary>
		property array<CASCFileInfo^>^ Files
		{
			array<CASCFileInfo^>^ get()
			{
				return _Files;
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="CASCStorage"/> class for the specified path.
		/// </summary>
		/// <param name="path">Path to the storage.</param>
		/// <param name="localeMask">Locale Mask. Only used for World of Warcraft storages.</param>
		CASCStorage(String^ path, Int32 localeMask);

		/// <summary>
		/// Initializes a new instance of the <see cref="CASCStorage"/> class for the specified path.
		/// </summary>
		/// <param name="path">Path to the storage.</param>
		CASCStorage(String^ path);

		/// <summary>
		/// Opens a file that is contained in the CASC
		/// </summary>
		/// <param name="fileName">Name of the file in the CASC.</param>
		/// <returns>
		/// The resulting <see cref="CASCFileStream"/>
		/// </returns>
		CASCFileStream^ OpenFile(String^ fileName);

		/// <summary>
		/// Releases the unmanaged resources used by the <see cref="CASCStorage"/> and optionally releases the managed resources.
		/// </summary>
		~CASCStorage();
	};
}
