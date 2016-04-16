

uniform mat4 mvp;
attribute vec3 pos;
varying vec3 v_norm;


void main()
{
    v_norm = normalize(pos);
    gl_Position = mvp * vec4(pos,1.0);
}
