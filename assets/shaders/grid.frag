#version 330 core 

in vec3 worldPos;
out vec4 FragColor;

const float lineThickness = 3.5;

float grid(vec2 coord, float scale) {
    vec2 g = abs(fract(coord / scale - 0.5) - 0.5) / (fwidth(coord / scale));
    return min(g.x, g.y);
}

void main() {
    float small = grid(worldPos.xz, 50.0);
    float large = grid(worldPos.xz, 500.0);

    float line = min(small, large);
    line = 1.0 - clamp(line / lineThickness , 0.0, 1.0);

    float axisWidth = 1.75;

    float xAxis = 1.0 - min(abs(worldPos.z) / fwidth(worldPos.z), axisWidth) / axisWidth;
    float zAxis = 1.0 - min(abs(worldPos.x) / fwidth(worldPos.x), axisWidth) / axisWidth;

    xAxis = clamp(xAxis, 0.0, 1.0);
    zAxis = clamp(zAxis, 0.0, 1.0);

    vec3 gridColor = vec3(0.7);
    vec3 color = gridColor * line;

    color = mix(color, vec3(1.0, 0.0, 0.0), xAxis);
    color = mix(color, vec3(0.0, 0.2, 1.0), zAxis);

    float alpha = line; 
    alpha = max(alpha, xAxis);
    alpha = max(alpha, zAxis);

    FragColor = vec4(color, alpha);
}