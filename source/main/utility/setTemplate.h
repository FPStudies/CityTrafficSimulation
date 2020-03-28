#ifndef SET_TEMPLATE_H
#define SET_TEMPLATE_H

template<typename Interface>
class SetTemplate{

protected:
    using Container = std::list<std::shared_ptr<Interface>>;

    Container objects;

    void addFast(const std::shared_ptr<Interface>& obj){
        objects.push_back(obj);
    }

    bool findInstance(const std::shared_ptr<Interface>& obj, Container::iterator& it){
        for(it = objects.begin(); it != objects.end();  ++it){
            if(*it == obj) {
                return false;
            }
        }
        return true;
    }

public:
    DrawSetFactory() {}

    virtual ~DrawSetFactory() {}

    DrawSetFactory(const DrawSetFactory& other) 
    : objects(other.objects)
    {}

    DrawSetFactory(const std::shared_ptr<Interface>& obj){
        addFast(obj);
    }

    void add(std::shared_ptr<Interface>& obj){
        addFast(obj);
    }

    bool addNew(std::shared_ptr<Interface>& obj){
        Container::iterator it;
        if(!findInstance(obj, it)) {
            addFast(obj);
            return false;
        }
        return true;
    }
    
    bool remove(std::shared_ptr<Interface>& obj){
        Container::iterator it;
        if(findInstance(obj, it)) {
            objects.erase(it);
            return false;
        }
        return true;
    }

    bool empty() const{
        return objects.empty();
    }

    Container getAll() const{
        return objects;
    }

};


#endif