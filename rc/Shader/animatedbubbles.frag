uniform sampler2D 	source;
uniform float time;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float circle(float r, vec2 u, vec2 v) {
	float a = distance(u, v) - r;
	return a <= 0;
}

void main()
{

	//float t = fract(- 0.2*time + gl_TexCoord[0].x);
	vec4 valImg = texture2D(source, gl_TexCoord[0].xy);

	vec4 color;

	color = 0;
	float offset = 0.01*sin(time + gl_TexCoord[0].x);

	float c1 = 0.1*circle(0.1, vec2(0.02, 0.06), vec2(gl_TexCoord[0].x, gl_TexCoord[0].y/2 + offset)) ;
	float c2 = 0.1*circle(0.04, vec2(0.24, 0.07), vec2(gl_TexCoord[0].x, gl_TexCoord[0].y/2 + offset)) ;
	float c3 = 0.1*circle(0.1, vec2(0.44, 0.02), vec2(gl_TexCoord[0].x, gl_TexCoord[0].y/2 + offset)) ;
	float c4 = 0.1*circle(0.045, vec2(0.64, 0.1), vec2(gl_TexCoord[0].x, gl_TexCoord[0].y/2 + offset)) ;
	float c5 = 0.1*circle(0.1, vec2(0.855, 0.11), vec2(gl_TexCoord[0].x, gl_TexCoord[0].y/2 + offset)) ;
	float c6 = 0.1*circle(0.04, vec2(0.98, 0.27), vec2(gl_TexCoord[0].x, gl_TexCoord[0].y/2 + offset)) ;


	float grad = clamp(1-(gl_TexCoord[0].y + 1.6) * 0.5, 0, 1);

	gl_FragColor = (c1+ c2 + c3 + c4+ c5 + c6) * vec4(1, 1, 1, 1) + vec4(grad * vec3(1, 1, 1), 1) + valImg;
}