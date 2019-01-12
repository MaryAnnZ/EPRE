#include "MeshLoadInfo.h"
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::LIGHTING_SHADER = new ShaderLoadInfo(std::string("vertexShaderPath"), std::string("fragmentShaderPath"));
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::TEXTURE_SHADER = new ShaderLoadInfo(std::string("../kingsrow/Shader/Vertex/texture_vertex_shader.glsl"), std::string("../kingsrow/Shader/Fragment/texture_fragment_shader.glsl"));
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::SIMPLE_LIGHTING_SHADER = new ShaderLoadInfo(std::string("../kingsrow/Shader/Vertex/SimpleVertexShader.vertexshader"), std::string("../kingsrow/Shader/Fragment/SimpleFragmentShader.fragmentshader"));
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::GBUFFER_SHADER = new ShaderLoadInfo(std::string("../kingsrow/Shader/Vertex/gBuffer.vertexshader"), std::string("../kingsrow/Shader/Fragment/gBuffer.fragmentshader"));
const MeshLoadInfo::ShaderLoadInfo* MeshLoadInfo::DEFERRED_SHADER = new ShaderLoadInfo(std::string("../kingsrow/Shader/Vertex/deferredShader.vertexshader"), std::string("../kingsrow/Shader/Fragment/deferredShader.fragmentshader"));


const MeshLoadInfo::LoadInfo* MeshLoadInfo::TABLE = new LoadInfo(std::string("../kingsrow/Assets/Models/Table.dae"), std::string("../kingsrow/Assets/Models/duck_textures/rainbow.jpg"), SIMPLE_LIGHTING_SHADER, MeshLoadInfo::CollisionType::DYNAMIC, MeshLoadInfo::CollisionShapeType::CONVEX);
const MeshLoadInfo::LoadInfo* MeshLoadInfo::NANO = new LoadInfo(std::string("../kingsrow/Assets/Models/cube.dae"), std::string("../kingsrow/Assets/Models/duck_textures/duck.png"), GBUFFER_SHADER, MeshLoadInfo::CollisionType::DYNAMIC, MeshLoadInfo::CollisionShapeType::CONVEX);