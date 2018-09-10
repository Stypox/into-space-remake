#version 330 core

in vec2 position;
in vec2 texturePosition;
in vec2 offset;
in float textureIndex;

out vec2 vTexturePosition;

uniform float screenRatio; 
uniform int nrPackedTextures;

const float optimalScreenRatio = 16.0/9.0;

void main() {
    gl_Position = vec4(position + offset, 0.0, 1.0);
    gl_Position.x /= optimalScreenRatio;
    if (screenRatio > optimalScreenRatio) {
        gl_Position.y = (gl_Position.y + 1.0) * screenRatio / optimalScreenRatio - 1.0;
    }
    else {
        gl_Position.x = gl_Position.x * optimalScreenRatio / screenRatio;
    }

    // calculates the texture position based on the index of the texture (assumes every texture is a square).
    // + 1e-6 is needed because otherwise the pixel position relative to the texture position is not rounded the right way.
    vTexturePosition.x = texturePosition.x / nrPackedTextures + textureIndex / nrPackedTextures + 1e-6;
    vTexturePosition.y = texturePosition.y;
}