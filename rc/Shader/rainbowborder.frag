uniform sampler2D 	source;
uniform float time;


vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	vec4 valImg = texture2D(source, gl_TexCoord[0].xy);

	vec4 color;

	if(gl_TexCoord[0].x < 0.02)
		color = vec4(hsv2rgb(vec3(fract(time - gl_TexCoord[0].y), 0.8, 1)), 1);
	else if(gl_TexCoord[0].x > 0.98)
		color = vec4(hsv2rgb(vec3(fract(time + gl_TexCoord[0].y), 0.8, 1)), 1);
	else if(gl_TexCoord[0].y > 0.95)
		color = vec4(hsv2rgb(vec3(fract(time - gl_TexCoord[0].x), 0.8, 1)), 1);
	else if(gl_TexCoord[0].y < 0.05)
		color = vec4(hsv2rgb(vec3(fract(time + gl_TexCoord[0].x), 0.8, 1)), 1);
	else
		color = valImg;

	gl_FragColor = color;// + valImg;
}