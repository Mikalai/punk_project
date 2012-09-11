
#ifndef _H_PUNK_STRING
#define _H_PUNK_STRING

class string
{
protected:

	struct Representation
	{
		wchar_t* m_data;
		int m_length;
		int m_useCount;
		Representation(const wchar_t* data, int length);
		Representation(const char* data, int length);
		~Representation();

		Representation* GetOwnCopy();
		void Assign(const wchar_t* data, int length);
		void Assign(const char* data, int length);
		void Append(const wchar_t* data, int length);
	private:
		Representation(const Representation&);
		Representation& operator = (const Representation&);
	};

	Representation* m_rep;
	mutable wchar_t* m_cstring_cache;

public:
	string();
	string(const char* s);
	string(const wchar_t* s);
	string(const string& s);
	string& operator = (const string& s);
	string& operator = (const wchar_t* s);
	string& operator = (const char* s);
	~string();

	wchar_t operator [] (int i) const;
	wchar_t& operator [] (int i);

	int Length() const;

	string& operator += (const string& s);
	string& operator += (const wchar_t* s);

	friend bool operator == (const string& s1, const string& s2);
	friend bool operator == (const string& s1, const wchar_t* s2);

	friend bool operator != (const string& s1, const string& s2);
	friend bool operator != (const string& s1, const wchar_t* s2);

	friend int operator > (const string& s1, const string& s2);
	friend int operator < (const string& s1, const wchar_t* s2);
};

#endif