#ifndef NGENGINE_ENTITY_SERIALIZER_H
#define	NGENGINE_ENTITY_SERIALIZER_H

#include <string>

namespace nge {
namespace entity {   
  
  class AbstractSerializer {
  public:
    
    virtual ~AbstractSerializer();
    
    virtual int get_supported_type() = 0;
    
    virtual void *create_entity() = 0;
    virtual void copy(const void *src, void *dest) = 0;
    
    virtual std::string serialize(void *to_serialize) = 0;
    virtual void decode(const std::string &to_decode, void *dest) = 0;
    
  };
  
}
}

#endif	/* SERIALIZER_H */

