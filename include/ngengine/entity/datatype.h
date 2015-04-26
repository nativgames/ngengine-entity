#ifndef NGENGINE_ENTITY_DATATYPE_H
#define NGENGINE_ENTITY_DATATYPE_H

namespace nge {
namespace entity {    

  /*
    Define the types serializable by ngengine-orm and ngengine-network.
    Serialializer may be created to extend possibilities.
  */
  
  enum DataType {
    UNKNOWN = 0,
    UINT8   = 1,
    UINT16  = 2,
    UINT32  = 3,
    UINT64  = 4,
    SINT8   = 5,
    SINT16  = 6,
    SINT32  = 7,
    SINT64  = 8,
    FLOAT   = 9,
    DOUBLE  = 10,
    STRING  = 11,   // std::string
    ENTITY =  12
  };
    
}
}

#endif

