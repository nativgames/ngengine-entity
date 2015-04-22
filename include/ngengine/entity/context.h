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
    
    virtual std::map<uint32_t, AbstractSerializer *> *get_serializers() = 0;
    virtual std::map<std::string, EntityDefinition *> *get_entity_definitions() = 0;

    std::vector<std::string> *get_error_messages();
    
    void push_back_error_message(std::string message);
    std::string pop_back_error_message();
    
  private:
    
    std::vector<std::string> _error_messages;
  };
  
}
}

#endif
