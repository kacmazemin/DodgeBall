#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform float u_ctime;
uniform float u_gtime;
uniform vec4 u_color;
uniform int way;

float easeOutCubic(float t, float b, float c, float d) {
    t /= d;
    t--;
    return c*(t*t*t + 1.0) + b;
}

void main() {
    vec4 tex = texture2D(CC_Texture0, v_texCoord);
    
    float progress = easeOutCubic(u_ctime, -2.0, 3.0, u_gtime);
    float diff;
    if(way == 1) // CROSS
    {
        progress += v_texCoord.y;
        diff = v_texCoord.x - progress;
    }
    else if(way == 2) // RIGHT
    {
        diff = v_texCoord.x -progress;
    }
    else // UP
    {
        progress += v_texCoord.y;
        diff = - progress;
    }
    
    if (diff <= 0.8 && diff > 0.0) {
        tex = tex + (u_color * diff) * tex.a * u_color.a;
    }
    gl_FragColor = tex * v_fragmentColor;
}
