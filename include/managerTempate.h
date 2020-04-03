
// TODO
template<typename Stored, typename StoredInteface>
class Manager{

protected:
    class StoredInner{
        Stored stored;
        bool active;

    public:
        StoredInner(const Stored& store);
        StoredInner(const Stored& store, bool mode);
        StoredInner(const StoredInteface& interface);
        StoredInner(const StoredInteface& interface, bool mode);
        ~StoredInner();
        StoredInner(const StoredInner& store);

        bool isActive() const;
        Stored& getStored();

        void setMode(bool mode);
        void addInterface(const StoredInteface& interface);
        bool removeInterface(const StoredInteface& interface);
        virtual bool empty() const = 0;
    };
};