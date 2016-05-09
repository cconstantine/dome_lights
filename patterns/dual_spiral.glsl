#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
varying vec2 surfacePosition;

void main(void) {
  vec2 pos = surfacePosition;
  float dist = length(pos) / 2.0;

  vec3 color = vec3(0.0);
  float ang = atan(pos.y, pos.x) / 3.14159265;
  if(mod(ang - dist + time / 5.0, 0.05) < 0.01 || dist < 0.01) color = vec3(0.55, 0.25, 1.0);
  if(mod(ang + dist - time / 10.0, 0.05) < 0.01) color = vec3(0.05, 0.45, 0.85);
  gl_FragColor = vec4(vec3(color), 1.0 );

}