@ctype mat4 hmm_mat4

@vs vs
uniform vs_params {
    mat4 mvp;
};

struct s_frag {
    vec2 uv;
    vec4 fill;
    vec4 outline;
};

in vec2 IN_pos;
in vec2 IN_uv;
in float IN_radius;
in vec4 IN_fill;
in vec4 IN_outline;

out s_frag FRAG;

void main(){
    gl_Position = mvp * vec4(IN_pos + IN_radius * IN_uv, 1, 1);
    FRAG.uv = IN_uv;
    FRAG.fill = IN_fill;
    FRAG.fill.rgb *= IN_fill.a;
    FRAG.outline = IN_outline;
    FRAG.outline.a *= IN_outline.a;
}
@end

@fs fs
struct s_frag {
    vec2 uv;
    vec4 fill;
    vec4 outline;
};

in s_frag FRAG;

out vec4 OUT_color;

void main(){
    float len = length(FRAG.uv);
    float fw = length(fwidth(FRAG.uv));
    float mask = smoothstep(-1, fw - 1, -len);

    float outline = 1 - fw;
    float outline_mask = smoothstep(outline - fw, outline, len);
    vec4 color = FRAG.fill + (FRAG.outline - FRAG.fill * FRAG.outline.a) * outline_mask;
    OUT_color = color * mask;
}
@end

@program app vs fs