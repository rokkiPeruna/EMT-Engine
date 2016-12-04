template <typename ... Ms>
inline void Messenger::Add(const MessageType& t, const Ms& ... ms)
{
    m_messages.emplace_back(_addString(ms...), t);
}


template <typename M>
inline std::string Messenger::_addString(const M& m)
{
    std::ostringstream stream;
    stream << m;
    return stream.str();
}


template <typename M, typename ... Ms>
inline std::string Messenger::_addString(const M& m, const Ms& ... ms)
{
    return _addString(m) + "\n" + _addString(ms...);
}
