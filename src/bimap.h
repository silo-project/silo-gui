//
// https://stackoverflow.com/a/35528441
//

#include <algorithm>
#include <list>

#ifndef SILO_GUI_BIMAP_H
#define SILO_GUI_BIMAP_H


namespace bimap {
    namespace detail {
        template <typename Cmp, typename V, size_t I> struct CompareByElement : private Cmp {
            bool operator()(V const& a, V const& b) const {
                using std::get;
                return Cmp::operator()(get<I>(a), get<I>(b));
            }
            bool operator()(V const& a, V const& b) {
                using std::get;
                return Cmp::operator()(get<I>(a), get<I>(b));
            }
        };

        namespace tags {
            struct left_view;
            struct right_view;
        }

        template <typename ViewTag, typename Left, typename Right, typename LeftCmp, typename RightCmp, typename RawAlloc>
        struct view_traits;

        template <typename Left, typename Right, typename LeftCmp, typename RightCmp, typename RawAlloc>
        struct view_traits<tags::left_view, Left, Right, LeftCmp, RightCmp, RawAlloc> {
            using value_type     = std::tuple<Left, Right>;
            using allocator_type = typename RawAlloc::template rebind<value_type>::other;
            using base_type      = std::list<value_type, allocator_type>;
            using comparator     = CompareByElement<LeftCmp, value_type, 0>;
        };

        template <typename Left, typename Right, typename LeftCmp, typename RightCmp, typename RawAlloc>
        struct view_traits<tags::right_view, Left, Right, LeftCmp, RightCmp, RawAlloc> {
            using value_type     = std::tuple<Left, Right>;
            using allocator_type = typename RawAlloc::template rebind<std::reference_wrapper<value_type const>>::other;
            using base_type      = std::list<std::reference_wrapper<value_type const>, allocator_type>;
            using comparator     = CompareByElement<RightCmp, value_type, 1>;
        };

        template <typename Left, typename Right, typename LeftCmp, typename RightCmp, typename RawAlloc>
        struct bimap_traits {
            using left_traits = view_traits<tags::left_view,  Left, Right, LeftCmp, RightCmp, RawAlloc>;
            using right_traits = view_traits<tags::right_view, Left, Right, LeftCmp, RightCmp, RawAlloc>;
        };

        template <typename Traits> struct map_adaptor :
                private Traits::base_type,
                private Traits::comparator // empty base class optimization
        {
            using value_type     = typename Traits::value_type;
            using allocator_type = typename Traits::allocator_type;
            using base_type      = typename Traits::base_type;
            using comparator     = typename Traits::comparator;

            using iterator       = typename base_type::iterator;
            using const_iterator = typename base_type::const_iterator;

            using base_type::cbegin;
            using base_type::cend;
            using base_type::begin;
            using base_type::end;
            using base_type::insert;
            using base_type::size;

            auto lower_bound(value_type const& v)       { return std::lower_bound(base_type::begin(), base_type::end(), v, get_comp()); }
            auto upper_bound(value_type const& v)       { return std::upper_bound(base_type::begin(), base_type::end(), v, get_comp()); }
            auto equal_range(value_type const& v)       { return std::equal_range(base_type::begin(), base_type::end(), v, get_comp()); }
            auto lower_bound(value_type const& v) const { return std::lower_bound(base_type::begin(), base_type::end(), v, get_comp()); }
            auto upper_bound(value_type const& v) const { return std::upper_bound(base_type::begin(), base_type::end(), v, get_comp()); }
            auto equal_range(value_type const& v) const { return std::equal_range(base_type::begin(), base_type::end(), v, get_comp()); }

            auto find(value_type const& v) {
                auto er = equal_range(v);
                return er.first == er.second? end() : er.first;
            }

            auto find(value_type const& v) const {
                auto er = equal_range(v);
                return er.first == er.second? end() : er.first;
            }

            base_type& base()                  { return *static_cast<base_type*>(this);       }
            base_type const & base() const     { return *static_cast<base_type const*>(this); }
        private:
            comparator& get_comp()             { return *this;                                }
            comparator const& get_comp() const { return *this;                                }
        };
    }

    template <typename Left, typename Right,
            typename LeftCmp = std::less<Left>, typename RightCmp = std::less<Right>,
            typename RawAlloc = std::allocator<void>,
            typename Traits = detail::bimap_traits<Left, Right, LeftCmp, RightCmp, RawAlloc>
    >
    class bimap : private detail::map_adaptor<typename Traits::left_traits> {
    public:
        using left_type      = typename detail::map_adaptor<typename Traits::left_traits>;
        using right_type     = typename detail::map_adaptor<typename Traits::right_traits>;

        using value_type     = typename Traits::left_traits::value_type;
        using allocator_type = typename Traits::left_traits::allocator_type;
        using base_type      = left_type;

        using const_iterator = typename base_type::const_iterator;
        using iterator       = const_iterator;

        using base_type::cbegin;
        using base_type::cend;
        auto begin() const { return cbegin(); }
        auto end() const { return cend(); }
        using base_type::size;

        left_type  const& left()  const { return *this;         }
        right_type const& right() const { return inverse_index; }

        std::pair<const_iterator, bool> insert(value_type const& v) {
            auto lr = left().find(v);
            auto rr = right().find(v);

            bool hasl = lr!=left().end(),
                    hasr = rr!=right().end();

            if (!hasl && !hasr) {
                auto lins = mutable_left().insert(left().lower_bound(v), v);
                auto rins = mutable_right().insert(right().lower_bound(*lins), *lins);
                (void) rins;

                return { lins, true };
            } else {
                return { end(), false };
            }
        }

    private:
        detail::map_adaptor<typename Traits::right_traits> inverse_index;
        left_type&  mutable_left()  { return *this;         }
        right_type& mutable_right() { return inverse_index; }
    };
}


#endif //SILO_GUI_BIMAP_H
