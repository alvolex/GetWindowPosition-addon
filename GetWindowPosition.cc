#include <napi.h>
#include <windows.h>

Napi::Value GetWindowPositionByName(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::String name = info[0].As<Napi::String>();

    const auto hWnd = FindWindowA(NULL, name.Utf8Value().c_str());
    if (hWnd == NULL) {
        return env.Null();
    }

    RECT* lpRect = new RECT;
    GetWindowRect(hWnd, lpRect);

    Napi::Object result = Napi::Object::New(env);
    result.Set("left", Napi::Number::New(env, lpRect->left));
    result.Set("top", Napi::Number::New(env, lpRect->top));
    result.Set("right", Napi::Number::New(env, lpRect->right));
    result.Set("bottom", Napi::Number::New(env, lpRect->bottom));

    delete lpRect;

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("getWindowPositionByName", Napi::Function::New(env, GetWindowPositionByName));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
