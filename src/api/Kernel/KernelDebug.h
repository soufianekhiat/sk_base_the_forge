#pragma once

#ifdef EMV_COMPILER_VCPP
#	define EMV_DISABLE_WARNING_START	__pragma( warning( push ) )
#	define EMV_DISABLE_WARNING( X )		__pragma( warning( disable : X ) )
#	define EMV_DISABLE_WARNING_END		__pragma( warning( pop ) )
#elif defined(EMV_COMPILER_CLANG)
#	define EMV_DISABLE_WARNING_START	__pragma( clang diagnostic push )
#	define EMV_DISABLE_WARNING( X )		__pragma( clang diagnostic ignored X )
#	define EMV_DISABLE_WARNING_END		__pragma( clang diagnostic pop )
#else
#	define EMV_DISABLE_WARNING_START
#	define EMV_DISABLE_WARNING( X )
#	define EMV_DISABLE_WARNING_END
#endif

#ifdef EMV_COMPILER_VCPP
#	define EMV_TODO( sMessage )												\
	__pragma( warning( push ) )												\
	__pragma( warning( disable : 4081 ) )									\
	__pragma( message( __FILE__ "( " __LINE__ " ) : TODO: " sMessage ) )	\
	__pragma( warning( pop ) )												
#else
#	define EMV_TODO( sMessage )
#endif

#if defined EMV_KERNEL_DISABLE_BREAK
#	define EMV_BREAK_CPU()
#elif defined __EMV_LINUX__
#	define EMV_BREAK_CPU()	( *( ( char* )0 ) = 0 )
//#include <signal.h>
//#	define EMV_BREAK_CPU()	raise(SIGTRAP) // SIGBREAK?
#elif defined __EMV_WIN64__
#	define EMV_BREAK_CPU()	__debugbreak()
#elif defined __EMV_WIN32__
#	define EMV_BREAK_CPU()	__asm { int 3 }
#else
#	define EMV_BREAK_CPU()	( *( ( char* )0 ) = 0 )
#endif
