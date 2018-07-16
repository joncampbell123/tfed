
#ifndef TF_MAPWITHRULES_H
#define TF_MAPWITHRULES_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

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
        if (name.empty()) throw std::runtime_error("empty key name");
    }
    virtual ValType *new_value(const KeyType &name) {
        /* override if needed */
        return new ValType(name);
    }
public:
    void clear(void) {
        do {
            auto i = SelfType::begin();
            if (i == SelfType::end()) break;
            SelfType::erase(i);
        } while (1);
    }
    valtype& create(const keytype &name) {
        check_key_valid(name); /* throw exception if not */

        auto i = BaseType::find(name);
        if (i != BaseType::end()) throw std::runtime_error("create: sequence already exists");

        auto &ptr = BaseType::operator[](name); /* poof */
        ptr = new_value(name);/* will throw exception on failure */

        return *ptr;
    }
    valtype& operator[](const keytype &name) {
        check_key_valid(name); /* throw exception if not */

        auto i = BaseType::find(name);
        if (i == BaseType::end()) throw std::runtime_error("[]: sequence does not exist");

        auto &ptr = i->second;
        if (ptr == NULL) throw std::runtime_error("[]: sequence does exist but ptr is null");

        return *ptr;
    }
    void erase(ListIterator const &i) {
        auto &ptr = i->second;
        if (ptr == NULL) throw std::runtime_error("erase: sequence does exist but ptr is null");
        delete ptr;

        BaseType::erase(i);
    }
    void erase(const keytype &name) {
        check_key_valid(name); /* throw exception if not */

        auto i = BaseType::find(name);
        if (i == BaseType::end()) throw std::runtime_error("erase: sequence does not exist");

        SelfType::erase(i);
    }
    void rename(const keytype &oldname,const keytype &newname) {
        check_key_valid(oldname);
        check_key_valid(newname);

        if (oldname != newname) {
            auto old_i = BaseType::find(oldname);
            if (old_i == BaseType::end()) throw std::runtime_error("rename_sequence: old name does not exist");

            auto &old_p = old_i->second;
            if (old_p == NULL) throw std::runtime_error("rename_sequence: old name does exist but is null");

            auto new_i = BaseType::find(newname);
            if (new_i != BaseType::end()) throw std::runtime_error("rename_sequence: new name already exists");

            auto &new_p = BaseType::operator[](newname);

            new_p = old_p;
            new_p->name = newname;

            BaseType::erase(old_i);
        }
    }
public:
    ListIterator find(const keytype &name) {
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

