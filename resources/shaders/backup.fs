uniform samplerCube texture;
varying vec3 v_norm;

void main()
{
    vec3 normal = vec3(v_norm.x, -v_norm.y, v_norm.z);
    gl_FragColor = textureCube(texture, normal);
}
