
#ifndef TF_ASSET_H
#define TF_ASSET_H

#include "tf_mapwithrules.h"
#include "tf_trackgrouping.h"
#include "tf_trackgroup.h"
#include "tf_rational.h"
#include "tf_audiodesc.h"
#include "tf_videodesc.h"
#include "tf_trackgroupslice.h"

class TFAssetList;

class TFAsset {
public:
    enum asset_type_t {
        ASSET_NULL=0,
        ASSET_GENERATOR,
        ASSET_FILE
    };
public:
                                                TFAsset(const std::string &_name = std::string()) : name(_name) { };
    virtual                                     ~TFAsset() { };
public:
    std::string                                 name;               // asset name (key to the list, used in tracks, usually a UUID)
    std::string                                 file_path;          // file path (if file)
    enum asset_type_t                           asset_type = ASSET_NULL;
protected:
    friend class                                TFAssetList;
};

using TFAssetListBaseClass = TFMapWithRules< std::string, TFAsset >;

class TFAssetList : public TFAssetListBaseClass {
public:
                                                TFAssetList() : TFAssetListBaseClass() { };
    virtual                                     ~TFAssetList() { };
public:
    virtual void check_key_valid(const KeyType &name) {
        /* default. override if needed */
        if (name.empty()) throw std::runtime_error("empty key name");
    }
    virtual ValType *new_value(const KeyType &name) {
        return new ValType(name);
    }
    virtual void change_key_name(const KeyType &oldname,const KeyType &newname,ValType &value) {
        (void)oldname;
        value.name = newname;
    }
};

#endif //TF_ASSET_H

