
// hole3SphereShape: colored sphere with 3 cylindrical holes

#ifdef GL_ES
  precision mediump float;
#endif

uniform float time;
varying vec2 surfacePosition;
  
#define ptpi 1385.4557313670110891409199368797 //powten(pi)
#define pipi  36.462159607207911770990826022692 //pi pied, pi^pi
#define picu  31.006276680299820175476315067101 //pi cubed, pi^3
#define pepi  23.140692632779269005729086367949 //powe(pi);
#define chpi  11.59195327552152062775175205256  //cosh(pi)
#define shpi  11.548739357257748377977334315388 //sinh(pi)
#define pisq  9.8696044010893586188344909998762 //pi squared, pi^2
#define twoPi  6.283185307179586476925286766559  //two pi, 2*pi
#define pi    3.1415926535897932384626433832795 //pi
#define e     2.7182818284590452353602874713526 //eulers number
#define sqpi  1.7724538509055160272981674833411 //square root of pi
#define phi   1.6180339887498948482045868343656 //golden ratio
#define hfpi  1.5707963267948966192313216916398 //half pi, 1/pi
#define cupi  1.4645918875615232630201425272638 //cube root of pi
#define prpi  1.4396194958475906883364908049738 //pi root of pi
#define lnpi  1.1447298858494001741434273513531 //logn(pi);
#define trpi  1.0471975511965977461542144610932 //one third of pi, pi/3
#define thpi  0.99627207622074994426469058001254//tanh(pi)
#define lgpi  0.4971498726941338543512682882909 //log(pi)      
#define rcpi  0.31830988618379067153776752674503// reciprocal of pi  , 1/pi 
#define rcpipi  0.0274256931232981061195562708591 // reciprocal of pipi  , 1/pipi

float tt = time * e;
float t = rcpi*(pi+tt/pisq) + pepi;
float k = lgpi*(pi+tt/chpi) + chpi;

vec3 qAxis = normalize(vec3(sin(t*(prpi)), cos(k*(cupi)), cos(k*(hfpi)) ));
vec3 wAxis = normalize(vec3(cos(k*(-trpi)/pi), sin(t*(rcpi)/pi), sin(k*(lgpi)/pi) ));
vec3 sAxis = normalize(vec3(cos(t*(trpi)), sin(t*(-rcpi)), sin(k*(lgpi)) ));
float axe = pow(qAxis.x+qAxis.y+qAxis.z+wAxis.x+wAxis.y+wAxis.z+sAxis.x+sAxis.y+sAxis.z,2.0);

vec3 camPos = (vec3(0.0, 0.0, 1.0));
vec3 camUp  = (vec3(0.0, 1.0, 0.0));
float focus = 77.0;  //pi+sin(t)*phi;
vec3 camTarget = vec3(0.0);

vec3 rotate(vec3 vec, vec3 axis, float ang)
{
    return vec * cos(ang) + cross(axis, vec) * sin(ang) + axis * dot(axis, vec) * (1.0 - cos(ang));
}

vec3 pin(vec3 v)
{
    vec3 q = vec3(0.5);
    q.x += 0.5*sin(v.x);
    q.y += 0.5*sin(v.y+0.66666667*pi);
    q.z += 0.5*sin(v.z+1.33333333*pi);
    return (q);
}

vec3 spin(vec3 v)
{
    for(int i = 1; i <3; i++)
    {
        v=pin(rotate((v),pin(v),float(i*i)))*e;
    }
    return (v.xyz);
}

vec3 fin(vec3 v)
{
  vec4 vt = vec4(v,(v.x+v.y+v.z)/pi);
  vec4 vs = vt;
  vt.xyz  += pin(vs.xyz);
  vt.xyz  += pin(vs.yzw);
  vt.xyz  += pin(vs.zwx);
  vt.xyz  += pin(vs.wxy);
  return spin(vt.xyz/pisq);
}

vec3 shapeColor(vec3 v)
{
    for(int i = 1; i < 6; i++)
    {
        v =(v+fin(v*float(i)));
    }
    return (normalize((pin(v.zxy)))+sqrt(spin(v.zxy*rcpi)));
}

// sphere with 3 pipe holes
float hole3Sphere(vec3 p, float sphereRadius, float holeFactor) 
{
    float rd = sphereRadius * holeFactor;
    return max(-min( min(length(p.xy)-rd
                  ,length(p.yz)-rd)
                   ,length(p.zx)-rd)
            ,length(p)-sphereRadius);
}

void main( void )
{
    vec2 pos = (surfacePosition*e)*pi;//(sin(t*pi)+2.0);
    float ang = (sin(t*lnpi)*pi)+(distance(sAxis,wAxis)+distance(qAxis,sAxis)+distance(wAxis,qAxis));
    camPos = chpi*(camPos * cos(ang) + cross(qAxis, camPos) * sin(ang) + qAxis * dot(qAxis, camPos) * (1.0 - cos(ang)));
   
    vec3 camDir = normalize(camTarget-camPos);
    //camUp = rotate(camUp, camDir, sin(t*prpi)*pi);
    vec3 camSide = cross(camDir, camUp);
    vec3 sideNorm=normalize(cross(camUp, camDir));
    vec3 upNorm=cross(camDir, sideNorm);
    vec3 worldFacing=(camPos + camDir);
    vec3 rayDir = -normalize((worldFacing+sideNorm*pos.x + upNorm*pos.y - camDir*((focus))));
   
    vec3 clr = pin(rayDir);
  
    vec3 vx = camPos;
   
    float t = 0.1;
    for(int i = 0 ; i < 100; i++) 
    {
        float temp = hole3Sphere(camPos + rayDir * t, 0.5, 0.6);
        if(temp <= 0.0) break;
        t += temp;
    }
    clr = (camPos + rayDir * t);
    clr = vec3( shapeColor(clr*twoPi) / sqrt(t));
    gl_FragColor = vec4(clr, 1.0);
}