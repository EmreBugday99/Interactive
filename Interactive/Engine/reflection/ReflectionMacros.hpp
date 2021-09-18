#pragma once

#define DEFINITON_ID int
#define DEFINITION_SIZE size_t

#define CLASS_DEFINITION(T) DEFINITON_ID DefinitionId {Interactive::RuntimeReflection::GenerateClassDefinition(__FILE__, Interactive::RuntimeReflection::GetClassSize<T>())};

#define RUNTIME_CLASS Interactive::RuntimeClass* RuntimeReflection {Interactive::RuntimeReflection::GenerateRuntimeClass(DefinitionId, this)};