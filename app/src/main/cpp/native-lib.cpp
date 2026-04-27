#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define TAG "NATIVE_LOG"
#define LOG_I(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

// 1) Message de bienvenue via JNI
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_getWelcomeMessage(
        JNIEnv* env,
        jobject /* this */) {
    LOG_I("Native function getWelcomeMessage executed");
    return env->NewStringUTF("Greetings from Native C++!");
}

// 2) Calcul de factorielle avec contrôle de dépassement
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_computeFactorial(
        JNIEnv* env,
        jobject /* this */,
        jint val) {

    if (val < 0) {
        LOG_E("Input negative for factorial: %d", val);
        return -101;
    }

    long long result = 1;
    for (int i = 2; i <= val; i++) {
        result *= i;
        if (result > INT_MAX) {
            LOG_E("Overflow occurred for value: %d", val);
            return -102;
        }
    }

    LOG_I("Factorial of %d computed: %lld", val, result);
    return static_cast<jint>(result);
}

// 3) Renversement de chaîne Java
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_invertText(
        JNIEnv* env,
        jobject /* this */,
        jstring input) {

    if (input == nullptr) {
        LOG_E("Received null string input");
        return env->NewStringUTF("Error: Null Data");
    }

    const char* nativeChars = env->GetStringUTFChars(input, nullptr);
    if (nativeChars == nullptr) {
        return nullptr;
    }

    std::string str(nativeChars);
    env->ReleaseStringUTFChars(input, nativeChars);

    std::reverse(str.begin(), str.end());

    LOG_I("String reversed successfully");
    return env->NewStringUTF(str.c_str());
}

// 4) Somme des entiers d'un tableau
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_calculateArraySum(
        JNIEnv* env,
        jobject /* this */,
        jintArray values) {

    if (values == nullptr) {
        LOG_E("Null array pointer");
        return -1;
    }

    jsize count = env->GetArrayLength(values);
    jint* elements = env->GetIntArrayElements(values, nullptr);

    if (elements == nullptr) {
        LOG_E("Could not access array elements");
        return -2;
    }

    long long accumulator = 0;
    for (jsize i = 0; i < count; i++) {
        accumulator += elements[i];
    }

    env->ReleaseIntArrayElements(values, elements, JNI_ABORT);

    if (accumulator > INT_MAX || accumulator < INT_MIN) {
        LOG_E("Arithmetic overflow in array sum");
        return -3;
    }

    LOG_I("Summation complete: %lld", accumulator);
    return static_cast<jint>(accumulator);
}
