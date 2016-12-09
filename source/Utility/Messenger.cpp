#include <Utility/Messenger.hpp>


#include <Core/Settings.hpp>
#include <Utility/FileHandler.hpp>

#ifdef __ANDROID__
#include <android/log.h>
#include <android_native_app_glue.h>

#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

#endif

namespace jej
{
    std::vector<std::pair<std::string, Messenger::MessageType>> Messenger::m_messages = {};

    ////////////////////////////////////////////////////////////

    void Messenger::PrintMessages()
    {
        auto& mm = m_messages;

        if (mm.empty())
            return;

#ifdef _WIN32 //Windows messages

        HANDLE debugHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        for (size_t i = 0u; i < mm.size(); ++i)
        {
            if (mm[i].second == MessageType::Error && JEJ_DEBUG_LEVEL > 0)
            {
                SetConsoleTextAttribute(debugHandle, 4u);
                std::cout << mm[i].first << std::endl;
                SetConsoleTextAttribute(debugHandle, 7u);
            }

            else if (mm[i].second == MessageType::Warning && JEJ_DEBUG_LEVEL > 1)
            {
                SetConsoleTextAttribute(debugHandle, 6u);
                std::cout << mm[i].first << std::endl;
                SetConsoleTextAttribute(debugHandle, 7u);
            }

            else if (mm[i].second == MessageType::Debug && JEJ_DEBUG_LEVEL > 2)
            {
                SetConsoleTextAttribute(debugHandle, 10u);
                std::cout << mm[i].first << std::endl;
                SetConsoleTextAttribute(debugHandle, 7u);
            }

            else if (mm[i].second == MessageType::Info && JEJ_DEBUG_LEVEL > 3)
            {
                SetConsoleTextAttribute(debugHandle, 8u);
                std::cout << mm[i].first << std::endl;
                SetConsoleTextAttribute(debugHandle, 7u);
            }
        }

#elif defined __ANDROID__ //Android messages

        //TODO: Android problems, in which lib is mm.first?
        /*for (size_t i = 0u; i < mm.size(); ++i)
        {
        if (mm[i].second == MessageType::Error && JEJ_DEBUG_LEVEL > 0)
        __android_log_assert(0, "jej", mm[i].first.c_str());

        else if (mm[i].second == MessageType::Warning && JEJ_DEBUG_LEVEL > 1)
        __android_log_assert(0, "jej", mm[i].first.c_str());

        else if (mm[i].second == MessageType::Debug && JEJ_DEBUG_LEVEL > 2)
        __android_log_assert(0, "jej", mm[i].first.c_str());

        else if (mm[i].second == MessageType::Info && JEJ_DEBUG_LEVEL > 3)
        <<<<<<< HEAD
        __android_log_assert(0, "jej", mm.first[i].c_str());
        =======
        __android_log_assert(0, "jej", mm[i].first.c_str());
        >>>>>>> origin/JuhoAndroidBranch
        }*/


#endif

        mm.clear();
        //std::vector<std::pair<std::string, MessageType>> next = {};
        //mm.swap(next);
    }


    bool Messenger::WriteLog(const std::string& p_name)
    {
        std::string fileName = p_name.empty() ? "log.txt" : p_name;

        FileHandler handler;

        for (auto i : m_messages)
            std::copy(i.first.begin(), i.first.end(), std::back_inserter(handler.GetReadDataRef())); //Copy all messages to FileHandler for writing

        return handler.Write(fileName);
    }


}

