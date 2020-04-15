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
    gl_Position = vpMatrix * vec4(IN_pos + IN_radius * IN_uv, 0, 1);
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
    vec4 empty = vec4(0.0, 0.0, 0.0, 0.0);

    float len = length(FRAG.uv);
    float fw = length(fwidth(FRAG.uv));
    float mask = smoothstep(-0.9, fw - 0.9, -len);
    
    vec4 color = FRAG.color * mask;

    if (FRAG.highlight != empty)
    {
        color = (FRAG.color + (FRAG.highlight - FRAG.color) * smoothstep(0.0, 1.0, len)) * mask;
    }

    OUT_color = color;
}
@end

@program app vs fs