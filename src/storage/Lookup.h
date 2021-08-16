//
// Created by chris on 2021-08-16.
//

#ifndef HAZELCHAIN_LOOKUP_H
#define HAZELCHAIN_LOOKUP_H

#include <vector>

template<typename K, typename V>
class Lookup {
public:
    using value_type = std::pair<K, V>;
    using container_type = std::vector<value_type>;

private:
    container_type container_;

public:
    using iterator = typename container_type::const_iterator;
    using const_iterator = iterator;

    Lookup(std::initializer_list<value_type> init) : container_(init) {
        sort(container_.begin(), container_.end());
    }

    explicit Lookup(std::vector<value_type> init) : container_(init) {
        sort(container_.begin(), container_.end());
    }

    const_iterator begin() const {
        return container_.begin();
    }

    const_iterator end() const {
        return container_.end();
    }

    const_iterator find(const K &key) const {
        const_iterator it = std::lower_bound(
                begin(),
                end(),
                key,
                [](const value_type &p, const K key) {
                    return p.first < key;
                }
        );
        return it != end() && it->first == key ? it : end();
    }

    [[nodiscard]] size_t size() const {
        return container_.size();
    }

};


#endif //HAZELCHAIN_LOOKUP_H
