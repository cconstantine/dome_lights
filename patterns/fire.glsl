// https://www.shadertoy.com/view/lsf3RH

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;
uniform sampler2D backbuffer;

void main(void) 
{
	vec2 p = -.5 + gl_FragCoord.xy / resolution.xy;// + vec2(1.-fract(time)*2., 0)*0.5;
	p.x *= resolution.x/resolution.y;
	
	float color = 3.0 - (3.*length(2.*p));
	
	vec3 coord = vec3(atan(p.x,p.y)/6.2832+.5, length(p)*.4, .5);
	
	for(int i = 1; i <= 7; i++)
	{
		float power = pow(2.0, float(i));
		
		vec3 uv = coord + vec3(0.,-time*.05, time*.01);
		float res = power*16.0;
		
		const vec3 s = vec3(1e0, 1e2, 1e4);
		uv *= res;
		vec3 uv0 = floor(mod(uv, res))*s;
		vec3 uv1 = floor(mod(uv+vec3(1.), res))*s;
		
		vec3 f = fract(uv); f = f*f*(3.0-2.0*f);
		
		vec4 v = vec4(uv0.x+uv0.y+uv0.z, uv1.x+uv0.y+uv0.z,
			      uv0.x+uv1.y+uv0.z, uv1.x+uv1.y+uv0.z);
		
		vec4 r = fract(sin(v*1e-3)*1e5);
		float r0 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);
		
		r = fract(sin((v + uv1.z - uv0.z)*1e-3)*1e5);
		float r1 = mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y);
		
		float snoise = mix(r0, r1, f.z)*2.-1.0;
		
		color += (1.5 / power) * snoise;
	}
	
	vec3 col = texture2D(backbuffer, gl_FragCoord.xy / resolution.xy).rgb;
	vec3 col2 = vec3( color, pow(max(color,0.),2.)*0.4, pow(max(color,0.),3.)*0.15);
	
	gl_FragColor = vec4(mix(col, col2, fract(time)*.05 + abs(cos(time))*.05), 1.);
}






