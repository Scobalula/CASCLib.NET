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
// Description: This file contains the CASC File Stream Class
#pragma once
#include "pch.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace CASCLibNET
{
	/// <summary>
	/// Provides a Stream for CASC Files
	/// </summary>
	public ref class CASCFileStream : Stream
	{
	private:
		/// <summary>
		/// The Native File Handle
		/// </summary>
		HANDLE FileHandle;
	public:
		/// <summary>
		/// Gets a value that indicates whether the current stream supports reading.
		/// </summary>
		property bool CanRead
		{
			bool get() override
			{
				return true;
			}
		}

		/// <summary>
		/// Gets a value that indicates whether the current stream supports seeking.
		/// </summary>
		property bool CanSeek
		{
			bool get() override
			{
				return true;
			}
		}

		/// <summary>
		/// Gets a value that indicates whether the current stream supports writing.
		/// </summary>
		property bool CanWrite
		{
			bool get() override
			{
				return false;
			}
		}

		/// <summary>
		/// Gets the length in bytes of the stream.
		/// </summary>
		property Int64 Length
		{
			Int64 get() override
			{
				uint64_t Result = 0;
				CascGetFileSize64(FileHandle, &Result);
				return Result;
			}
		}

		/// <summary>
		/// Gets or sets the current position of this stream.
		/// </summary>
		property Int64 Position
		{
			Int64 get() override
			{
				TCascFile* hf;

				hf = TCascFile::IsValid(FileHandle);
				if (hf == NULL)
					return 0;

				return hf->FilePointer;
			}
			void set(Int64 value) override
			{
				CascSetFilePointer64(FileHandle, value, NULL, FILE_BEGIN);
			}
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="CASCFileStream"/> class for the specified file handle.
		/// </summary>
		/// <param name="handle">CASC File Handle.</param>
		CASCFileStream(IntPtr handle);

		/// <summary>
		/// Clears buffers for this stream and causes any buffered data to be written to the file.
		/// </summary>
		void Flush() override;

		/// <summary>
		/// Reads a block of bytes from the strean and writes the data in a given buffer.
		/// </summary>
		/// <param name="buffer">When this method returns, contains the specified byte array with the values between offset and (offset + count - 1) replaced by the bytes read from the current source.</param>
		/// <param name="offset">The byte offset in array at which the read bytes will be placed.</param>
		/// <param name="count">The maximum number of bytes to read.</param>
		/// <returns>
		/// The total number of bytes read into the buffer. This might be less than the number of bytes requested if that number of bytes are not currently available, or zero if the end of the stream is reached.
		/// </returns>
		int Read(array<System::Byte>^ buffer, Int32 offset, Int32 count) override;

		/// <summary>
		/// Sets the current position of this stream to the given value.
		/// </summary>
		/// <param name="offset">The point relative to origin from which to begin seeking.</param>
		/// <param name="origin">Specifies the beginning, the end, or the current position as a reference point for offset, using a value of type <see cref="SeekOrigin"/>.</param>
		/// <returns>
		/// The new position in the stream.
		/// </returns>
		Int64 Seek(Int64 offset, SeekOrigin origin) override;

		/// <summary>
		/// Sets the length of this stream to the given value.
		/// </summary>
		/// <param name="value">The new length of the stream.</param>
		void SetLength(Int64 value) override;

		/// <summary>
		/// Writes a block of bytes to the stream.
		/// </summary>
		/// <param name="buffer">The buffer containing data to write to the stream.</param>
		/// <param name="offset">The zero-based byte offset in array from which to begin copying bytes to the stream.</param>
		/// <param name="count">The maximum number of bytes to write.</param>
		void Write(array<System::Byte>^ buffer, Int32 offset, Int32 count) override;

		/// <summary>
		/// Releases the unmanaged resources used by the <see cref="CASCFileStream"/> and optionally releases the managed resources.
		/// </summary>
		~CASCFileStream();
	};
}
