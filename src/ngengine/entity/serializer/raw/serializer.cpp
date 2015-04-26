#include <ngengine/entity/serializer/raw/serializer.h>
#include <arpa/inet.h>

using namespace nge::entity;
using namespace nge::entity::serializer::raw;

// Macro declaring serializer for integers
#define DEFINE_INT_SERIALIZER(name, type, id, serialize_fn, decode_fn) \
name##Serializer::~name##Serializer()\
{\
}\
\
int name##Serializer::get_supported_type()\
{\
  return id;\
}\
void *name##Serializer::create_entity()\
{\
  return calloc(1, sizeof(name));\
}\
void name##Serializer::copy(const void *src, void *dest)\
{\
  *((name *) dest) = *((name *) src);\
}\
void name##Serializer::serialize(const void *to_serialize, void *dest)\
{\
  *((name *)dest) = serialize_fn(*((name *) to_serialize));\
}\
\
void name##Serializer::decode(const void *to_decode, void *dest)\
{\
  *((name *)dest) = decode_fn(*((name *) to_decode));\
}\

// declare the integers serializers
DEFINE_INT_SERIALIZER(uint8_t, uint16_t, UINT8, , )
DEFINE_INT_SERIALIZER(uint16_t, uint16_t, UINT16, htobe16, be16toh)
DEFINE_INT_SERIALIZER(uint32_t, uint32_t, UINT32, htobe32, be32toh)
DEFINE_INT_SERIALIZER(uint64_t, uint64_t, UINT64, htobe64, be64toh)
// TODO: find how to treat endianness with signed variable
//DEFINE_INT_SERIALIZER(int8_t, int16_t, SINT8, , )
//DEFINE_INT_SERIALIZER(int16_t, int16_t, SINT16, htons, )
//DEFINE_INT_SERIALIZER(int32_t, int32_t, SINT32, , )
//DEFINE_INT_SERIALIZER(int64_t, int64_t, SINT64, , )
// Can't really treat about endianness with float or double ...
// TODO: find a solution
//DEFINE_INT_SERIALIZER(float, float, FLOAT, , )
//DEFINE_INT_SERIALIZER(double, double, DOUBLE, , )

// use macro overkill 
#define DEFINE_STR_SERIALIZER(name, id) \
name##Serializer::~name##Serializer()\
{\
}\
\
int name##Serializer::get_supported_type()\
{\
  return id;\
}\
void *name##Serializer::create_entity()\
{\
  return new std::string;\
}\
void name##Serializer::copy(const void *src, void *dest)\
{\
  *((std::string *) dest) = *((std::string *) src);\
}\
\
void name##Serializer::serialize(const void *to_serialize, void *dest)\
{\
  *((std::string *)dest) =  *((std::string *)to_serialize);\
}\
\
void name##Serializer::decode(const void *to_decode, void *dest)\
{\
  *((std::string *) dest) = *((std::string *)to_decode);\
}\

DEFINE_STR_SERIALIZER(string, STRING)

// ----------
  
RawContext::RawContext()
{
  entity::AbstractSerializer *s;
  
#define ADD_SERIALIZER(type) \
  s = new type##Serializer();\
  this->_serializers.insert(std::make_pair(s->get_supported_type(), s));
  
  ADD_SERIALIZER(uint8_t)
  ADD_SERIALIZER(uint16_t)
  ADD_SERIALIZER(uint32_t)
  ADD_SERIALIZER(uint64_t)
  //ADD_SERIALIZER(int8_t)
  //ADD_SERIALIZER(int16_t)
  //ADD_SERIALIZER(int32_t)
  //ADD_SERIALIZER(int64_t)
  //ADD_SERIALIZER(float)
  //ADD_SERIALIZER(double)
  ADD_SERIALIZER(string)
}

