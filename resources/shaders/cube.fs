uniform samplerCube texture;
varying vec3 v_norm;

vec3 light_color = vec3(1.0, 0.0, 0.0);
float light_intensity = 0.6;
float ambient_coefficient = 0.2;
vec3 light_direction = normalize(vec3(-1.0, -1.0, 0.0));
vec4 surface_color = textureCube(texture, vec3(v_norm.x, -v_norm.y, v_norm.z));

vec4 calcAmbient(vec4 color) {
  return vec4(ambient_coefficient * color.rgb * light_intensity, color.w);
}

vec4 calcDiffuse(vec4 color) {
  float diffuse_coefficient =
      max(0.0, dot(normalize(v_norm), -light_direction));
  return vec4(diffuse_coefficient * color.rgb * light_intensity, color.w);
}

void main() {
  gl_FragColor = calcDiffuse(surface_color) + calcAmbient(surface_color);
}
