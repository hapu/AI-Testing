uniform mat4 mvp;
attribute vec3 position;
attribute vec3 color;
varying vec4 v_color;

void main()
{
    v_color = vec4(color, 1.0);
    gl_Position = mvp * vec4(position, 1.0);
}
