/*
 * DoubleKeyManager.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UTILITY_DOUBLE_KEY_MANAGER_H
#define TRAFFIC_SIM_MAIN_UTILITY_DOUBLE_KEY_MANAGER_H


#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <memory>

#include "ID.hpp"

namespace Utils{

template<
    typename KeyOne, 
    typename KeyTwo, 
    typename SharedVariable>
class DoubleKeyManager{
protected:
    
    struct Pair{
        KeyOne key_one_;
        KeyTwo key_two_;
        std::shared_ptr<SharedVariable> shared_variable_;

        Pair(const KeyOne& one, const KeyTwo& two, const std::shared_ptr<SharedVariable>& var)
        : key_one_(one), key_two_(two), shared_variable_(var)
        {}

    };

    struct IndexByKeyOne {};
    struct IndexByKeyTwo {};

    /**
     * @brief Container used to store a Pair stuct with 2 keys.
     * 
     */
    using Container = typename boost::multi_index_container<
    Pair,
    boost::multi_index::indexed_by<
    boost::multi_index::ordered_unique<
        boost::multi_index::tag<IndexByKeyOne>,
        boost::multi_index::member<Pair, KeyOne, &Pair::key_one_>
    >,
    boost::multi_index::ordered_unique<
        boost::multi_index::tag<IndexByKeyTwo>,
        boost::multi_index::member<Pair, KeyTwo, &Pair::key_two_>
    >>
    >;

    using ViewNodeByOne = typename boost::multi_index::index<Container, IndexByKeyOne>::type;
    using ViewNodeByTwo = typename boost::multi_index::index<Container, IndexByKeyTwo>::type;
    
    using IterOne = typename Container::template index_iterator<IndexByKeyOne>::type;
    using IterTwo = typename Container::template index_iterator<IndexByKeyTwo>::type;

    Container map_;



    bool keyOneExist(const KeyOne& one){
        ViewNodeByOne& index_by_key_one_id = map_.template get<IndexByKeyOne>();
        auto found = index_by_key_one_id.find(one);

        if(found != index_by_key_one_id.end())
            return true;
        return false;
    }

    bool keyTwoExist(const KeyTwo& two){
        ViewNodeByTwo& index_by_key_two = map_.template get<IndexByKeyTwo>();
        auto found = index_by_key_two.find(two);

        if(found != index_by_key_two.end())
            return true;
        return false;
    }



public:
    DoubleKeyManager() = default;
    ~DoubleKeyManager() = default;
    DoubleKeyManager(const DoubleKeyManager&) = delete;
    DoubleKeyManager& operator=(const DoubleKeyManager&) = delete;


    bool add(const std::shared_ptr<SharedVariable>& var, const KeyOne& one, const KeyTwo& two){
        if(keyOneExist(one))
            return true;

        auto& index_by_key_one_id = map_.template get<IndexByKeyTwo>();

        index_by_key_one_id.insert(Pair(one, two, var)); // making copy

        return false;
    }

    KeyOne getKeyOne(const KeyTwo& one) const{
        auto& index_by_key_two = map_.template get<IndexByKeyTwo>();
        auto found = index_by_key_two.find(one);
        
        if(found != index_by_key_two.end())
            return (*found).key_one_;
        return KeyOne();
    }

    KeyTwo getKeyTwo(const KeyOne& two) const{
        auto& index_by_key_one_id = map_.template get<IndexByKeyOne>();
        auto found = index_by_key_one_id.find(two);

        if(found != index_by_key_one_id.end())
            return (*found).key_two_;
        return KeyTwo();
    }

    bool remove(const KeyOne& one){
        ViewNodeByOne& index_by_key_one_id = map_.template get<IndexByKeyOne>();
        IterOne found = index_by_key_one_id.template find(one);

        if(found == index_by_key_one_id.end())
            return true;
        
        index_by_key_one_id.erase(found);
        return false;
    }

    bool remove(const KeyTwo& two){
        ViewNodeByTwo& index_by_key_two = map_.template get<IndexByKeyTwo>();
        IterTwo found = index_by_key_two.template find(two);

        if(found == index_by_key_two.end())
            return true;

        index_by_key_two.erase(found);
        return false;
    }

    const SharedVariable& getVariable(const KeyOne& one){
        ViewNodeByOne& index_by_key_one_id = map_.template get<IndexByKeyOne>();
        IterOne found = index_by_key_one_id.template find(one);

        if(found == index_by_key_one_id.end())
            throw std::out_of_range("Element not found.");
        
        return *(found->shared_variable_);
    }

    const SharedVariable& getVariable(const KeyTwo& two){
        ViewNodeByTwo& index_by_key_two = map_.template get<IndexByKeyTwo>();
        IterTwo found = index_by_key_two.template find(two);

        if(found == index_by_key_two.end())
            throw std::out_of_range("Element not found.");
        
        return *(found->shared_variable_);
    }
};

}

#endif
