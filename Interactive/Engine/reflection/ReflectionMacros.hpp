#pragma once

#define DEFINITION_ID unsigned int
#define DEFINITION_SIZE unsigned int

#define CLASS_DEFINITION(T) DEFINITION_ID DefinitionId {Interactive::RuntimeReflection::GenerateClassDefinition(__FILE__, Interactive::RuntimeReflection::GetClassSize<T>())};

#define RUNTIME_CLASS Interactive::RuntimeClass* RuntimeReflection {Interactive::RuntimeReflection::GenerateRuntimeClass(DefinitionId, this)};
#define DESTROY_RUNTIME_CLASS delete RuntimeReflection;