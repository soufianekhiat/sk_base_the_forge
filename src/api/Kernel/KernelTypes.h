#pragma once

#include <api/Kernel/KernelDebug.h>

EMV_DISABLE_WARNING_START
#ifdef EMV_COMPILER_MSVCPP
EMV_DISABLE_WARNING( 4530 )
#endif
#include <cstdint>
#include <cstddef>
#include <iomanip>
EMV_DISABLE_WARNING_END

typedef	void					Void;

typedef	bool					Bool;

typedef std::byte				Byte;

typedef	std::uint8_t			UInt8;
typedef	std::uint16_t			UInt16;
typedef	std::uint32_t			UInt32;
typedef	std::uint64_t			UInt64;

typedef	std::int8_t				Int8;
typedef	std::int16_t			Int16;
typedef	std::int32_t			Int32;
typedef	std::int64_t			Int64;

typedef	UInt64					AnyData;
typedef	UInt64 const			AnyDataConst;

typedef	char					CharASCII;
typedef	char8_t					CharUTF8;
typedef	char16_t				CharUTF16;
typedef	char32_t				CharUTF32;
typedef	wchar_t					CharWide;

typedef	void*					Ptr;
typedef	void const*				PtrConst;
typedef	void const* const		PtrConst_Const;
typedef	void* const				Ptr_Const;

typedef	float					f32;
typedef	double					f64;
typedef	long double				f80;

namespace Internal {
	extern UInt16	f32_to_f16( f32 value );
	extern UInt16	f32_to_bf16( f32 f );
	extern f32		f16_to_f32( UInt16 const value );
	extern f32		bf16_to_f32( UInt16 const b );
	extern UInt16	bf16_to_f16( UInt16 const b );
	extern UInt16	f16_to_bf16( UInt16 const b );
}

struct bf16;

// CPU to store data for GPU f16
struct f16
{
	f16() : _( 0 ) {}
	f16( Bool const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( UInt8 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( UInt16 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( UInt32 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( UInt64 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( Int8 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( Int16 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( Int32 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( Int64 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( f16 const& t ) : _( t._ ) {}
	//f16( bf16 const& t ) : _( t._ ) {}
	f16( f32 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}
	f16( f64 const t ) : _( Internal::f32_to_f16( static_cast< f32 >( t ) ) ) {}

	static
	f16 FromBits( UInt16 const bits )
	{
		f16 out;
		out._ = bits;
		return out;
	}

	eMVForceInline
	void AssignBits( UInt16 const bits )
	{
		_ = bits;
	}

	eMVForceInline
	UInt16 GetBits() const
	{
		return _;
	}

	eMVForceInline
	f16& operator=( f16 const& f )
	{
		_ = f._;
		return *this;
	}

	eMVForceInline
	bool operator==( f16 const f )
	{
		return _ == f._;
	}

	eMVForceInline
	bool operator!=( f16 const f )
	{
		return _ != f._;
	}

	eMVForceInline
	operator Bool() const
	{
		return _ != 0;
	}

	eMVForceInline
	operator UInt8() const
	{
		return static_cast< UInt8 >( Internal::f16_to_f32( _ ) );
	}

	eMVForceInline
	operator UInt16() const
	{
		return static_cast< UInt16 >( Internal::f16_to_f32( _ ) );
	}

	eMVForceInline
	operator UInt32() const
	{
		return static_cast< UInt32 >( Internal::f16_to_f32( _ ) );
	}

	eMVForceInline
	operator UInt64() const
	{
		return static_cast< UInt32 >( Internal::f16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int8() const
	{
		return static_cast< Int8 >( Internal::f16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int16() const
	{
		return static_cast< Int16 >( Internal::f16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int32() const
	{
		return static_cast< Int32 >( Internal::f16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int64() const
	{
		return static_cast< Int32 >( Internal::f16_to_f32( _ ) );
	}

	//operator bf16() const
	//{
	//	return Internal::f32_to_bf16( Internal::f16_to_f32( _ ) );
	//}

	eMVForceInline
	operator f32() const
	{
		return Internal::f16_to_f32( _ );
	}

	eMVForceInline
	operator f64() const
	{
		return static_cast< f64 >( Internal::f16_to_f32( _ ) );
	}

	UInt16 _;
};

struct bf16
{
	bf16() : _( 0 ) { }
	bf16( Bool const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( UInt8 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( UInt16 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( UInt32 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( UInt64 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( Int8 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( Int16 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( Int32 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( Int64 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( f16 const& t ) : _( Internal::f16_to_bf16( t._ ) ) {}
	bf16( bf16 const& t ) : _( t._ ) {}
	bf16( f32 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}
	bf16( f64 const t ) : _( Internal::f32_to_bf16( static_cast< f32 >( t ) ) ) {}

	static
	bf16 FromBits( UInt16 const bits )
	{
		bf16 out;
		out._ = bits;
		return out;
	}

	eMVForceInline
	void AssignBits( UInt16 const bits )
	{
		_ = bits;
	}

	eMVForceInline
	UInt16 GetBits() const
	{
		return _;
	}

	eMVForceInline
	bf16& operator=( bf16 const& f )
	{
		_ = f._;
		return *this;
	}

	eMVForceInline
	bool operator==( bf16 const f )
	{
		return _ == f._;
	}
	eMVForceInline
	bool operator!=( bf16 const f )
	{
		return _ != f._;
	}

	eMVForceInline
	operator Bool() const
	{
		return _ != 0;
	}

	eMVForceInline
	operator UInt8() const
	{
		return static_cast< UInt8 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator UInt16() const
	{
		return static_cast< UInt16 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator UInt32() const
	{
		return static_cast< UInt32 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator UInt64() const
	{
		return static_cast< UInt32 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int8() const
	{
		return static_cast< Int8 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int16() const
	{
		return static_cast< Int16 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int32() const
	{
		return static_cast< Int32 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator Int64() const
	{
		return static_cast< Int32 >( Internal::bf16_to_f32( _ ) );
	}

	eMVForceInline
	operator f16() const
	{
		return Internal::bf16_to_f16( _ );
	}

	eMVForceInline
	operator f32() const
	{
		return Internal::bf16_to_f32( _ );
	}

	eMVForceInline
	operator f64() const
	{
		return static_cast< f64 >( Internal::bf16_to_f32( _ ) );
	}

	UInt16 _;
};

#ifdef SCALAR64
typedef	f64						Scalar;
typedef	Int64					Integer;
typedef	UInt64					UInteger;
#else
typedef	f32						Scalar;
typedef	Int32					Integer;
typedef	UInt32					UInteger;
#endif

#ifdef __EMV_WIN32__
typedef	UInt32					Address;
#elif defined( __EMV_X64__ )
typedef	UInt64					Address;
#endif

typedef	decltype( nullptr )		NullPtrType;

#ifdef __EMV_WIN32__
typedef	UInt16					UPlatformHalfWord;
typedef	Int16					PlatformHalfWord;
typedef	UInt32					UPlatformWord;
typedef	Int32					PlatformWord;
typedef	UInt64					UPlatformDoubleWord;
typedef	Int64					PlatformDoubleWord;
#elif defined( __EMV_X64__ )
typedef	UInt32					UPlatformHalfWord;
typedef	Int32					PlatformHalfWord;
typedef	UInt64					UPlatformWord;
typedef	Int64					PlatformWord;
// Add UInt128 & SInt128 As {S}PlateformDoubleWord
#endif

#define eMVPtrToAdress( pPtr )		static_cast< Address >( reinterpret_cast< std::uintptr_t >( pPtr ) )
#define eMVAdressToPtr( uAddress )	reinterpret_cast< Ptr >( static_cast< Address >( uAddress ) )

#define	EMV_DECLARE_TEMPLATE_TYPE( TemplateType, NewNameType )		\
				typedef	TemplateType< Scalar >	NewNameType;		\
				typedef	TemplateType< UInt8 >	NewNameType ## u8;	\
				typedef	TemplateType< UInt16 >	NewNameType ## u16;	\
				typedef	TemplateType< UInt32 >	NewNameType ## u32;	\
				typedef	TemplateType< UInt64 >	NewNameType ## u64;	\
				typedef	TemplateType< Int8 >	NewNameType ## i8;	\
				typedef	TemplateType< Int16 >	NewNameType ## i16;	\
				typedef	TemplateType< Int32 >	NewNameType ## i32;	\
				typedef	TemplateType< Int64 >	NewNameType ## i64;	\
				typedef	TemplateType< f32 >		NewNameType ## f32;	\
				typedef	TemplateType< f64 >		NewNameType ## f64;	\
				typedef	TemplateType< f80 >		NewNameType ## f80;	\
				typedef	TemplateType< f32 >		NewNameType ## f;	\
				typedef	TemplateType< f64 >		NewNameType ## d;	\
				typedef	TemplateType< Int32 >	NewNameType ## i;	\
				typedef	TemplateType< UInt32 >	NewNameType ## u	

#define	EMV_ENUMIFY_MIXED( X, Type )															\
	inline																						\
	X	operator|( X const eA, X const eB )														\
	{																							\
		return static_cast< X >( static_cast< Type >( eA ) | static_cast< Type >( eB ) );		\
	}																							\
	inline																						\
	X	operator&( X const eA, X const eB )														\
	{																							\
		return static_cast< X >( static_cast< Type >( eA ) & static_cast< Type >( eB ) );		\
	}																							\
	inline																						\
	X	operator^( X const eA, X const eB )														\
	{																							\
		return static_cast< X >( static_cast< Type >( eA ) ^ static_cast< Type >( eB ) );		\
	}																							\
	inline																						\
	X&	operator|=( X& eA, X const eB )															\
	{																							\
		return eA = static_cast< X >( static_cast< Type >( eA ) | static_cast< Type >( eB ) );	\
	}																							\
	inline																						\
	X&	operator&=( X& eA, X const eB )															\
	{																							\
		return eA = static_cast< X >( static_cast< Type >( eA ) & static_cast< Type >( eB ) );	\
	}																							\
	inline																						\
	X&	operator^=( X& eA, X const eB )															\
	{																							\
		return eA = static_cast< X >( static_cast< Type >( eA ) ^ static_cast< Type >( eB ) );	\
	}																							\
	inline																						\
	X	operator<<( X& eA, UInt32 const uShift )												\
	{																							\
		return static_cast< X >( static_cast< Type >( eA ) << uShift );							\
	}																							\
	inline																						\
	X&	operator<<=( X& eA, UInt32 const uShift )												\
	{																							\
		return eA = static_cast< X >( static_cast< Type >( eA ) << uShift );					\
	}																							\
	inline																						\
	Bool	IsSetted( X const eA )																\
	{																							\
		return static_cast< Type >( eA ) != static_cast< Type >( 0 );							\
	}																							\
	inline																						\
	Bool	Is##X##BitSetted( X const eFull, X const eBit )										\
	{																							\
		return IsSetted( eFull & eBit );														\
	}																							

#define eMVEnumifyMixed( X )	EMV_ENUMIFY_MIXED( X, std::underlying_type< X >::type )

#define	EMV_ENUMIFY_UNIQUE( X, Type )																	\
	inline																								\
	inline																								\
	Bool	operator&( X const eA, X const eB )															\
	{																									\
		return ( static_cast< Type >( eA ) & static_cast< Type >( eB ) ) != static_cast< Type >( 0 );	\
	}																									

#define eMVEnableToUInt32( EnumType )								\
	constexpr inline UInt32 operator+( EnumType const e ) noexcept	\
	{																\
		return static_cast< UInt32 >( e );							\
	}																

// #define eMVEnumifyMixed(enumType) \
//     inline enumType operator|( enumType a, enumType b ) \
//     { \
//         return static_cast< enumType >( static_cast< std::underlying_type< enumType >::type >( a ) | static_cast< std::underlying_type< enumType >::type >( b ) ); \
//     } \
//     inline enumType operator&( enumType a, enumType b ) \
//     { \
//         return static_cast< enumType >( static_cast< std::underlying_type< enumType >::type >( a ) & static_cast< std::underlying_type< enumType >::type >( b ) ); \
//     } \
//     inline enumType operator^( enumType a, enumType b ) \
//     { \
//         return static_cast< enumType >( static_cast< std::underlying_type< enumType >::type >( a ) ^ static_cast< std::underlying_type< enumType >::type >( b ) ); \
//     } \
//     inline enumType operator~( enumType a ) \
//     { \
//         return static_cast< enumType >( ~static_cast< std::underlying_type< enumType >::type >( a ) ); \
//     } \
//     inline enumType& operator&=( enumType& a, enumType b ) \
//     { \
//         a = a & b; \
//         return a; \
//     } \
//     inline enumType& operator|=( enumType& a, enumType b ) \
//     { \
//         a = a | b; \
//         return a; \
//     } \
//     inline enumType& operator^=( enumType& a, enumType b ) \
//     { \
//         a = a ^ b; \
//         return a; \
//     } \
//     inline enumType operator<<( enumType a, UInt32 shift ) \
//     { \
//         return static_cast< enumType >( static_cast< std::underlying_type< enumType >::type >( a ) << shift ); \
//     } \
//     inline enumType operator<<=( enumType& a, UInt32 shift ) \
//     { \
//         a = a << shift; \
//         return a; \
//     } \
//     inline Bool IsSet( enumType a ) \
//     { \
//         return (static_cast<UInt32>(a) != 0); \
//     }

//	inline																					\
//	operator Type( X const eX ) const														\
//	{																						\
//		return static_cast< Type >( eX );													\
//	}																						

#define	EMV_ALIGNOF( X )	__declspec( align( ( X ) ) )

#define	EMV_UNUSED( X )		( ( void )X );

#define	__EMV_ASCII__	1
//#define	__EMV_UNICODE__	1
//#define	__EMV_UTF8__	1
//#define	__EMV_UTF16__	1
//#define	__EMV_UTF32__	1

typedef	CharASCII		Char;

#define	eMVASCIIStr( x )	x
#define	eMVUTF8Str( x )		u8 ## x
#define	eMVUTF16Str( x )	u ## x
#define	eMVUTF32Str( x )	U ## x
#define	eMVWideStr( x )		L ## x

typedef	UInt32					ClassID; // Must be 32 bits to have ObjectinstanceID working
typedef	UInt32					ObjectID;
typedef	UInt64					ObjectInstanceID; // { ObjectID, 0x00000000 } // ObjectID followed by Index
#define	eMVBadClassID			( static_cast< ClassID          >( 0xFFFFFFFFul ) )
#define	eMVBadObjectID			( static_cast< ObjectID         >( 0xFFFFFFFFul ) )
#define	eMVBadObjectInstanceID	( static_cast< ObjectInstanceID >( 0xFFFFFFFFFFFFFFFFull ) )

#define	eMV_kB( size )	( UInt64( size )*1000ull )
#define	eMV_PB( size )	( eMV_TB( size )*1000ull )
#define	eMV_MB( size )	( eMV_kB( size )*1000ull )
#define	eMV_GB( size )	( eMV_MB( size )*1000ull )
#define	eMV_TB( size )	( eMV_GB( size )*1000ull )

#define	eMV_kiB( size )	(  UInt64( size )*1024ull )
#define	eMV_GiB( size )	( eMV_MiB( size )*1024ull )
#define	eMV_MiB( size )	( eMV_kiB( size )*1024ull )
#define	eMV_TiB( size )	( eMV_GiB( size )*1024ull )
#define	eMV_PiB( size )	( eMV_TiB( size )*1024ull )

#ifdef FMT_FORMAT_H_
#include <fmt/format.h>

template <>
class fmt::formatter< eMV::f16 > : public fmt::formatter< float >
{
public:
	//constexpr auto parse( format_parse_context& ctx )
	//{
	//	auto i = ctx.begin(), end = ctx.end();
	//	
	//	if ( i != end && *i != '}' )
	//	{
	//		throw format_error( "invalid format" );
	//	}
	//	return i;
	//}

	template < typename FmtContext >
	/*constexpr*/ auto format( eMV::f16 const f, FmtContext& ctx ) const
	{
		float const x = eMV::Internal::f16_to_f32( f._ );
		return fmt::format_to( ctx.out(), "{}", x );
	}
};

template <>
class fmt::formatter< eMV::bf16 > : public fmt::formatter< float >
{
public:
	//constexpr auto parse( format_parse_context& ctx )
	//{
	//	auto i = ctx.begin(), end = ctx.end();
	//
	//	if ( i != end && *i != '}' )
	//	{
	//		throw format_error( "invalid format" );
	//	}
	//	return i;
	//}

	template < typename FmtContext >
	/*constexpr*/ auto format( eMV::bf16 const f, FmtContext& ctx ) const
	{
		float const x = eMV::Internal::bf16_to_f32( f._ );
		return fmt::format_to( ctx.out(), "{}", x );
	}
};

namespace std
{
	template <>
	class numeric_limits< eMV::f16 > : public _Num_int_base
	{
	public:
		_NODISCARD static const eMV::f16( min )( ) noexcept
		{
			return { 0x400 };
		}

		_NODISCARD static const eMV::f16( max )( ) noexcept
		{
			eMV::f16 _;
			_.FromBits( 0x7bff );
			return _;
		}

		_NODISCARD static const eMV::f16 lowest() noexcept
		{
			eMV::f16 _;
			_.FromBits( 0xfbff );
			return _;
		}

		_NODISCARD static const eMV::f16 epsilon() noexcept
		{
			eMV::f16 _;
			_.FromBits( 0x0800 );
			return _;
		}

		_NODISCARD static const eMV::f16 round_error() noexcept
		{
			eMV::f16 _( 0.5 );
			return _;
		}

		_NODISCARD static const eMV::f16 denorm_min() noexcept
		{
			eMV::f16 _;
			_.FromBits( 0x1 );
			return _;
		}

		_NODISCARD static const eMV::f16 infinity() noexcept
		{
			eMV::f16 _;
			_.FromBits( 0x7c00 );
			return _;
		}

		_NODISCARD static const eMV::f16 quiet_NaN() noexcept
		{
			eMV::f16 _;
			_.FromBits( 0x7e00 );
			return _;
		}

		_NODISCARD static const eMV::f16 signaling_NaN() noexcept
		{
			eMV::f16 _;
			_.FromBits( 0x7d00 );
			return _;
		}

		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		static constexpr bool has_infinity = true;
		static constexpr bool has_quiet_NaN = true;
		static constexpr bool has_signaling_NaN = true;
		//static constexpr float_denorm_style has_denorm = denorm_present;
		//static constexpr bool has_denorm_loss = false;
		static constexpr std::float_round_style round_style = std::round_to_nearest;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = false;
		static constexpr bool is_modulo = false;
		static constexpr int digits = 11;
		static constexpr int digits10 = 3;      // according to http://half.sourceforge.net/structstd_1_1numeric__limits_3_01half__float_1_1half_01_4.html
		static constexpr int max_digits10 = 5;  // according to http://half.sourceforge.net/structstd_1_1numeric__limits_3_01half__float_1_1half_01_4.html
		static constexpr int radix = 2;
		static constexpr int min_exponent = -13;
		static constexpr int min_exponent10 = -4;
		static constexpr int max_exponent = 16;
		static constexpr int max_exponent10 = 4;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = false;
	};

	template <>
	class numeric_limits< eMV::bf16 > : public _Num_int_base
	{
	public:
		_NODISCARD static const eMV::bf16( min )( ) noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x0080 );
			return _;
		}

		_NODISCARD static const eMV::bf16( max )( ) noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x7f7f );
			return _;
		}

		_NODISCARD static const eMV::bf16 lowest() noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0xff7f );
			return _;
		}

		_NODISCARD static const eMV::bf16 epsilon() noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x3c00 );
			return _;
		}

		_NODISCARD static const eMV::bf16 round_error() noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x3f00 );
			return _;
		}

		_NODISCARD static const eMV::bf16 denorm_min() noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x0001 );
			return _;
		}

		_NODISCARD static const eMV::bf16 infinity() noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x7f80 );
			return _;
		}

		_NODISCARD static const eMV::bf16 quiet_NaN() noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x7fc0 );
			return _;
		}

		_NODISCARD static const eMV::bf16 signaling_NaN() noexcept
		{
			eMV::bf16 _;
			_.FromBits( 0x7f81 );
			return _;
		}

		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		static constexpr bool has_infinity = true;
		static constexpr bool has_quiet_NaN = true;
		static constexpr bool has_signaling_NaN = true;
		//static constexpr float_denorm_style has_denorm = std::denorm_absent;
		//static constexpr bool has_denorm_loss = false;
		static constexpr std::float_round_style round_style = numeric_limits<float>::round_style;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = 8;
		static constexpr int digits10 = 2;
		static constexpr int max_digits10 = 4;
		static constexpr int radix = 2;
		static constexpr int min_exponent = numeric_limits<float>::min_exponent;
		static constexpr int min_exponent10 = numeric_limits<float>::min_exponent10;
		static constexpr int max_exponent = numeric_limits<float>::max_exponent;
		static constexpr int max_exponent10 = numeric_limits<float>::max_exponent10;
		static constexpr bool traps = numeric_limits<float>::traps;
		static constexpr bool tinyness_before = numeric_limits<float>::tinyness_before;
	};
}
#endif
