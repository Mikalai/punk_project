#ifdef _WIN32

#include <stdio.h>
#include "text_file_win32.h"

namespace System
{
    TextFile TextFile::Create(const string& filename)
    {

        TextFile file;
		_wfopen_s(&file.f, filename.Data(), L"wt");
        return file;
    }

    TextFile TextFile::Open(const string& filename)
    {
        TextFile file;
        _wfopen_s(&file.f, filename.Data(), L"rt");
        return file;
    }

    bool TextFile::IsExist(const string& filename)
    {
        FILE* f = 0;
		_wfopen_s(&f, filename.Data(), L"rt");
        if (f == NULL)
            return false;
        fclose(f);
        return true;
    }

    void TextFile::Close()
    {
        fclose(f);
    }

    double TextFile::ReadDouble()
    {
        double res;
        fscanf(f, "%f", &res);
        return res;
    }

    float TextFile::ReadFloat()
    {
        float res;
        fscanf(f, "%f", &res);
        return res;
    }

    short TextFile::ReadShort()
    {
        short res;
        fscanf(f, "%d", &res);
        return res;
    }

    int TextFile::ReadInt()
    {
        int res;
        fscanf(f, "%d", &res);
        return res;
    }

    char TextFile::ReadChar()
    {
        return static_cast<char>(fgetc(f));
    }

    void TextFile::ReadLine(char *buffer, int bufferSize)
    {
        fgets(buffer, bufferSize, f);
    }

    void TextFile::Write(char value)
    {
        fputc(static_cast<int>(value), f);
    }

    void TextFile::Write(const char *text)
    {
        fputs(text, f);
    }

    void TextFile::Write(const wchar_t *text)
    {
        fputws(text, f);
    }

    void TextFile::Write(double value)
    {
        fprintf(f, "%f", value);
    }

    void TextFile::Write(float value)
    {
        fprintf(f, "%f", value);
    }

    void TextFile::Write(int value)
    {
        fprintf(f, "%d", value);
    }

    void TextFile::Write(short value)
    {
        fprintf(f, "%d", value);
    }

    void TextFile::WriteLine(const char *line)
    {
        fputs(line, f);
        fputc('\n', f);
    }

    void TextFile::WriteLine(const wchar_t *line)
    {
        fputws(line, f);
        fputwc('\n', f);
    }

	void TextFile::Flush()
	{
		fflush(f);
	}
}

#endif // _WIN32
