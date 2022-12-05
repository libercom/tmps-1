#pragma once

#include <cstdint>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader 
{
public:
	Shader(const std::string&, const std::string&);
	virtual ~Shader();

	void Bind();
	void Unbind();
	void SetInt(const std::string&, int);
	void SetFloat(const std::string&, float);
	void SetFloat2(const std::string&, const glm::vec2&);
	void SetFloat3(const std::string&, const glm::vec3&);
	void SetFloat4(const std::string&, const glm::vec4&);
	void SetMat4(const std::string&, const glm::mat4&);
private:
	uint32_t m_ProgramId;
};