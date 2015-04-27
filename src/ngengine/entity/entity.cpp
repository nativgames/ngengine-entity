#include <ngengine/entity/entity.h>
#include <stdexcept>

using namespace nge::entity;

AttributeDefinition::AttributeDefinition()
{
  type = 0;
  offset = 0;
}

AttributeDefinition::AttributeDefinition(std::string name, uint32_t type, uint32_t offset)
{
  this->name = name;
  this->type = type;
  this->offset = offset;
}

// --

Entity::Entity(Context *context)
{
  _context = context;
}

Entity::~Entity()
{
}

Context *Entity::__get_context()
{
  return _context;
}

void Entity::__set(std::string name, void *p)
{
  EntityDefinition *def = this->__get_definition();
  AttributeVector *attr = def->get_attributes();
  
  try {
    
    bool found = false;
    AttributeDefinition def;
    for(auto att: *attr) {
      if(att->name == name) {
        def = *att;//= attr->at(name);
        found = true;
        break;
      }
    }
    if(!found) return;
    
    uint8_t *q = (uint8_t *) this;
    q += def.offset;
    
    // now use the good serializer
    AbstractSerializer *serializer = _context->get_serializers()->at(def.type); // another std::out_of_range possible
    if(serializer) {
      serializer->copy(p, q);
    }
  }
  catch(const std::out_of_range& oor) {
    
  }
}

void *Entity::__get(std::string name)
{
  uint8_t *q = NULL;
  EntityDefinition *def = this->__get_definition();
  AttributeVector *attr = def->get_attributes();
  
  try {
    bool found = false;
    AttributeDefinition def;
    for(auto att: *attr) {
      if(att->name == name) {
        def = *att;//= attr->at(name);
        found = true;
        break;
      }
    }
    if(!found) return nullptr;
    
    q = (uint8_t *) this;
    q += def.offset;
  }
  catch(const std::out_of_range& oor) {
    
  }
  
  return q;
}

// -----------------

EntityDefinition::EntityDefinition()
{
  _type = UNKNOWN;
}

void EntityDefinition::define_attribute(std::string name, uint32_t type, void *instance_addr, void *instance_attr_addr)
{
  uint8_t *p1, *p2;
  p2 = (uint8_t *) instance_addr;
  p1 = (uint8_t *) instance_attr_addr; 
  this->_attributes.push_back(new AttributeDefinition(name, type, p1 - p2));
}

void EntityDefinition::set_table(std::string table)
{
  _table = table;
}

std::string EntityDefinition::get_table() const
{
  return _table;
}

void EntityDefinition::set_type(uint32_t type)
{
  _type = type;
}

uint32_t EntityDefinition::get_type()
{
  return _type;
}

void EntityDefinition::set_factory(EntityFactory factory)
{
  _factory = factory;
}

EntityFactory EntityDefinition::get_factory()
{
  return _factory;
}

void EntityDefinition::set_attributes(AttributeVector attributes)
{
  _attributes = attributes;
}

AttributeVector *EntityDefinition::get_attributes()
{
  return &_attributes;
}

const AttributeVector *EntityDefinition::get_attributes() const
{
  return &_attributes;
}
