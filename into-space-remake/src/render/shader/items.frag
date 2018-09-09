#version 330 core

in vec2 vTexturePosition;

out vec4 outColor;

uniform sampler2D entitiesTexture;

void main() {
    outColor = texture(entitiesTexture, vTexturePosition);
}