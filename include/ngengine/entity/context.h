#ifndef NGENGINE_ENTITY_CONTEXT_H
#define	NGENGINE_ENTITY_CONTEXT_H

#include <vector>
#include <map>
#include <ngengine/entity/serializer.h>

namespace nge {
namespace entity {
  
  class EntityDefinition;
  
  class Context {
  public:
    
    virtual ~Context();
    
    std::map<uint32_t, AbstractSerializer *> *get_serializers();
    std::map<std::string, EntityDefinition *> *get_entity_definitions();

    std::vector<std::string> *get_error_messages();
    
    void push_back_error_message(std::string message);
    std::string pop_back_error_message();
    
  protected:
    
    std::vector<std::string> _error_messages;
    
    std::map<uint32_t, AbstractSerializer *> _serializers;
    std::map<std::string, EntityDefinition *> _entity_definitions;
  };
  
}
}

#endif
