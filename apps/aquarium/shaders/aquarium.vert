#version 410 core
layout(location = 0) in vec3 vertexPosition;

uniform float time;
uniform vec3 position;

void main() {
    vec3 pos = (vertexPosition + position);
    pos.x += sin(time) * pos.x * 0.5f;
    pos.y += cos(time) * pos.y * 0.5f;
    gl_Position = vec4(pos, 1.0);
}
