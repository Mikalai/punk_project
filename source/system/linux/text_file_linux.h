/*
        File: text_file_linux.h
	Author: Nickolai Abramov
	Desc: A simple text file
*/

#ifndef _H_PUNK_LINUX_TEXT_FILE
#define _H_PUNK_LINUX_TEXT_FILE

struct _iobuf;
struct _IO_FILE;

namespace System
{
    class TextFile
    {
        _IO_FILE* f;        
    public:
        void WriteLine(const char* line);
        void WriteLine(const wchar_t* line);
        void Write(const char* text);
        void Write(const wchar_t* text);
        void Write(char value);
        void Write(short value);
        void Write(int value);
        void Write(float value);
        void Write(double value);
        void ReadLine(char* buffer, int bufferSize);
        char ReadChar();
        int ReadInt();
        short ReadShort();
        float ReadFloat();
        double ReadDouble();
        void Close();

        static TextFile Create(const char* filename);
        static TextFile Open(const char* filename);
        static bool IsExist(const char* filename);
    };
}

#endif
