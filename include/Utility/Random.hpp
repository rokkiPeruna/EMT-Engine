#ifndef K_RAND_HPP
#define K_RAND_HPP

#include <limits>
#include <random>

namespace kerberos
{

    template <class T>
    class Random
    {
    private:

        //Randomization engine
        std::default_random_engine m_eng;

        //Limits
        T m_min;
        T m_max;

    public:

        //Default constructor
        Random();

        //Constructor with limits
        Random(const T min, const T max);

        //Destructor
        ~Random();

        //Set limits
		inline Random& setRange(const T min, const T max);

        //Randomize
        inline T r();

    };

#include <Util/Inl/Random.inl>

}
#endif