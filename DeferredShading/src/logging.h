#pragma once

#define NOMINMAX

#ifdef ANDROID

#include <android/log.h>

namespace base{
namespace type{
typedef unsigned short EnumType;
}
}

namespace el{
	enum class Level : base::type::EnumType;// : unsigned short;
}

int elToAndroidLog(el::Level priority);

#define ELPP_CUSTOM_COUT_LINE(logline) ( __android_log_print( elToAndroidLog( m_data->logMessage()->level() ), m_data->logMessage()->logger()->id().c_str(), logline.c_str() ) )

#endif //ANDROID

#include <easylogging++.h>
