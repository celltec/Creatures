@ctype mat4 Uniform

@vs vs
uniform vs_params {
    mat4 vpMatrix;
};

struct s_frag {
    vec2 uv;
    vec2 center;
    vec4 color;
};

in vec2 IN_pos;
in vec2 IN_uv;
in vec4 IN_center;
in float IN_radius;
in vec4 IN_color;

out s_frag FRAG;

void main()
{
    gl_Position = vpMatrix * vec4(IN_pos + IN_radius * IN_uv, 0, 1);
    FRAG.uv = IN_uv;
    FRAG.color = IN_color;
}
@end

@fs fs
struct s_frag {
    vec2 uv;
    vec2 center;
    vec4 color;
};

in s_frag FRAG;

out vec4 OUT_color;

void main()
{
    float len = length(FRAG.uv);
    float fw = length(fwidth(FRAG.uv));
    float mask = smoothstep(-1, fw - 1, -len);

    vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
    float outline = 1 - fw;
    float outline_mask = smoothstep(outline - fw, outline, len);
    vec4 color = FRAG.color + (black - FRAG.color) * outline_mask;

    OUT_color = color * mask;
}
@end

@program app vs fs