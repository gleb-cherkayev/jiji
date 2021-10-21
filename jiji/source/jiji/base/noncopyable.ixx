export module jiji:base.noncopyable;


namespace jiji::no_adl_noncopyable {

/*
	Base class for types that are not supposed to allow copying.
*/
class noncopyable {
protected:
	constexpr noncopyable() = default;
	~noncopyable() = default;

	noncopyable(const noncopyable&) = delete;
	noncopyable& operator=(const noncopyable&) = delete;
};

}  // jiji::no_adl_noncopyable


namespace jiji {
using noncopyable = no_adl_noncopyable::noncopyable;
}  // jiji
