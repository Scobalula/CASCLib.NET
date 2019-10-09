# CASCLib.NET
[![Releases](https://img.shields.io/github/downloads/Scobalula/CASCLib.NET/total.svg)](https://github.com/Scobalula/Greyhound/releases) [![License](https://img.shields.io/github/license/Scobalula/CASCLib.NET.svg)](https://github.com/Scobalula/Greyhound/blob/master/LICENSE) [![Discord](https://img.shields.io/badge/chat-Discord-blue.svg)](https://discord.gg/fGVpV39)

A wrapper around Ladislav Zezula's CASC Library for .NET that provides classes and methods to read Blizzard's CASC (Content Addressable Storage Container) which are used by multiple games on their platform.

# Using the Library

Download x86/x64 Debug/Release binaries from the [Releases](https://github.com/Scobalula/CASCLib.NET/releases) page and add them to your .NET project. See the [Wiki](https://github.com/Scobalula/CASCLib.NET/wiki) for API documentation or see below for quick examples.

# Reporting Bugs/Contributing

The library has been extensively tested on Overwatch, Call of Duty: Modern Warfare Beta, and Call of Duty: Black Ops IIII. If you find any bugs simply open an issues on the [Issues]() page with the required info. The library was made for my own tools but I'm happy to fix any bugs with specific games, etc. and to possibly provide more features.

If you'd like to contribute simply fork, edit, and make a pull request. Make sure to document methods, properties, etc. Contributed code for this library is assumed to be licensed to me under the same [License](https://github.com/Scobalula/CASCLib.NET/blob/master/LICENSE) as the library.

# Quick Start Examples

Open a CASC Storage:

## C#

```cs
using CASCLibNET;

// Open Overwatch
using (var storage = new CASCStorage("F:\\BattleLib\\Overwatch")) { }
```

## VB Net

```vb
Imports CASCLibNET

' Open Overwatch
Using storage = New CASCStorage("F:\BattleLib\Overwatch")
End Using
```

Open a CASC Storage and print all files:

## C#

```cs
using CASCLibNET;

// Open Black Ops 4
using (var storage = new CASCStorage("F:\\BattleLib\\Call of Duty Black Ops 4"))
{
    Console.WriteLine("Files contained in CASC Storage: {0}", storage.FilePath);

    foreach (var file in storage.Files)
    {
        Console.WriteLine("Name: {0}", file.FileName);
        Console.WriteLine("Size: {0}", file.FileSize);
        Console.WriteLine("Local: {0}", file.IsLocal);
        Console.WriteLine();
    }
}
```

## VB Net

```vb
Imports CASCLibNET

' Open Black Ops 4
Using storage = New CASCStorage("F:\BattleLib\Call of Duty Black Ops 4")
    Console.WriteLine("Files contained in CASC Storage: {0}", storage.FilePath)

    For Each file In storage.Files
        Console.WriteLine("Name: {0}", file.FileName)
        Console.WriteLine("Size: {0}", file.FileSize)
        Console.WriteLine("Local: {0}", file.IsLocal)
        Console.WriteLine()
    Next
End Using
```

Open a CASC Storage and open files:

## C#

```cs
using CASCLibNET;

// Open Black Ops 4
using(var storage = new CASCStorage("F:\\BattleLib\\Call of Duty Black Ops 4"))
{
    // CASCStorage.OpenFile(...) returns a Stream-derived obj that can be passed to BinaryReader, etc.
    foreach(var file in storage.Files)
    {
        using(var reader = storage.OpenFile(file.FileName)) { }
    }
}
```

## VB Net

```vb
Imports CASCLibNET

' Open Black Ops 4
Using storage = New CASCStorage("F:\BattleLib\Call of Duty Black Ops 4")
    For Each file In storage.Files
        ' CASCStorage.OpenFile(...) returns a Stream-derived obj that can be passed to BinaryReader, etc.
        Using reader = storage.OpenFile(file.FileName)
        End Using
    Next
End Using
```

# License/Disclaimers

The library is available under the MIT License like CascLib and can be used for any purpose.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.