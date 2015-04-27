#ifndef NGENGINE_ENTITY_SERIALIZER_RAW_SERIALIZER_H
#define	NGENGINE_ENTITY_SERIALIZER_RAW_SERIALIZER_H

/*
 
 Define raw serializer: binary data stays binary data, string stays string
 Only endianness differs in binary data
 */

#include <ngengine/entity/serializer.h>
#include <ngengine/entity/context.h>

namespace nge {
namespace entity {
namespace serializer {
namespace raw {
  
  // Buffer used to serialize / deserialize
  struct RawBuffer {
    RawBuffer();
    ~RawBuffer();
    
    uint32_t size;
    bool variable_size;
    void *data;
  };
  
  DECLARE_SERIALIZER(uint8_t)
  DECLARE_SERIALIZER(uint16_t)
  DECLARE_SERIALIZER(uint32_t)
  DECLARE_SERIALIZER(uint64_t)
  //DECLARE_SERIALIZER(int8_t)
  //DECLARE_SERIALIZER(int16_t)
  //DECLARE_SERIALIZER(int32_t)
  //DECLARE_SERIALIZER(int64_t)
  //DECLARE_SERIALIZER(float)
  //DECLARE_SERIALIZER(double)
  DECLARE_SERIALIZER(string)
    
  // define the raw context
  class RawContext : public Context {
    public:
      RawContext();
  };
  
}
}
}
}

#endif	
