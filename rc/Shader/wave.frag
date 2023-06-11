uniform sampler2D 	source;
uniform float time;


#define TAU 6.283185

void main()
{
	float t = 0.3*time + 1.2*gl_TexCoord[0].y;
	vec2 v = vec2(gl_TexCoord[0].x - 0.02*cos(TAU * t), gl_TexCoord[0].y);
	

	vec4 valImg = texture2D(source, v);
	
	gl_FragColor = valImg;
}