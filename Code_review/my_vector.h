//
//  my_vector.h
//  Code_review
//
//  Created by Yuliana Vintyuk on 11.05.22.
//

#ifndef my_vector_h
#define my_vector_h

#ifndef CODEREVIEWTASK_MYVECTOR_HPP
#define CODEREVIEWTASK_MYVECTOR_HPP
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>
/*
 * MyVector stores a collection of objects with their names.
 *
 * For each object T, MyVector stores T`s name as std::string.
 * Several objects can have similar name.
 * operator[](const std::string& name) should return the first object
 * with the given name.
 *
 * Your task is to find as many mistakes and drawbacks in this code
 * (according to the presentation) as you can.
 * Annotate these mistakes with comments.
 *
 * Once you have found all the mistakes, rewrite the code
 * so it would not change its original purpose
 * and it would contain no mistakes.
 * Try to make the code more efficient without premature optimization.
 *
 * You can change MyVector interface completely, but there are several rules:
 * 1) you should correctly and fully implement copy-on-write idiom.
 * 2) std::pair<const T&, const std::string&> operator[](int index) const must take constant time
 at worst.
 * 3) const T& operator[](const std::string& name) const should be present.
 * 4) both operator[] should have non-const version.
 * 5) your implementation should provide all the member types of std::vector.
 * 6) your implementation should provide the following functions:
 * 1) begin(), cbegin(), end(), cend()
 * 2) empty(), size()
 * 3) reserve(), clear()
 */

//Recommended to use composition and not inheritance
//If we do not re-implement all function from std::vector, MyVector behavior will be incorrect
template <typename T>
class MyVector {
    using key_value_type = std::pair<T, std::string>;
    using internal_vector_data_type = std::vector<key_value_type>;
    std::shared_ptr<internal_vector_data_type> m_data;
    
    void copy_data() {
        if (m_data.use_count()>1) {
            auto temp_data = std::make_shared<internal_vector_data_type>();
            *temp_data = *m_data;
            m_data = temp_data;
        }
    }
public:
    using value_type = typename internal_vector_data_type::value_type;
    using allocator_type = typename internal_vector_data_type::allocator_type;
    using size_type = typename internal_vector_data_type::size_type;
    using difference_type = typename internal_vector_data_type::difference_type;
    using reference = typename internal_vector_data_type::reference;
    using const_reference = typename internal_vector_data_type::const_reference;
    using pointer = typename internal_vector_data_type::pointer;
    using const_pointer = typename internal_vector_data_type::const_pointer;
    using iterator = typename internal_vector_data_type::iterator;
    using const_iterator = typename internal_vector_data_type::const_iterator;
    using reverse_iterator = typename internal_vector_data_type::reverse_iterator;
    using const_reverse_iterator = typename internal_vector_data_type::const_reverse_iterator;

    MyVector()
    {
        m_data = std::make_shared<internal_vector_data_type>();
    }
    MyVector(const MyVector& other) : m_data(other.m_data) {}
    
    void push_back(const T& obj, const std::string& name)
    {
        copy_data();
        m_data->push_back(std::make_pair(obj, name));
    }
    
    std::pair<const T&, const std::string&> operator[](int index) const
    {
        return (*m_data)[index];
    }
    
    std::pair<T&, std::string&> operator[](int index)
    {
        // Could be changed, must copy just in case
        copy_data();
        return (*m_data)[index];
    }
    
    const T& operator[](const std::string& name) const
    {
        auto iter = std::find_if(m_data->begin(), m_data->end(),                                                             [name](key_value_type kv) { return kv.second == name;});
        
        return iter->first;
    }
    
    T& operator[](const std::string& name)
    {
        // Could be changed, must copy just in case
        copy_data();
        auto iter = std::find_if(m_data->begin(), m_data->end(),                                                       [name](key_value_type kv) { return kv.second == name;});
        
        return iter->first;
    }
    
    auto begin() {
        copy_data();
        return m_data->begin();
    }
    
    auto cbegin() const {
        return m_data->cbegin();
    }
    
    auto end() {
        copy_data();
        return m_data->end();
    }
    
    auto cend() const {
        return m_data->cend();
    }
    
    auto empty() const {
        return m_data->empty();
    }
    
    auto size() const {
        return m_data->size();
    }
    
    void reserve(typename internal_vector_data_type::value_type new_cap) {
        copy_data();
        m_data->reserve(new_cap);
    }
    
    void clear() {
        copy_data();
        m_data->clear();
    }
};

#endif //CODEREVIEWTASK_MYVECTOR_HPP

#endif /* my_vector_h */
