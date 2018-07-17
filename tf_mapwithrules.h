
#ifndef TF_MAPWITHRULES_H
#define TF_MAPWITHRULES_H

#include <map>
#include <string>

template <class keytype, class valtype> class TFMapWithRules : protected std::map< keytype, valtype* > {
public:
    using KeyType =                             keytype;
    using ValType =                             valtype;
    using SelfType =                            TFMapWithRules<keytype, valtype>;
    typedef std::map< keytype, valtype* >       BaseType;
    typedef typename BaseType::iterator         ListIterator;
public:
    TFMapWithRules() : BaseType() { }
    virtual ~TFMapWithRules() {
        clear();
    }
public:
    virtual void check_key_valid(const KeyType &name) {
        /* default. override if needed */
        (void)name;
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        /* override if needed */
        (void)oldname;
        (void)newname;
        (void)value;
    }
    virtual ValType *new_value(const KeyType &name) = 0;
public:
    virtual void clear(void) {
        do {
            auto i = SelfType::begin();
            if (i == SelfType::end()) break;
            SelfType::erase(i);
        } while (1);
    }
    virtual ValType& create(const KeyType &name) {
        check_key_valid(name); /* throw exception if not */

        auto i = BaseType::find(name);
        if (i != BaseType::end()) throw std::runtime_error("create: key already exists");

        auto &ptr = BaseType::operator[](name); /* poof */
        ptr = new_value(name);/* will throw exception on failure */

        return *ptr;
    }
    virtual ValType& operator[](const KeyType &name) {
        check_key_valid(name); /* throw exception if not */

        auto i = BaseType::find(name);
        if (i == BaseType::end()) throw std::runtime_error("[]: key does not exist");

        auto &ptr = i->second;
        if (ptr == NULL) throw std::runtime_error("[]: key does exist but ptr is null");

        return *ptr;
    }
    virtual ListIterator erase(ListIterator const &i) {
        auto &ptr = i->second;
        if (ptr == NULL) throw std::runtime_error("erase: key does exist but ptr is null");
        delete ptr;

        return BaseType::erase(i);
    }
    virtual void erase(const KeyType &name) {
        check_key_valid(name); /* throw exception if not */

        auto i = BaseType::find(name);
        if (i == BaseType::end()) throw std::runtime_error("erase: key does not exist");

        SelfType::erase(i);
    }
    virtual void rename(const KeyType &oldname,const KeyType &newname) {
        check_key_valid(oldname);
        check_key_valid(newname);

        if (oldname != newname) {
            auto old_i = BaseType::find(oldname);
            if (old_i == BaseType::end()) throw std::runtime_error("rename: old key does not exist");

            auto &old_p = old_i->second;
            if (old_p == NULL) throw std::runtime_error("rename: old key does exist but is null");

            auto new_i = BaseType::find(newname);
            if (new_i != BaseType::end()) throw std::runtime_error("rename: new key already exists");

            auto &new_p = BaseType::operator[](newname);
            new_p = old_p;

            change_key_name(oldname, newname, *new_p);

            BaseType::erase(old_i);
        }
    }
public:
    ListIterator find(const KeyType &name) {
        check_key_valid(name); /* throw exception if not */

        return BaseType::find(name);
    }
    ListIterator begin(void) {
        return BaseType::begin();
    }
    ListIterator end(void) {
        return BaseType::end();
    }
protected: /* the base class is protected */
};

#endif //TF_MAPWITHRULES_H

