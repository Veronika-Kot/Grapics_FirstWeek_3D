uniform mat4 MVP;
attribute vec3 vCol; //rgb
attribute vec3 vPos; //xyz vec2 for xy only
varying vec3 color;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0); //changed from vec4 bc vPos has 3 values now
    color = vCol;
}
