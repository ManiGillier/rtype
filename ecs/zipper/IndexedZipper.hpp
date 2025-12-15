#ifndef _INDEXED_ZIPPER_HPP_
#define _INDEXED_ZIPPER_HPP_

#include <cstddef>
#include <tuple>
#include <utility>

namespace containers
{

template <class... Containers>
class indexed_zipper;

template <class... Containers>
class indexed_zipper_iterator;

template <class... Containers>
class indexed_zipper_iterator
{
    template <class Container>
    using iterator_t = decltype(std::declval<Container&>().begin());

    template <class Container>
    using it_reference_t = typename iterator_t<Container>::reference;

  public:
    using value_type = std::tuple<size_t, it_reference_t<Containers>...>;
    using reference = value_type;
    using pointer = void;
    using difference_type = size_t;
    using iterator_category = std::forward_iterator_tag;
    using iterator_tuple = std::tuple<iterator_t<Containers>...>;

    friend containers::indexed_zipper<Containers...>;

  private:
    indexed_zipper_iterator(iterator_tuple const& it_tuple, size_t max, bool skip_check = false);

  public:
    indexed_zipper_iterator(indexed_zipper_iterator const& z) = default;

    indexed_zipper_iterator& operator++();
    indexed_zipper_iterator operator++(int);
    value_type operator*();
    value_type operator->();

    friend bool operator==(indexed_zipper_iterator<Containers...> const& lhs,
                           indexed_zipper_iterator<Containers...> const& rhs)
    {
        return lhs._idx == rhs._idx;
    }

    friend bool operator!=(indexed_zipper_iterator<Containers...> const& lhs,
                           indexed_zipper_iterator<Containers...> const& rhs)
    {
        return !(lhs == rhs);
    }

  private:
    template <size_t... Is>
    void incr_all(std::index_sequence<Is...>);

    template <size_t... Is>
    bool all_set(std::index_sequence<Is...>);

    template <size_t... Is>
    value_type to_value(std::index_sequence<Is...>);

  private:
    iterator_tuple _current;
    size_t _max;
    size_t _idx;
    static constexpr std::index_sequence_for<Containers...> _seq{};
};

template <class... Containers>
class indexed_zipper
{
  public:
    using iterator = indexed_zipper_iterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;

    indexed_zipper(Containers&... cs);

    iterator begin();
    iterator end();

  private:
    static size_t _compute_size(Containers&... containers);
    static iterator_tuple _compute_end(Containers&... containers);

  private:
    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};

template <class... Containers>
indexed_zipper_iterator<Containers...>::indexed_zipper_iterator(
    iterator_tuple const& it_tuple, size_t max, bool skip_check)
    : _current(it_tuple), _max(max), _idx(skip_check ? max : 0)
{
    if (_idx < _max && (skip_check || !all_set(_seq))) {
        incr_all(_seq);
    }
}

template <class... Containers>
indexed_zipper_iterator<Containers...>&
indexed_zipper_iterator<Containers...>::operator++()
{
    if (_idx < _max) {
        incr_all(_seq);
    }
    return *this;
}

template <class... Containers>
indexed_zipper_iterator<Containers...>
indexed_zipper_iterator<Containers...>::operator++(int)
{
    indexed_zipper_iterator tmp(*this);
    operator++();
    return tmp;
}

template <class... Containers>
typename indexed_zipper_iterator<Containers...>::value_type
indexed_zipper_iterator<Containers...>::operator*()
{
    return to_value(_seq);
}

template <class... Containers>
typename indexed_zipper_iterator<Containers...>::value_type
indexed_zipper_iterator<Containers...>::operator->()
{
    return to_value(_seq);
}

template <class... Containers>
template <size_t... Is>
void indexed_zipper_iterator<Containers...>::incr_all(
    std::index_sequence<Is...>)
{
    (++std::get<Is>(_current), ...);
    ++_idx;

    while (_idx < _max && !all_set(_seq)) {
        (++std::get<Is>(_current), ...);
        ++_idx;
    }
}

template <class... Containers>
template <size_t... Is>
bool indexed_zipper_iterator<Containers...>::all_set(std::index_sequence<Is...>)
{
    return ((std::get<Is>(_current))->has_value() && ...);
}

template <class... Containers>
template <size_t... Is>
typename indexed_zipper_iterator<Containers...>::value_type
indexed_zipper_iterator<Containers...>::to_value(std::index_sequence<Is...>)
{
    return value_type(_idx, *std::get<Is>(_current)...);
}

template <class... Containers>
indexed_zipper<Containers...>::indexed_zipper(Containers&... cs)
    : _begin(std::make_tuple(cs.begin()...)), _end(_compute_end(cs...)),
      _size(_compute_size(cs...))
{
}

template <class... Containers>
typename indexed_zipper<Containers...>::iterator
indexed_zipper<Containers...>::begin()
{
    return iterator(_begin, _size);
}

template <class... Containers>
typename indexed_zipper<Containers...>::iterator
indexed_zipper<Containers...>::end()
{
    return iterator(_end, _size, true);
}

template <class... Containers>
size_t indexed_zipper<Containers...>::_compute_size(Containers&... containers)
{
    return std::ranges::min({containers.size()...});
}

template <class... Containers>
typename indexed_zipper<Containers...>::iterator_tuple
indexed_zipper<Containers...>::_compute_end(Containers&... containers)
{
    return std::make_tuple(containers.end()...);
}

} // namespace containers

#endif
