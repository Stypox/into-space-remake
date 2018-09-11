#version 330 core

in vec2 position;
in vec2 texturePosition;

in vec2 offset;
in vec2 size;
in float textureOffset;
in float textureWidth;

out vec2 vTexturePosition;

uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * vec4(position.x * size.x + offset.x, position.y * size.y + offset.y, 0.0, 1.0);

	if (position.x < 0.5) {
		// position.x is 0.0, thus < 0.5
		vTexturePosition.x = textureOffset;
	}
	else {
		// position.x is 1.0, thus >= 0.5
		vTexturePosition.x = textureOffset + textureWidth;
	}
	vTexturePosition.y = texturePosition.y;
}