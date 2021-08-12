#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void doTranslate()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	// ��ע��������Ǿ����ʼ����һ�����ӣ����ʹ�õ���0.9.9�����ϰ汾
	// �������д������Ҫ��Ϊ:
	// glm::mat4 trans = glm::mat4(1.0f)
	// ֮�󽫲��ٽ�����ʾ
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
}