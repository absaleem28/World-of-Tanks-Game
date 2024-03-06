#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_norm;
layout(location = 2) in vec2 v_text;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 MeshColor;
uniform int MeshLifes;
uniform float Time_now;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// Output
// TODO(student): Output values to fragment shader
out vec3 frag_color;
out vec3 frag_norm;
out vec2 frag_text;
out vec3 frag_position;


void main()
{
   // TODO(student): Send output to fragment shader

   vec3 world_pos = (Model * vec4(v_position,1)).xyz;
   vec3 world_normal = normalize( mat3(Model) * v_norm);
   vec3 L = normalize( light_position - world_pos );
   vec3 V = normalize( eye_position - world_pos );
   vec3 H = normalize( L + V );

   float ambient_light = 0.25;

   float diffuse_light = 0;
   diffuse_light = material_kd * max (dot(v_norm,L), 0);

   float specular_light = 0;

   if (diffuse_light > 0)
   {
      vec3 R = reflect (-L, world_normal);
      specular_light = material_ks * diffuse_light * pow(max(dot(V, R), 0), material_shininess);
   }

   float light_color = diffuse_light + specular_light + ambient_light;

   
   frag_color = MeshColor * light_color;

   // TODO(student): Compute gl_Position
   if (MeshLifes < 3)
   {
      gl_Position = Projection * View * Model * vec4(v_position * vec3(0.25 * MeshLifes, 1, 0.25 * MeshLifes), 1.0);
   } else {
      gl_Position = Projection * View * Model * vec4(v_position, 1.0);
      
   }

}
