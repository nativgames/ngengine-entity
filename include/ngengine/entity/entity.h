#ifndef NGENGINE_ENTITY_ENTITY_H
#define	NGENGINE_ENTITY_ENTITY_H

#include <ngengine/entity/datatype.h>
#include <ngengine/entity/context.h>

namespace nge {
namespace entity {    
  
  struct AttributeDefinition {
    std::string name;
    uint32_t type;
    uint32_t offset;
    
    AttributeDefinition();
    AttributeDefinition(std::string name, uint32_t type, uint32_t offset);
  };
  
  class EntityDefinition;
  
  class Entity {
  public:
    
    Entity(Context *context);
    virtual ~Entity();
    
    virtual EntityDefinition *__get_definition() const = 0; // create an entity definition
   
    void __set(std::string name, void *p); // p is a pointer on the value
    void *__get(std::string name); // returns a pointer to the value
    
    void set_id(uint32_t id);
    uint32_t get_id() const;
    uint32_t *get_id_ptr();
    
  protected:
    uint32_t _id;
    
  protected:
    Context *_context;
    
  };
  
  // AttributeDefinition can be herited in order to extend informations: primary key, nullable etc..
  typedef std::vector<AttributeDefinition *> AttributeVector;
  typedef Entity *(*EntityFactory)();

  class EntityDefinition {
  public:
    
    EntityDefinition();
    
    void define_attribute(std::string name, uint32_t type, void *instance_addr, void *instance_attr_addr);
    
    void set_table(std::string table);
    std::string get_table() const;
    
    void set_type(uint32_t type);
    uint32_t get_type();
   
    void set_factory(EntityFactory factory);
    EntityFactory get_factory();
    
    void set_attributes(AttributeVector attributes);
    AttributeVector*get_attributes();
    const AttributeVector *get_attributes() const;
    
  private:
    
    std::string _table;
    uint32_t _type;    
    EntityFactory _factory;    
    AttributeVector _attributes;
  };
    
}
}

#endif
