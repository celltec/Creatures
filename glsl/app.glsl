  
@ctype mat4 hmm_mat4

@vs vs
uniform vs_params {
    mat4 mvp;
};

in vec4 position;
in vec4 color;
out vec4 vert_color;

void main()
{
    gl_Position = mvp * position;
    vert_color = color;
}
@end

@fs fs
in vec4 vert_color;
out vec4 frag_color;

void main()
{
    frag_color = vert_color;
}
@end

@program app vs fs