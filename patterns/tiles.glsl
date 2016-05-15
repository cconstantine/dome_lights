#version 330 core

// http://glslsandbox.com/e#31898.0

// Voronoi
// By: Brandon Fogerty
// bfogerty at gmail dot com
// xdpixel.com

#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

out vec4 color_out;

vec2 randomVec2( vec2 p )
{
  mat2 m = mat2( 15.27, 47.63,
           99.41, 88.98 );
  
  return fract( sin(m * p) * 46839.32 );
}

vec2 voronoi( vec2 p )
{
  
  vec2 g = floor( p );
  vec2 f = fract(p);
  
  float t = 8.0;
  
  vec3 res = vec3(8.0,0.0,0.0);
  
  for( int y = -1; y <= 1; ++y )
  {
    for( int x = -1; x <= 1; ++x )
    {
      vec2 lattice = vec2( x, y );
      vec2 offset = randomVec2(lattice + g);
      float d = distance( lattice + (sin( time * offset) * 0.5 + 0.5), f);
      
      if( d < res.x )
      {
        res = vec3( d, offset );
      }
    }
  }
  
  
  return vec2( res.yz );
}

void main( void ) {

  vec2 uv = ( gl_FragCoord.xy / resolution.xy ) * 2.0 - 1.0;
  uv.x *= resolution.x / resolution.y;

  vec2 c = voronoi( uv * 8.0 );
  vec3 finalColor = cos(c.x * 10.23 + vec3( 1.0, 2.0, 3.0)) * 0.5 + 0.5;
  color_out = vec4( finalColor, 1.0 );

}