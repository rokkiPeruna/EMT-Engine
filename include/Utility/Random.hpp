#ifndef K_RAND_HPP
#define K_RAND_HPP

#include <limits>
#include <random>

namespace jej
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
        Random(const T p_min, const T p_max);

        //Disabled copy-constructors
        Random(const Random&) = delete;
        void operator=(const Random&) = delete;

        //Destructor
        ~Random();

        //Set limits
		inline Random& SetRange(const T p_min, const T p_max);

        //Randomize
        inline T Randomize();

    };

#include <Utility/Inl/Random.inl>

}
#endif