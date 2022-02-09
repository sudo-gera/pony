#define BOOST_INCLUDED
#if __has_include("boost/numeric/ublas/vector.hpp")
	#include <boost/numeric/ublas/vector.hpp>
#else
	#undef BOOST_INCLUDED
#endif
#if __has_include("boost/numeric/ublas/matrix.hpp")
	#include <boost/numeric/ublas/matrix.hpp>
#else
	#undef BOOST_INCLUDED
#endif
#if __has_include("boost/numeric/ublas/io.hpp")
	#include <boost/numeric/ublas/io.hpp>
#else
	#undef BOOST_INCLUDED
#endif
#if __has_include("boost/pfr/core.hpp")
	#include <boost/pfr/core.hpp>
#else
	#undef BOOST_INCLUDED
#endif

