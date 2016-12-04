
template <class T>
Random<T>::Random() :
m_eng(std::random_device()()),
m_min((std::numeric_limits<T>::min)()),
m_max((std::numeric_limits<T>::max)())
{

}

template <class T>
Random<T>::Random(const T p_min, const T p_max) :
m_eng(std::random_device()()),
m_min(p_min <= p_max ? p_min : p_max),
m_max(p_max >= p_min ? p_max : p_min)
{

}

template<class T>
Random<T>::~Random()
{

}

template <class T>
inline Random<T>& Random<T>::SetRange(const T p_min, const T p_max)
{
    m_min = p_min <= p_max ? p_min : p_max;
    m_max = p_max >= p_min ? p_max : p_min;
    return *this;
}

template <class T>
inline T Random<T>::Randomize()
{
    return static_cast<T>(std::uniform_real_distribution<long double>(m_min, m_max)(m_eng));
}
