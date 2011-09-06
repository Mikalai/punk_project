/*
        File: text_file_win32.h
	Author: Nickolai Abramov
	Desc: A simple text file
*/

#ifndef _H_PUNK_TEXT_WIN32_FILE
#define _H_PUNK_TEXT_WIN32_FILE

#include "string_win32.h"

struct _iobuf;

namespace System
{
    class TextFile
    {
        _iobuf* f;        
    public:
        void WriteLine(string line);
        void Write(string text);
        void Write(char value);
        void Write(short value);
        void Write(int value);
        void Write(float value);
        void Write(double value);
        string ReadLine();
		string ReadWord();
        char ReadChar();
        int ReadInt();
        short ReadShort();
        float ReadFloat();
        double ReadDouble();
		void Flush();
        void Close();

        static TextFile Create(const string& filename);
        static TextFile Open(const string& filename);
        static bool IsExist(const string& filename);
    };
}

#endif      //  _H_PUNK_TEXT_WIN32_FILE
