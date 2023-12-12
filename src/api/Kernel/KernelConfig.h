#pragma once

//#define USE_QUIET_NAN
//#define USE_SIGNAL_NAN

#define	EMV_VECTORIAL_ALIGNMENT			EMV_VECTORIAL_ALIGNMENT_SSE

#define	EMV_VECTORIAL_ALIGNMENT_SSE		16
#define	EMV_VECTORIAL_ALIGNMENT_AVX		32
#define	EMV_VECTORIAL_ALIGNMENT_AVX512	64

#define	EMV_GPU_ALIGNMENT				16

#define	eMVForceInline	__forceinline

#ifdef __EMV_DEBUG__
#	define	EMV_DEBUG_ONLY( X )		X
#	define	EMV_RELEASE_ONLY( X )	
#else
#	define	EMV_DEBUG_ONLY( X )
#	define	EMV_RELEASE_ONLY( X )	X
#endif

#ifdef	__EMV_DEV_VERSION__
#	define	EMV_DEV_ONLY( X )	X
#	define	EMV_PROD_ONLY( X )	
#elif	defined( __EMV_PROD_VERSION__ )
#	define	EMV_DEV_ONLY( X )	
#	define	EMV_PROD_ONLY( X )	X
#endif

#if defined( __clang__ ) || defined( __llvm__ )
#	define	EMV_COMPILER_CLANG	1
#elif defined ( __GNUC__ ) || defined( __MINGW64__ )
#	define	EMV_COMPILER_GPP	1
#elif defined( _MSC_BUILD ) || defined( _MSC_VER )
#	define	EMV_COMPILER_VCPP	1
#elif defined( __INTEL_COMPILER )
#	define	EMV_COMPILER_ICPP	1
#else
#	error Compiler Unknown
#endif

#if EMV_COMPILER_VCPP == 1
// defined( _MSC_BUILD ) || defined( __INTEL_COMPILER )
//#	define	_CRT_SECURE_NO_WARNINGS
#	if defined( D_WIN32 ) || defined( _WIN32 ) || defined( _M_IX86 ) || defined( _M_IX86_FP )
#		undef __EMV_WIN64__
#		ifndef __EMV_WIN32__
#			define __EMV_WIN32__	1
#			define __EMV_X86__		1
#		endif
#		ifndef __EMV_WIN__
#			define __EMV_WIN__		1
#		endif
#	else
#		error only for Windows
#	endif

#	if defined( D_WIN64 ) || defined( _WIN64 ) || defined( _M_X64 ) || defined( _M_AMD64 ) || defined( __x86_64 ) || defined( _M_IA64 )
#		undef __EMV_WIN32__
#		undef __EMV_X86__
#		ifndef __EMV_WIN64__
#			define __EMV_WIN64__	1
#			define __EMV_X64__		1
#		endif
#		ifndef __EMV_WIN__
#			define __EMV_WIN__		1
#		endif
#	endif
#elif EMV_COMPILER_GPP == 1
//defined ( __GNUC__ ) || defined( __MINGW64__ )
#	if defined( i386 ) || defined( __i386 ) || defined( __i386__ ) || defined( _X86_ )
#		undef __EMV_WIN64__
#		ifndef __EMV_WIN32__
#			define __EMV_WIN32__	1
#			define __EMV_X86__		1
#		endif
#		ifndef __EMV_WIN__
#			define __EMV_WIN__		1
#		endif
#	endif

#	if defined( __x86_64 ) || defined( __x86_64__ ) || defined( __amd64 ) || defined( __amd64__ ) || defined( _M_AMD64 ) || defined( _M_X64 )
#		undef __EMV_WIN32__
#		undef __EMV_X86__
#		ifndef __EMV_WIN64__
#			define __EMV_WIN64__	1
#			define __EMV_X64__		1
#		endif
#		ifndef __EMV_WIN__
#			define __EMV_WIN__		1
#		endif
#	endif
#elif EMV_COMPILER_CLANG == 1
#	if defined( i386 ) || defined( __i386 ) || defined( __i386__ ) || defined( _M_IX86 ) || defined( _X86_ )
#		undef __EMV_WIN64__
#		ifndef __EMV_WIN32__
#			define __EMV_WIN32__	1
#			define __EMV_X86__		1
#		endif
#		ifndef __EMV_WIN__
#			define __EMV_WIN__		1
#		endif
#	endif

#	if defined( __x86_64 ) || defined( __x86_64__ ) || defined( __amd64 ) || defined( __amd64__ ) || defined( _M_AMD64 ) || defined( _M_X64 )
#		undef __EMV_WIN32__
#		undef __EMV_X86__
#		ifndef __EMV_WIN64__
#			define __EMV_WIN64__	1
#			define __EMV_X64__		1
#		endif
#		ifndef __EMV_WIN__
#			define __EMV_WIN__		1
#		endif
#	endif
#else
#	error Not yet test in another compiler use VC++2019-19.8.2
#endif

#define eMVPrivateCopy( ClassName )					\
	private:										\
		ClassName( ClassName const& );				\
		ClassName& operator=( ClassName const& );	

#define eMVToInt32( X )		static_cast< eMV::Int32 >( X )
//#define EMV_STATIC_ASSERT	static_assert

//#define eMVDLLExport	__declspec( dllexport )
//#define eMVDLLImport	__declspec( dllimport )

#define	eMVCRC64Init	0x95AC9329AC4BC9B5ull
