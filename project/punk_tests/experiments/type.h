//	get typename
template<typename> struct type;

#define TYPE(t) \
template<> \
struct type<void> \
{ \
	const char* toString() \
	{\
		return #t;\
	}\
};

TYPE(void)