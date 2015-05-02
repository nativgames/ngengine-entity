#include <ngengine/entity/serializer/raw/serializer.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

using namespace nge::entity;
using namespace nge::entity::serializer::raw;

RawBuffer::RawBuffer()
{
  size = 0;
  variable_size = false;
  data = nullptr;
}

RawBuffer::~RawBuffer()
{
  free(data);
}
    
// Macro declaring serializer for integers
#define DEFINE_INT_SERIALIZER(name, id, serialize_fn, decode_fn) \
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
 RawBuffer *buf = (RawBuffer *) dest;\
 buf->variable_size = false;\
 buf->size = sizeof(name);\
 buf->data = malloc(sizeof(name)); \
 name v = serialize_fn(*((name *) to_serialize));\
 memcpy(buf->data, &v, sizeof(name));\
}\
\
void name##Serializer::decode(const void *to_decode, void *dest)\
{\
  RawBuffer *buf = (RawBuffer *) to_decode;\
  name v;\
  memcpy(&v, buf->data, sizeof(name));\
  *((name *)dest) = decode_fn(v);\
}\

// declare the integers serializers
DEFINE_INT_SERIALIZER(uint8_t, UINT8, , )
DEFINE_INT_SERIALIZER(uint16_t, UINT16, htobe16, be16toh)
DEFINE_INT_SERIALIZER(uint32_t, UINT32, htobe32, be32toh)
DEFINE_INT_SERIALIZER(uint64_t, UINT64, htobe64, be64toh)
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

stringSerializer::~stringSerializer()
{
}

int stringSerializer::get_supported_type()
{
  return STRING;
}
void *stringSerializer::create_entity()
{
  return new std::string;
}
void stringSerializer::copy(const void *src, void *dest)
{
  *((std::string *) dest) = *((std::string *) src);
}

void stringSerializer::serialize(const void *to_serialize, void *dest)
{
  RawBuffer *buf = (RawBuffer *) dest;
  std::string *str = ((std::string *)to_serialize);
  buf->variable_size = true;
  buf->size = strlen(str->c_str());
  buf->data = malloc(buf->size);
  memcpy(buf->data, str->c_str(), buf->size);
}

void stringSerializer::decode(const void *to_decode, void *dest)
{
  RawBuffer *buf = (RawBuffer *) to_decode;
  char *p = (char *) buf->data;
  std::string *str = ((std::string *) dest);
  
  for(uint32_t i = 0; i < buf->size; i++) {
    *str += *p;
    p++;
  }
}

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

