#ifndef _SPARSE_ARRAY_HPP_
#define _SPARSE_ARRAY_HPP_

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

template <typename Component>
class SparseArray
{
  public:
    using value_type = std::optional<Component>;
    using reference_type = value_type&;
    using const_reference_type = value_type const&;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

  public:
    SparseArray() = default;
    SparseArray(SparseArray const& other);
    SparseArray(SparseArray&& other) noexcept;
    ~SparseArray() = default;

    SparseArray& operator=(SparseArray const& other);
    SparseArray& operator=(SparseArray&& other) noexcept;

    reference_type operator[](size_t idx);
    const_reference_type operator[](size_t idx) const;

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    size_type size() const;

    reference_type insert_at(size_type pos, Component const& component);
    reference_type insert_at(size_type pos, Component&& component);

    template <typename... Params>
    reference_type emplace_at(size_type pos, Params&&... params);

    void erase(size_type pos);
    size_type get_index(value_type const& value) const;

  private:
    container_t _data;
};

template <typename Component>
SparseArray<Component>::SparseArray(SparseArray const& other)
    : _data(other._data)
{
}

template <typename Component>
SparseArray<Component>::SparseArray(SparseArray&& other) noexcept
    : _data(std::move(other._data))
{
}

template <typename Component>
SparseArray<Component>&
SparseArray<Component>::operator=(SparseArray const& other)
{
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

template <typename Component>
SparseArray<Component>&
SparseArray<Component>::operator=(SparseArray&& other) noexcept
{
    if (this != &other) {
        _data = std::move(other._data);
    }
    return *this;
}

template <typename Component>
typename SparseArray<Component>::reference_type
SparseArray<Component>::operator[](size_t idx)
{
    return _data[idx];
}

template <typename Component>
typename SparseArray<Component>::const_reference_type
SparseArray<Component>::operator[](size_t idx) const
{
    return _data[idx];
}

template <typename Component>
typename SparseArray<Component>::iterator SparseArray<Component>::begin()
{
    return _data.begin();
}

template <typename Component>
typename SparseArray<Component>::const_iterator
SparseArray<Component>::begin() const
{
    return _data.begin();
}

template <typename Component>
typename SparseArray<Component>::const_iterator
SparseArray<Component>::cbegin() const
{
    return _data.cbegin();
}

template <typename Component>
typename SparseArray<Component>::iterator SparseArray<Component>::end()
{
    return _data.end();
}

template <typename Component>
typename SparseArray<Component>::const_iterator
SparseArray<Component>::end() const
{
    return _data.end();
}

template <typename Component>
typename SparseArray<Component>::const_iterator
SparseArray<Component>::cend() const
{
    return _data.cend();
}

template <typename Component>
typename SparseArray<Component>::size_type SparseArray<Component>::size() const
{
    return _data.size();
}

template <typename Component>
typename SparseArray<Component>::reference_type
SparseArray<Component>::insert_at(size_type pos, Component const& component)
{
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }
    _data[pos] = component;
    return _data[pos];
}

template <typename Component>
typename SparseArray<Component>::reference_type
SparseArray<Component>::insert_at(size_type pos, Component&& component)
{
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }
    _data[pos] = std::move(component);
    return _data[pos];
}

template <typename Component>
template <typename... Params>
typename SparseArray<Component>::reference_type
SparseArray<Component>::emplace_at(size_type pos, Params&&... params)
{
    if (pos >= _data.size()) {
        _data.resize(pos + 1);
    }

    using allocator_type = typename container_t::allocator_type;
    using alloc_traits = std::allocator_traits<allocator_type>;
    using component_allocator =
        typename alloc_traits::template rebind_alloc<Component>;
    using component_alloc_traits = std::allocator_traits<component_allocator>;

    component_allocator alloc = _data.get_allocator();

    if (_data[pos].has_value()) {
        Component* ptr = std::addressof(_data[pos].value());
        component_alloc_traits::destroy(alloc, ptr);
    }

    _data[pos].emplace(std::forward<Params>(params)...);
    return _data[pos];
}

template <typename Component>
void SparseArray<Component>::erase(size_type pos)
{
    if (pos < _data.size()) {
        _data[pos].reset();
        _data[pos].resetee()
    }
}

template <typename Component>
typename SparseArray<Component>::size_type
SparseArray<Component>::get_index(value_type const& value) const
{
    const value_type* ptr = std::addressof(value);
    const value_type* base = _data.data();
    return static_cast<size_type>(ptr - base);
}

#endif
