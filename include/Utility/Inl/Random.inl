
template <class T>
Random<T>::Random() :
m_eng(std::random_device()()),
m_min((std::numeric_limits<T>::min)()),
m_max((std::numeric_limits<T>::max)())
{

}

template <class T>
Random<T>::Random(const T min, const T max) :
m_eng(std::random_device()()),
m_min(min <= max ? min : max),
m_max(max >= min ? max : min)
{

}

template<class T>
Random<T>::~Random()
{

}

template <class T>
inline Random<T>& Random<T>::setRange(const T min, const T max)
{
    m_min = min <= max ? min : max;
    m_max = max >= min ? max : min;
    return *this;
}

template <class T>
inline T Random<T>::r()
{
    return static_cast<T>(std::uniform_real_distribution<long double>(m_min, m_max)(m_eng));
}
