template <typename ... Ms>
inline void Messenger::add(const MessageType& t, const Ms& ... ms)
{
    messages.emplace_back(addString(ms...), t);
}


template <typename M>
inline std::string Messenger::addString(const M& m)
{
    std::ostringstream stream;
    stream << m;
    return stream.str();
}


template <typename M, typename ... Ms>
inline std::string Messenger::addString(const M& m, const Ms& ... ms)
{
    return addString(m) + "\n" + addString(ms...);
}
