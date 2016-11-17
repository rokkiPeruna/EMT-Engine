#ifndef JEJ_MESSAGES_HPP
#define JEJ_MESSAGES_HPP



#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace jej
{
    class Messenger
    {
    public:

        enum class MessageType
        {
            Error,
            Warning,
            Debug,
            Info
        };

        //No instances of this class can be created
        Messenger() = delete;
        Messenger(const Messenger&) = delete;
        Messenger operator=(const Messenger&) = delete;
        ~Messenger() = delete;

        //Add a message to be printed
        template <typename ... Ms>
        static void Add(const MessageType& t, const Ms& ... ms);

        //Print all the messages
        static void PrintMessages();

        //Write all messages to log file
        //Name is filename with extension, defaults to log.txt
        static bool WriteLog(const std::string& name = "");

    private:

        //Add single element to be printed
        template <typename M>
        static std::string _addString(const M& m);

        //Add multiple elements to be printed
        template <typename M, typename ... Ms>
        static std::string _addString(const M& m, const Ms& ... ms);

        //Messages to be printed
        static std::vector<std::pair<std::string, MessageType>> m_messages;

    };

#include <Utility/Inl/Messenger.inl>

}


#endif