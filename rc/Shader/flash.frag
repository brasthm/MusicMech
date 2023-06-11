uniform sampler2D 	source;
uniform float time;

void main()
{
	float t = fract(time + gl_TexCoord[0].x);
	vec4 valImg = texture2D(source, gl_TexCoord[0].xy);
	vec4 color;
	if((int)time%3 == 0) 
		color = vec4(clamp(1 - abs(0.7*(gl_TexCoord[0].xxx-gl_TexCoord[0].yyy) - 4 + 8*(fract(-time))), 0, 1), 1);

	gl_FragColor = 0.2*color + valImg;
}