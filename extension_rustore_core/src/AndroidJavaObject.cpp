#if defined(DM_PLATFORM_ANDROID)
#include "AndroidJavaObject.h"

using namespace RuStoreSDK;

AndroidJavaObject::AndroidJavaObject()
{
	cls = nullptr;
	obj = nullptr;
}

void AndroidJavaObject::Free(JNIEnv* env)
{
	if (cls)
	{
		env->DeleteLocalRef(cls);
		cls = nullptr;
	}
	if (obj)
	{
		env->DeleteLocalRef(obj);
		obj = nullptr;
	}
}
#endif
