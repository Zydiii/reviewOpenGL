#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void doTranslate()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	// 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
	// 下面这行代码就需要改为:
	// glm::mat4 trans = glm::mat4(1.0f)
	// 之后将不再进行提示
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;
}