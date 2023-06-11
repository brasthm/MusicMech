uniform sampler2D 	source;
uniform float time;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	float t = fract(time + gl_TexCoord[0].x);
	vec4 valImg = texture2D(source, gl_TexCoord[0].xy);
	float randval = rand( floor(gl_TexCoord[0].xx*30) + 0.2 * floor(20 * time));
	vec4 color;
	if(gl_TexCoord[0].y < 0.4*randval)
		color = vec4(hsv2rgb(vec3(gl_TexCoord[0].y/0.7, 0.6, 1)), 1);
	else
		color = vec4(1, 1, 1, 1);

	gl_FragColor = color * valImg;
}