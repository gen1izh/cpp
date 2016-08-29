#include "templateplugin.h"

/*
 * Создание объекта источника питания.
 */
ModuleInterface* TemplatePluginInterface::createModule( int id ) {
  TemplateModule* tmpl = new TemplateModule(NULL);
  tmpl->setId(id);
  return tmpl;
}

