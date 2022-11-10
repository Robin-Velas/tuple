#ifndef T_TUPLE_H
#define T_TUPLE_H

namespace t {

    namespace help {
        template<typename L, typename R>
        struct HelpType {
            using type = std::common_type<L, R>;
        };


        /* Few tries : */
        template<typename... Types>
        struct Foo {};
        template<typename... Types>
        struct Bar;

        template<typename L, typename R>
        struct Bar<L, R> {
            using type = std::common_type<L, R>;
        };
        template<typename Type, typename... Types>
        struct Bar<Foo<Type>, Foo<Types...>> {
            using type = std::common_type<Type, Types...>;
        };
        template<typename... L, typename ... R>
        struct Bar<Foo<L...>, Foo<R...>> {
            using type = std::common_type<L..., R...>;
        };

    }

    template<typename... Types>
    class Tuple {

    };

    template<typename Type, typename... Types>
    class Tuple<Type, Types...> {

    template <typename... Args> friend class Tuple;

    private:
        Type m_value;
        Tuple<Types...> m_other;

    public:
        /**
         * Default constructor
         */
        Tuple() {}

        /**
         * Constructor to initialize values
         */
        Tuple(const Type &first, const Types &... end)
                : m_value(first), m_other(end...) {}

        /**
         * Value getter
         */
        template<int index>
        const auto& get() const {
            if constexpr(index == 0) {
                return m_value;
            } else {
                return m_other.template get<index - 1>();
            }
        }

        template<int index>
        auto& get() {
            if constexpr(index == 0) {
                return m_value;
            } else {
                return m_other.template get<index - 1>();
            }
        }
        /**
         * Addition between to tuples
         */
        template<typename ... OtherTypes>
        Tuple<typename help::Bar<Types, OtherTypes>::type...> operator+(const Tuple<OtherTypes...> &other) const {
            //Tuple<typename help::HelpType<Types, OtherTypes>::type...> t;

            Tuple<typename help::Bar<Types, OtherTypes>::type...> t;

            t.value = m_value + other.m_value;
            t.other = m_other + other.m_other;
            return t;

            // Problem : "different size between Types and OtherTypes"
        }

        /**
         * Addition between to tuples - in place
         */
        template<typename ... OtherTypes>
        Tuple<OtherTypes...> &operator+=(const Tuple<OtherTypes...> &other) {
            m_value += other.m_value;
            constexpr size_t size = sizeof...(OtherTypes);
            if constexpr(size > 1){
                m_other += other.m_other;
            }
            return *this;
        }

        /**
         * Substraction between to tuples
         */
        template<typename ... OtherTypes>
        Tuple</* implementation defined */> operator-(const Tuple<OtherTypes...> &other) const {
            // Not implemented because don't work with operator+
        }

        /**
         * Substraction between to tuples - in place
         */
        template<typename ... OtherTypes>
        Tuple<OtherTypes...> &operator-=(const Tuple<OtherTypes...> &other) {
            m_value -= other.m_value;
            constexpr size_t size = sizeof...(OtherTypes);
            if constexpr(size > 1){
                m_other -= other.m_other;
            }
            return *this;
        }

        /**
         * Multiplication between to tuples
         */
        template<typename ... OtherTypes>
        Tuple</* implementation defined */> operator*(const Tuple<OtherTypes...> &other) const {
            // Not implemented because don't work with operator+
        }

        /**
         * Multiplication between to tuples - in place
         */
        template<typename ... OtherTypes>
        Tuple<OtherTypes...> &operator*=(const Tuple<OtherTypes...> &other) {
            m_value *= other.m_value;
            constexpr size_t size = sizeof...(OtherTypes);
            if constexpr(size > 1){
                m_other *= other.m_other;
            }
            return *this;
        }

        /**
         * Division between to tuples
         */
        template<typename ... OtherTypes>
        Tuple</* implementation defined */> operator/(const Tuple<OtherTypes...> &other) const {
            // Not implemented because don't work with operator+
        }

        /**
         * Division between to tuples - in place
         */
        template<typename ... OtherTypes>
        Tuple<OtherTypes...> &operator/=(const Tuple<OtherTypes...> &other) {
            m_value /= other.m_value;
            constexpr size_t size = sizeof...(OtherTypes);
            if constexpr(size > 1){
                m_other /= other.m_other;
            }
            return *this;
        }





        /**
         * Comparaison operators
         */
        template<typename ... OtherTypes>
        bool operator==(const Tuple<OtherTypes...> &other) const {
            constexpr size_t size = sizeof...(OtherTypes);
            if(m_value != other.m_value){
                return false;
            }
            if constexpr(size > 1){
                return m_other == other.m_other;
            }
            return true;
        }

        template<typename ... OtherTypes>
        bool operator!=(const Tuple<OtherTypes...> &other) const {
            constexpr size_t size = sizeof...(OtherTypes);
            if(m_value == other.m_value){
                return false;
            }
            if constexpr(size > 1){
                return m_other != other.m_other;
            }
            return true;
        }

        template<typename ... OtherTypes>
        bool operator<(const Tuple<OtherTypes...> &other) const {
            constexpr size_t size = sizeof...(OtherTypes);
            if(m_value >= other.m_value){
                return false;
            }
            if constexpr(size > 1){
                return m_other < other.m_other;
            }
            return true;
        }

        template<typename ... OtherTypes>
        bool operator<=(const Tuple<OtherTypes...> &other) const {
            constexpr size_t size = sizeof...(OtherTypes);
            if(m_value > other.m_value){
                return false;
            }
            if constexpr(size > 1){
                return m_other <= other.m_other;
            }
            return true;
        }

        template<typename ... OtherTypes>
        bool operator>(const Tuple<OtherTypes...> &other) const {
            constexpr size_t size = sizeof...(OtherTypes);
            if(m_value <= other.m_value){
                return false;
            }
            if constexpr(size > 1){
                return m_other > other.m_other;
            }
            return true;
        }

        template<typename ... OtherTypes>
        bool operator>=(const Tuple<OtherTypes...> &other) const {
            constexpr size_t size = sizeof...(OtherTypes);
            if(m_value < other.m_value){
                return false;
            }
            if constexpr(size > 1){
                return m_other >= other.m_other;
            }
            return true;
        }




        /**
         * Concatenate two tuples
         */
        template<typename ... OtherTypes>
        Tuple<OtherTypes...> operator|(Tuple<OtherTypes...> &&other) {
            // Not implemented
        }
    };




    /**
     * Helper function to create a tuple
     */
    template <class... Types>
    constexpr Tuple<Types...> makeTuple(Types&&... args) {
        return {
            std::forward<Types>(args)...
        };
    }

}

#endif // T_TUPLE_H
