//#ifndef _H_PROPERTY
//#define _H_PROPERTY
//
//#include "../config.h"
//#include "../code.h"
//
//namespace Logic
//{
//	class PUNK_LOGIC_MODULE Property
//	{
//	public:
//		static const int MAX_PROPERTY_NAME = 64;
//		static const int MAX_PROPERTY_STRING = 128;
//		enum Type {TYPE_INTEGER, TYPE_REAL, TYPE_STRING};
//	private:
//		ID m_name;
//		Type m_type;
//		union
//		{
//			int m_int;
//			double m_real;
//			wchar_t* m_string;
//		};
//	public:
//		Property();
//		Property(ID name);
//		Property(const Property& p);
//		Property& operator = (const Property& p);
//		~Property();
//
//		bool IsProperty(ID name);
//		ID GetName() const;
//		void SetName(ID name);
//		void SetValue(int value);
//		void SetValue(double value);
//		void Inc(int value);
//		void Dec(int value);
//		void Inc(double value);
//		void Dec(double value);
//		void SetValue(const wchar_t* value);
//		int AsInt() const;
//		double AsReal() const;
//		const wchar_t* AsString() const;
//		Type GetType() const;
//	private:
//		void Allocate(int size_in_bytes);
//		void Deallocate();
//	};
//
//}
//#endif
