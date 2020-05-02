#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_android_myapplication_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_android_myapplication_jniTexasHoldem_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_android_myapplication_jniTexasHoldem_anotherCheckJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement anotherCheckJNI()
}