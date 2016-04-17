uniform samplerCube texture;
varying vec3 v_norm;

vec3 light_color;
vec3 light_direction;
vec3 ambient_color;
float ambient_weight;

vec3 norm;


vec3 diffuseCoeficent(vec3 normal, vec3 dir)
{
    float intensity = max(dot(-dir, normal), 0.0);
    return light_color * intensity;
}

vec4 ilumina(vec4 color)
{
    vec3 totalDiffuse = diffuseCoeficent(norm, light_direction);
    return vec4(  (  (ambient_color * ambient_weight) + (totalDiffuse * (1.0 - ambient_weight))) * color.rgb, color.w);
}

void main()
{
    // calc fragment normal
    norm = normalize(v_norm);
    // calc surfaceColor;
    vec4 surfaceColor = textureCube(texture, vec3(norm.x, -norm.y, norm.z));


    light_color     = vec3(1.0,1.0,1.0);
    light_direction = normalize(vec3(-0.3,-1.0,0.2));
    ambient_color   = vec3(1.0,1.0,1.0);
    ambient_weight  = 0.3;

    gl_FragColor = ilumina(surfaceColor);
}
