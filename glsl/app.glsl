@vs vs
layout(location = 0) in vec2 IN_pos;
layout(location = 1) in vec2 IN_uv;
layout(location = 2) in float IN_radius;
layout(location = 3) in vec4 IN_fill;
layout(location = 4) in vec4 IN_outline;
			
uniform mat4 U_vp_matrix;
			
out struct {
	vec2 uv;
	vec4 fill;
	vec4 outline;
} FRAG;
			
void main(){
	gl_Position = U_vp_matrix*vec4(IN_pos + IN_radius*IN_uv, 0, 1);
	FRAG.uv = IN_uv;
	FRAG.fill = IN_fill;
	FRAG.fill.rgb *= IN_fill.a;
	FRAG.outline = IN_outline;
	FRAG.outline.a *= IN_outline.a;
}
@end

@fs fs
			in struct {
				vec2 uv;
				vec4 fill;
				vec4 outline;
			} FRAG;
			
			out vec4 OUT_color;
			
			void main(){
				float len = length(FRAG.uv);
				float fw = length(fwidth(FRAG.uv));
				float mask = smoothstep(-1, fw - 1, -len);
				
				float outline = 1 - fw;
				float outline_mask = smoothstep(outline - fw, outline, len);
				vec4 color = FRAG.fill + (FRAG.outline - FRAG.fill*FRAG.outline.a)*outline_mask;
				OUT_color = color*mask;
			}
@end

@program app vs fs
