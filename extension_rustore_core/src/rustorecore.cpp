#define EXTENSION_NAME RuStoreCore
#define LIB_NAME "RuStoreCore"
#define MODULE_NAME "rustorecore"

#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID)

#include "RuStoreChannelListener.h"
#include "ChannelCallbackManager.h"
#include "AndroidJavaObject.h"

using namespace RuStoreSDK;

static void GetJavaCoreInstance(JNIEnv* env, AndroidJavaObject* instance)
{
    jclass cls = dmAndroid::LoadClass(env, "ru.rustore.defold.core.RuStoreCore");
    jfieldID instanceField = env->GetStaticFieldID(cls, "INSTANCE", "Lru/rustore/defold/core/RuStoreCore;");
    jobject obj = env->GetStaticObjectField(cls, instanceField);

    instance->cls = cls;
    instance->obj = obj;
}

static void InitDefoldPlayer()
{
    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    jclass jplayerCls = dmAndroid::LoadClass(env, "ru.rustore.defold.core.wrappers.DefoldPlayerWrapper");
    jobject jplayerObj = env->NewObject(jplayerCls, env->GetMethodID(jplayerCls, "<init>", "()V"));

    jclass jproviderCls = dmAndroid::LoadClass(env, "ru.rustore.defold.core.PlayerProvider");
    jfieldID instanceField = env->GetStaticFieldID(jproviderCls, "INSTANCE", "Lru/rustore/defold/core/PlayerProvider;");
    jobject playerProviderInstance = env->GetStaticObjectField(jproviderCls, instanceField);

    jmethodID method = env->GetMethodID(jproviderCls, "setExternalProvider", "(Lru/rustore/defold/core/IPlayerProvider;)V");
    env->CallVoidMethod(playerProviderInstance, method, jplayerObj);
}

static void InitRuStoreCallbacks()
{
    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    jobject wrapper = RuStoreChannelListener::Instance()->GetJWrapper();

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "setChannelListener", "(Lru/rustore/defold/core/callbacks/IRuStoreChannelListener;)V");
    env->CallVoidMethod(instance.obj, method, wrapper);
    instance.Free(env);
}

static int Connect(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    const char* channel = (char*)luaL_checkstring(L, 1);
    dmScript::LuaCallbackInfo* callback = dmScript::CreateCallback(L, 2);

    auto channelCallbackItem = std::make_shared<ChannelCallbackItem>(channel, callback);
    ChannelCallbackManager::Instance()->AddChannelCallback(channelCallbackItem);

    return 0;
}

static int ShowToast(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* msg = (char*)luaL_checkstring(L, 1);
    jstring jmsg = env->NewStringUTF(msg);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "showToast", "(Landroid/app/Activity;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity(), jmsg);
    instance.Free(env);

    env->DeleteLocalRef(jmsg);

    return 0;
}

static int LogVerbose(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* tag = (char*)luaL_checkstring(L, 1);
    const char* msg = (char*)luaL_checkstring(L, 2);

    jstring jtag = env->NewStringUTF(tag);
    jstring jmsg = env->NewStringUTF(msg);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "logVerbose", "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jtag, jmsg);
    instance.Free(env);

    env->DeleteLocalRef(jtag);
    env->DeleteLocalRef(jmsg);

    return 0;
}

static int LogDebug(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* tag = (char*)luaL_checkstring(L, 1);
    const char* msg = (char*)luaL_checkstring(L, 2);

    jstring jtag = env->NewStringUTF(tag);
    jstring jmsg = env->NewStringUTF(msg);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "logDebug", "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jtag, jmsg);
    instance.Free(env);

    env->DeleteLocalRef(jtag);
    env->DeleteLocalRef(jmsg);

    return 0;
}

static int LogInfo(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* tag = (char*)luaL_checkstring(L, 1);
    const char* msg = (char*)luaL_checkstring(L, 2);

    jstring jtag = env->NewStringUTF(tag);
    jstring jmsg = env->NewStringUTF(msg);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "logInfo", "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jtag, jmsg);
    instance.Free(env);

    env->DeleteLocalRef(jtag);
    env->DeleteLocalRef(jmsg);

    return 0;
}

static int LogWarning(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* tag = (char*)luaL_checkstring(L, 1);
    const char* msg = (char*)luaL_checkstring(L, 2);

    jstring jtag = env->NewStringUTF(tag);
    jstring jmsg = env->NewStringUTF(msg);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "logWarning", "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jtag, jmsg);
    instance.Free(env);

    env->DeleteLocalRef(jtag);
    env->DeleteLocalRef(jmsg);

    return 0;
}

static int LogError(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* tag = (char*)luaL_checkstring(L, 1);
    const char* msg = (char*)luaL_checkstring(L, 2);

    jstring jtag = env->NewStringUTF(tag);
    jstring jmsg = env->NewStringUTF(msg);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "logError", "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jtag, jmsg);
    instance.Free(env);

    env->DeleteLocalRef(jtag);
    env->DeleteLocalRef(jmsg);

    return 0;
}

static int CopyToClipboard(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* text = (char*)luaL_checkstring(L, 1);
    jstring jtext = env->NewStringUTF(text);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "copyToClipboard", "(Landroid/app/Activity;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity(), jtext);
    instance.Free(env);

    env->DeleteLocalRef(jtext);

    return 0;
}

static int GetFromClipboard(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getFromClipboard", "(Landroid/app/Activity;)Ljava/lang/String;");
    jstring jtext = (jstring)env->CallObjectMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity());
    instance.Free(env);

    const char* ctext = env->GetStringUTFChars(jtext, nullptr);
    lua_pushstring(L, ctext);
    env->ReleaseStringUTFChars(jtext, ctext);

    return 1;
}

static int GetStringResources(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* name = (char*)luaL_checkstring(L, 1);
    jstring jname = env->NewStringUTF(name);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getStringResources", "(Landroid/app/Activity;Ljava/lang/String;)Ljava/lang/String;");
    jstring jtext = (jstring)env->CallObjectMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity(), jname);
    instance.Free(env);

    const char* ctext = env->GetStringUTFChars(jtext, nullptr);
    lua_pushstring(L, ctext);
    env->ReleaseStringUTFChars(jtext, ctext);

    env->DeleteLocalRef(jname);

    return 1;
}

static int GetStringSharedPreferences(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* storageName = (char*)luaL_checkstring(L, 1);
    jstring jstorageName = env->NewStringUTF(storageName);

    const char* key = (char*)luaL_checkstring(L, 2);
    jstring jkey = env->NewStringUTF(key);

    const char* defaultValue = (char*)luaL_checkstring(L, 3);
    jstring jdefaultValue = env->NewStringUTF(defaultValue);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getStringSharedPreferences", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");
    jstring jtext = (jstring)env->CallObjectMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity(), jstorageName, jkey, jdefaultValue);
    instance.Free(env);

    const char* ctext = env->GetStringUTFChars(jtext, nullptr);
    lua_pushstring(L, ctext);
    env->ReleaseStringUTFChars(jtext, ctext);

    env->DeleteLocalRef(jstorageName);
    env->DeleteLocalRef(jkey);
    env->DeleteLocalRef(jdefaultValue);

    return 1;
}

static int SetStringSharedPreferences(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* storageName = (char*)luaL_checkstring(L, 1);
    jstring jstorageName = env->NewStringUTF(storageName);

    const char* key = (char*)luaL_checkstring(L, 2);
    jstring jkey = env->NewStringUTF(key);

    const char* defaultValue = (char*)luaL_checkstring(L, 3);
    jstring jdefaultValue = env->NewStringUTF(defaultValue);

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "setStringSharedPreferences", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity(), jstorageName, jkey, jdefaultValue);
    instance.Free(env);

    env->DeleteLocalRef(jstorageName);
    env->DeleteLocalRef(jkey);
    env->DeleteLocalRef(jdefaultValue);

    return 0;
}

static int GetIntSharedPreferences(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* storageName = (char*)luaL_checkstring(L, 1);
    jstring jstorageName = env->NewStringUTF(storageName);

    const char* key = (char*)luaL_checkstring(L, 2);
    jstring jkey = env->NewStringUTF(key);

    jint jdefaultValue = static_cast<jint>(luaL_checkint(L, 3));

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getIntSharedPreferences", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;I)I");
    int value = (int)env->CallIntMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity(), jstorageName, jkey, jdefaultValue);
    lua_pushinteger(L, value);
    instance.Free(env);

    env->DeleteLocalRef(jstorageName);
    env->DeleteLocalRef(jkey);

    return 1;
}

static int SetIntSharedPreferences(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* storageName = (char*)luaL_checkstring(L, 1);
    jstring jstorageName = env->NewStringUTF(storageName);

    const char* key = (char*)luaL_checkstring(L, 2);
    jstring jkey = env->NewStringUTF(key);

    jint jvalue = static_cast<jint>(luaL_checkint(L, 3));

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "setIntSharedPreferences", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;I)V");
    env->CallVoidMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity(), jstorageName, jkey, jvalue);
    instance.Free(env);

    env->DeleteLocalRef(jstorageName);
    env->DeleteLocalRef(jkey);

    return 0;
}

static int IsRuStoreInstalled(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 1);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "isRuStoreInstalled", "(Landroid/app/Activity;)Z");
    jboolean result = env->CallBooleanMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity());
    lua_pushboolean(L, result ? 1 : 0);
    instance.Free(env);

    return 1;
}

static int OpenRuStoreDownloadInstruction(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "openRuStoreDownloadInstruction", "(Landroid/app/Activity;)V");
    env->CallVoidMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity());
    instance.Free(env);

    return 0;
}

static int OpenRuStore(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "openRuStore", "(Landroid/app/Activity;)V");
    env->CallVoidMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity());
    instance.Free(env);

    return 0;
}

static int OpenRuStoreAuthorization(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaCoreInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "openRuStoreAuthorization", "(Landroid/app/Activity;)V");
    env->CallVoidMethod(instance.obj, method, dmGraphics::GetNativeAndroidActivity());
    instance.Free(env);

    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"connect", Connect},
    {"log_verbose", LogVerbose},
    {"log_debug", LogDebug},
    {"log_info", LogInfo},
    {"log_warning", LogWarning},
    {"log_error", LogError},
    {"show_toast", ShowToast},
    {"copy_to_clipboard", CopyToClipboard},
    {"get_from_clipboard", GetFromClipboard},
    {"get_string_resources", GetStringResources},
    {"get_string_shared_preferences", GetStringSharedPreferences},
    {"set_string_shared_preferences", SetStringSharedPreferences},
    {"get_int_shared_preferences", GetIntSharedPreferences},
    {"set_int_shared_preferences", SetIntSharedPreferences},
    {"is_rustore_installed", IsRuStoreInstalled},
    {"open_rustore_download_instruction", OpenRuStoreDownloadInstruction},
    {"open_rustore", OpenRuStore},
    {"open_rustore_authorization", OpenRuStoreAuthorization},
    {0, 0}
};

#else

static const luaL_reg Module_methods[] =
{
    {0, 0}
};

#endif

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

#if defined(DM_PLATFORM_ANDROID)

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    InitDefoldPlayer();
    InitRuStoreCallbacks();

    return dmExtension::RESULT_OK;
}

#else

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

#endif

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

#if defined(DM_PLATFORM_ANDROID)

static void ProcessOneParam(QueueCallbackItem* item)
{
    const char* channel = item->channel.c_str();
    const char* value = item->value.c_str();

    auto _callbacks = ChannelCallbackManager::Instance()->FindLuaCallbacksByChannel(channel);
    for (const auto& callback : _callbacks)
    {
        lua_State* L = dmScript::GetCallbackLuaContext(callback);

        DM_LUA_STACK_CHECK(L, 0);

        if (!dmScript::SetupCallback(callback)) continue;

        lua_pushstring(L, channel);
        lua_pushstring(L, value);

        dmScript::PCall(L, 3, 0); // self + # user arguments

        dmScript::TeardownCallback(callback);
    }
}

static void ProcessTwoParam(QueueCallbackItemTwoParams* item)
{
    const char* channel = item->channel.c_str();
    const char* value0 = item->value0.c_str();
    const char* value1 = item->value1.c_str();

    auto _callbacks = ChannelCallbackManager::Instance()->FindLuaCallbacksByChannel(channel);
    for (const auto& callback : _callbacks)
    {
        lua_State* L = dmScript::GetCallbackLuaContext(callback);

        DM_LUA_STACK_CHECK(L, 0);

        if (!dmScript::SetupCallback(callback)) continue;

        lua_pushstring(L, channel);
        lua_pushstring(L, value0);
        lua_pushstring(L, value1);

        dmScript::PCall(L, 4, 0); // self + # user arguments

        dmScript::TeardownCallback(callback);
    }
}

static dmExtension::Result UpdateExtension(dmExtension::Params* params)
{
    auto queue = QueueCallbackManager::Instance()->GetExexuteQueueCallback();

    while (!queue.empty())
    {
        auto item = queue.front();
        queue.pop();

        if (auto oneParam = dynamic_cast<QueueCallbackItem*>(item.get())) {
            ProcessOneParam(oneParam);
        }
        else if (auto twoParams = dynamic_cast<QueueCallbackItemTwoParams*>(item.get())) {
            ProcessTwoParam(twoParams);
        }
    }

    return dmExtension::RESULT_OK;
}

#else

static dmExtension::Result UpdateExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

#endif

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeExtension, AppFinalizeExtension, InitializeExtension, UpdateExtension, nullptr, nullptr)

#if defined(DM_PLATFORM_ANDROID)
extern "C"
{
    JNIEXPORT jobject JNICALL Java_ru_rustore_defold_core_wrappers_DefoldPlayerWrapper_NativeOnActivityRequest(JNIEnv* env, jobject obj)
    {
        return dmGraphics::GetNativeAndroidActivity();
    }
}
#endif
