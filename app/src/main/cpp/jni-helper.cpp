#include "jni.h"
#include <cstdint>
#include <string>
#include <thread>
#include <config.h>
#include <service.h>
using namespace std;

static std::list<thread*> listOfThreads;
static std::list<Service*> listOfServices;
static std::list<Config*> listOfConfigs;

static void startTrojan(const string &config)
{
    Config *trojanConfig;
    Service *trojanService;
    trojanConfig = new Config();
    trojanConfig->load(config);
    listOfConfigs.push_back(trojanConfig);
    trojanService = new Service(*trojanConfig);
    trojanService->run();
    listOfServices.push_back(trojanService);
}


extern "C" {
    JNIEXPORT void JNICALL Java_io_github_trojan_1gfw_igniter_JNIHelper_trojan(JNIEnv *env, jclass, jstring config) {
        thread *trojanThread;
        const char *s = env->GetStringUTFChars(config, 0);
        string a(s);
        env->ReleaseStringUTFChars(config, s);
        trojanThread = new thread(startTrojan, a);
        listOfThreads.push_back(trojanThread);
    }

    JNIEXPORT void JNICALL Java_io_github_trojan_1gfw_igniter_JNIHelper_stop(JNIEnv *env, jclass) {
        for (auto const& i : listOfServices) {
            i -> stop();
            delete i;
        }
        listOfServices.clear();
        for (auto const& i : listOfThreads) {
            i -> join();
            delete i;
        }
        listOfThreads.clear();
        for (auto const& i : listOfConfigs) {
            delete i;
        }
        listOfConfigs.clear();
    }
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    return JNI_VERSION_1_6;
}
