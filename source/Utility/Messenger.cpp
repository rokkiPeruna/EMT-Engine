#include <Utility/Messenger.hpp>


#include <Core/Settings.hpp>
#include <Utility/FileHandler/FileHandlerWin32.hpp>
#include <Utility/FileHandler/FileHandlerAndroid.hpp>


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

        for (unsigned int i = 0u; i < mm.size(); ++i)
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

#elif defined ANDROID //Android messages

        for (unsigned int i = 0u; i < mm.size(); ++i)
        {
            if (mm[i].second == MessageType::Error && JEJ_DEBUG_LEVEL > 0)
                __android_log_assert(0, "jej", mm.first[i].c_str());

            else if (mm[i].second == MessageType::Warning && JEJ_DEBUG_LEVEL > 1)
                __android_log_assert(0, "jej", mm.first[i].c_str());

            else if (mm[i].second == MessageType::Debug && JEJ_DEBUG_LEVEL > 2)
                __android_log_assert(0, "jej", mm.first[i].c_str());

            else if (mm[i].second == MessageType::Info && JEJ_DEBUG_LEVEL > 3)
                __android_log_assert(0, "jej", mm.first[i].c_str());
        }


#endif

        mm.clear();
        //std::vector<std::pair<std::string, MessageType>> next = {};
        //msg::mm.swap(next);
    }


    bool Messenger::WriteLog(const std::string& name)
    {
        std::string fileName = name.empty() ? "log.txt" : name;

#ifdef _WIN32
        FileHandlerWin32 handler;
#elif defined ANDROID
        FileHandlerAndroid handler;
#endif

        for (auto i : m_messages)
            std::copy(i.first.begin(), i.first.end(), std::back_inserter(handler.m_fileContents)); //Copy all messages to FileHandler for writing

        return handler.Write(fileName);
    }


}

