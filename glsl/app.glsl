@ctype mat4 Uniform

@vs vs
uniform vs_params {
    mat4 vpMatrix;
};

struct s_frag {
    vec2 uv;
    vec4 color;
    vec4 highlight;
};

in vec2 IN_pos;
in vec2 IN_uv;
in float IN_radius;
in vec4 IN_color;
in vec4 IN_highlight;

out s_frag FRAG;

void main()
{
    vec2 pos = IN_pos + IN_radius * IN_uv;
    gl_Position = vpMatrix * vec4(pos, 0, 1);

    FRAG.uv = IN_uv;
    FRAG.color = IN_color;
    FRAG.highlight = IN_highlight;
}
@end

@fs fs
struct s_frag {
    vec2 uv;
    vec4 color;
    vec4 highlight;
};

in s_frag FRAG;

out vec4 OUT_color;

void main()
{
    vec4 empty = vec4(0.0);
    vec4 darker = vec4(vec3(0.8), 1.0);

    float border = length(FRAG.uv);
    float fw = length(fwidth(FRAG.uv));
    float mask = smoothstep(-0.9, fw - 0.9, -border);
    
    vec4 color = FRAG.color;

    color += ((darker * FRAG.color - FRAG.color) * smoothstep(0.0, 1.0, border));

    if (FRAG.highlight != empty)
    {
        //color += step(border + fw, FRAG.highlight);
    }

    OUT_color = color * mask;
}
@end

@program app vs fs
