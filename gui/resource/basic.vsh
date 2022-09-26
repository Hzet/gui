#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

struct SModel
{
	mat4 transform;
};

struct SCamera
{
	mat4 projection;
	mat4 view;
};

uniform SCamera aglCamera;
uniform SModel aglModel;

out vec4 vColor;

void main()
{
	vColor = aColor;
	gl_Position = aglCamera.projection * aglCamera.view * aglModel.transform * vec4(aPos, 1.f);
}