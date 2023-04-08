#version 330 core
out vec4 FragColor;
in float xPos;
uniform float stopPos;

void main() {
if (xPos < stopPos) {
FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
else {
FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
}
