#define BOOST_INCLUDED
#if __has_include("boost/numeric/ublas/vector.hpp")
	#include <boost/numeric/ublas/vector.hpp>
#else
	// #warning "boost/numeric/ublas/vector is not available"
	#undef BOOST_INCLUDED
#endif
#if __has_include("boost/numeric/ublas/matrix.hpp")
	#include <boost/numeric/ublas/matrix.hpp>
#else
	// #warning "boost/numeric/ublas/matrix is not available"
	#undef BOOST_INCLUDED
#endif
#if __has_include("boost/numeric/ublas/io.hpp")
	#include <boost/numeric/ublas/io.hpp>
#else
	// #warning "boost/numeric/ublas/io is not available"
	#undef BOOST_INCLUDED
#endif
#if __has_include("boost/pfr/core.hpp")
	#include <boost/pfr/core.hpp>
#else
	// #warning "boost/pfr/core is not available"
	#undef BOOST_INCLUDED
#endif

#if __has_include("boost/multiprecision/cpp_int.hpp")
	#include <boost/multiprecision/cpp_int.hpp>
	using namespace boost::multiprecision;
#else
	// #warning "boost/multiprecision/cpp_int is not available"
	#undef BOOST_INCLUDED
#endif
