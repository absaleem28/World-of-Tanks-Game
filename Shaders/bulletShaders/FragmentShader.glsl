#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_color;
in vec3 frag_norm;
in vec2 frag_text;
in vec3 frag_position;

// Output

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_norm;
layout(location = 2) out vec3 out_text;
layout(location = 3) out vec4 out_position;

void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(frag_color, 1);
    out_norm = vec4(frag_norm, 1);
    out_text = vec3(frag_text, 1);
    out_position = vec4(frag_position, 1);

}
