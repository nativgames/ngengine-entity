#ifndef NGENGINE_ENTITY_SERIALIZER_H
#define	NGENGINE_ENTITY_SERIALIZER_H

#include <ngengine/entity/datatype.h>
#include <string>

namespace nge {
namespace entity {   
  
  class AbstractSerializer {
  public:
    
    virtual ~AbstractSerializer();
    
    virtual int get_supported_type() = 0;
    
    virtual void *create_entity() = 0;
    virtual void copy(const void *src, void *dest) = 0;
    
    virtual void serialize(const void *to_serialize, void *dest) = 0;
    virtual void decode(const void *to_decode, void *dest) = 0;
    
  };
  
}
}

// Use this macro to define a serializer
// Still have to implement the serializer, but still helps to minimize the code

#define DECLARE_SERIALIZER(name) \
  class name##Serializer : public entity::AbstractSerializer {\
  public:\
    \
    ~name##Serializer();\
    \
    virtual int get_supported_type();\
    \
    virtual void *create_entity();\
    virtual void copy(const void *src, void *dest);\
    \
    void serialize(const void *to_serialize, void *dest);\
    void decode(const void *to_decode, void *dest);\
  };\

#include <ngengine/entity/serializer/raw/serializer.h>

#endif	/* SERIALIZER_H */

