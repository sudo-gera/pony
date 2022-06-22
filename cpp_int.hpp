// // Fixed precision unsigned types:
// typedef number<cpp_int_backend<128, 128, unsigned_magnitude, unchecked, void> >   uint128_t;
// typedef number<cpp_int_backend<256, 256, unsigned_magnitude, unchecked, void> >   uint256_t;
// typedef number<cpp_int_backend<512, 512, unsigned_magnitude, unchecked, void> >   uint512_t;
// typedef number<cpp_int_backend<1024, 1024, unsigned_magnitude, unchecked, void> > uint1024_t;

// // Fixed precision signed types:
// typedef number<cpp_int_backend<128, 128, signed_magnitude, unchecked, void> >     int128_t;
// typedef number<cpp_int_backend<256, 256, signed_magnitude, unchecked, void> >     int256_t;
// typedef number<cpp_int_backend<512, 512, signed_magnitude, unchecked, void> >     int512_t;
// typedef number<cpp_int_backend<1024, 1024, signed_magnitude, unchecked, void> >   int1024_t;

// // Over again, but with checking enabled this time:
// typedef number<cpp_int_backend<0, 0, signed_magnitude, checked> >                 checked_cpp_int;
// typedef rational_adaptor<cpp_int_backend<0, 0, signed_magnitude, checked> >       checked_cpp_rational_backend;
// typedef number<cpp_rational_backend>                                              checked_cpp_rational;

// // Checked fixed precision unsigned types:
// typedef number<cpp_int_backend<128, 128, unsigned_magnitude, checked, void> >     checked_uint128_t;
// typedef number<cpp_int_backend<256, 256, unsigned_magnitude, checked, void> >     checked_uint256_t;
// typedef number<cpp_int_backend<512, 512, unsigned_magnitude, checked, void> >     checked_uint512_t;
// typedef number<cpp_int_backend<1024, 1024, unsigned_magnitude, checked, void> >   checked_uint1024_t;

// // Fixed precision signed types:
// typedef number<cpp_int_backend<128, 128, signed_magnitude, checked, void> >       checked_int128_t;
// typedef number<cpp_int_backend<256, 256, signed_magnitude, checked, void> >       checked_int256_t;
// typedef number<cpp_int_backend<512, 512, signed_magnitude, checked, void> >       checked_int512_t;
// typedef number<cpp_int_backend<1024, 1024, signed_magnitude, checked, void> >     checked_int1024_t;
#ifdef BOOST_INCLUDED
template<size_t N>
using sint=number<cpp_int_backend<N, N, signed_magnitude, unchecked, void> >;
template<size_t N>
using suns=number<cpp_int_backend<N, N, unsigned_magnitude, unchecked, void> >;
template<size_t N>
using csint=number<cpp_int_backend<N, N, signed_magnitude, checked, void> >;
template<size_t N>
using csuns=number<cpp_int_backend<N, N, unsigned_magnitude, checked, void> >;
#endif
