// copyright 2017 war10ck

#ifndef GDU_SINGLETON_HPP_
#define GDU_SINGLETON_HPP_

namespace gdp {
namespace gdu {

template<typename T>
class Singleton {
 public:
        static T& Instance() {
            static T instance;
            return instance;
        }
        Singleton() = delete;
        Singleton( const Singleton & ) = delete;
        Singleton & operator = ( const Singleton & ) = delete;
};

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_SINGLETON_HPP_
