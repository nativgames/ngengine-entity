#include <ngengine/entity/context.h>

using namespace nge;
using namespace nge::entity;

Context::~Context()
{  
}

std::vector<std::string> *Context::get_error_messages()
{
  return &_error_messages;
}
    
void Context::push_back_error_message(std::string message)
{
  _error_messages.push_back(message);
}

std::string Context::pop_back_error_message()
{
  std::string msg;
  
  if(_error_messages.size() > 0)
    msg = _error_messages.at(_error_messages.size() - 1);
  
  _error_messages.pop_back();
  
  return msg;
}

std::map<uint32_t, AbstractSerializer *> *Context::get_serializers()
{
  return &_serializers;
}

std::map<std::string, EntityDefinition *> *Context::get_entity_definitions()
{
  return &_entity_definitions;
}
