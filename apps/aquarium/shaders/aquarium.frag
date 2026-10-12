#version 410 core
uniform float time;

out vec4 fragColor;

void main() {
    float wave = sin(time) * 0.5 + 0.5;
    fragColor = vec4(0.1, wave, 1.0 - wave * 0.5, 1.0);
}
